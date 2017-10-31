#include "probe_dialog.h"
#include "ui_probe_dialog.h"

#include <QDir>
#include <QKeyEvent>

#include <device/device.h>
#include <focallaw/ut_probe.h>
#include <focallaw/pa_probe.h>

ProbeDialog::ProbeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProbeDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    DplDevice::GroupPointer group = DplDevice::Device::instance()->current_group();
    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        m_probePtr = DplFocallaw::UtProbePointer(new DplFocallaw::UtProbe);
    } else {
        m_probePtr = DplFocallaw::PaProbePointer(new DplFocallaw::PaProbe);
    }

    init_select_tab();
    init_define_tab();

    ui->dirListWidget->installEventFilter(this);
    ui->fileListWidget->installEventFilter(this);
}

ProbeDialog::~ProbeDialog()
{
    delete ui;
}

bool ProbeDialog::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() != QEvent::KeyRelease) {
        return  QDialog::eventFilter(obj, e);
    }

    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
    if (keyEvent->key() != Qt::Key_Return) {
        return false;
    }

    if (ui->dirListWidget->hasFocus()) {
        ui->dirListWidget->clearFocus();
        ui->fileListWidget->setFocus();
    } else if (ui->fileListWidget->hasFocus()) {
        this->accept();
    }

    return true;
}

QString ProbeDialog::get_dir()
{
    QString path = "/opt/mercury/probe/";

    if (m_probePtr->is_pa()) {
        path += "PA/";
    } else {
        path += "UT/";
    }

    return path;
}

void ProbeDialog::init_select_tab()
{
    QDir dir(get_dir());

    QStringList dirStringList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
    ui->dirListWidget->insertItems(0, dirStringList);
}

void ProbeDialog::init_define_tab()
{
    QString path = get_dir();
    path += "user";
    QDir dir(path);
    QStringList filesStringList = dir.entryList(QDir::Files|QDir::NoSymLinks, QDir::Name);
    ui->defineListWidget->clear();
    ui->defineListWidget->insertItems(0, filesStringList);

    if (! m_probePtr->is_pa()) {
        ui->priElemQtyLabel->hide();
        ui->secElemQtyLabel->hide();
        ui->priElemQtySpinBox->hide();
        ui->secElemQtySpinBox->hide();
        ui->refPointDoubleSpinBox->hide();
        ui->refPointLabel->hide();
        ui->priPitchLabel->hide();
        ui->priPitchDoubleSpinBox->hide();
        ui->secPitchLabel->hide();
        ui->secPitchDoubleSpinBox->hide();
    }
}

void ProbeDialog::show_info() const
{
    QString msg;

    msg += "<html><head><title>Wedge Information</title>"
           "<style>"
           "table, th, td {"
           "padding:5px;"
           "border: 1px solid black;"
           "border-collapse: collapse;"
           "}"
           "table {"
           "margin:0px;"
           "}"
           "th {"
           "text-align:left;"
           "background:#CCCCFF;"
           "}"
           "td {"
           "text-align:left;"
           "}"
           "</style>"
           "</head>"
           "<body>"
           "<table border=1 cellspacing=1 cellpadding=0>";

    msg += "<tr><th>";
    msg += tr("Serial") + "</th><td>"
            + m_probePtr->serial() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Model") + "</th><td>"
            + m_probePtr->model() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Type") + "</th><td>";
    switch (m_probePtr->type()) {
    case DplFocallaw::Probe::ANGLE_BEAM:
        msg += tr("Angle Beam");
        break;
    case DplFocallaw::Probe::CONTACT:
        msg += tr("Contact");
        break;
    case DplFocallaw::Probe::IMMERSION:
        msg += tr("Immersion");
        break;
    case DplFocallaw::Probe::DELAY:
        msg += tr("Delay");
        break;
    case DplFocallaw::Probe::DUAL:
        msg += tr("Dual");
        break;
    case DplFocallaw::Probe::TOFD:
        msg += "TOFD";
        break;
    default:
        msg += tr("Unkown");
        break;
    }
    msg += "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Freq") + "</th><td>"
            + QString::number(m_probePtr->freq(), 'f', 2)
            + " MHz</td></tr>";

    if (m_probePtr->is_pa()) {
        DplFocallaw::PaProbePointer paProbePtr = m_probePtr.staticCast<DplFocallaw::PaProbe>();

        msg += "<tr><th>";
        msg += tr("Array Type") + "</th><td>";
        switch (paProbePtr->array_mode()) {
        case DplFocallaw::PaProbe::LINEAR:
            msg += tr("Linear");
            break;
        case DplFocallaw::PaProbe::CURVED:
            msg += tr("Curved");
            break;
        case DplFocallaw::PaProbe::MATRIX:
            msg += tr("Matrix");
            break;
        case DplFocallaw::PaProbe::DUAL_LINEAR:
            msg += tr("Dual Linear");
            break;
        case DplFocallaw::PaProbe::DUAL_MATRIX:
            msg += tr("Dual Matrix");
            break;
        default:
            msg += tr("Unkown");
            break;
        }
        msg += "</td></tr>";

        msg += "<tr><th>";
        msg += tr("Pri Element Qty") + "</th><td>"
                + QString::number(paProbePtr->primary_element_qty())
                + "</td></tr>";

        msg += "<tr><th>";
        msg += tr("Sec Element Qty") + "</th><td>"
                + QString::number(paProbePtr->secondary_element_qty())
                + "</td></tr>";

        msg += "<tr><th>";
        msg += tr("Pri Pitch") + "</th><td>"
                + QString::number(paProbePtr->primary_pitch(), 'f', 2)
                + " mm</td></tr>";

        msg += "<tr><th>";
        msg += tr("Sec Pitch") + "</th><td>"
                + QString::number(paProbePtr->secondary_pitch(), 'f', 2)
                + " mm</td></tr>";
    } else {
        /* Ut Probe */

    }

    msg += "</table>"
           "</body>"
           "</html>";

    ui->label->setText(msg);
}

void ProbeDialog::on_dirListWidget_currentTextChanged(const QString &currentText)
{
    QString path = get_dir() + currentText;

    QDir dir(path);
    QStringList filesStringList = dir.entryList(QDir::Files|QDir::NoSymLinks, QDir::Name);

    ui->fileListWidget->clear();
    ui->fileListWidget->insertItems(0, filesStringList);
}

void ProbeDialog::on_fileListWidget_currentTextChanged(const QString &currentText)
{
    QString path = get_dir();
    path += ui->dirListWidget->currentItem()->text() + "/";
    path += currentText;

    if (!m_probePtr->load(path)) {
        ui->label->setText(tr("Ultrasonic phased array probe family."));
    } else {
        show_info();
    }
}

void ProbeDialog::on_okPushButton_clicked()
{
    this->accept();
}

void ProbeDialog::on_cancelPushButton_clicked()
{
    this->reject();
}

void ProbeDialog::on_cancelDefinePushButton_clicked()
{
    this->reject();
}

void ProbeDialog::on_savePushButton_clicked()
{
    if (ui->modelLineEdit->text().isEmpty()
            || ui->serialLineEdit->text().isEmpty()) {
        return;
    }

    QString m_probePath = get_dir();

    m_probePath += "user/";
    m_probePath += ui->modelLineEdit->text();

    if (m_probePtr->is_pa()) {
        m_probePath += ".opp";
    } else {
        m_probePath += ".oup";
    }

    if (m_probePtr->save(m_probePath)) {
        init_define_tab();
    }
}

void ProbeDialog::on_saveApplyPushButton_clicked()
{
    on_savePushButton_clicked();

    if (ui->modelLineEdit->text().isEmpty()
            || ui->serialLineEdit->text().isEmpty()) {
        return;
    }

    this->accept();
}

void ProbeDialog::on_delPushButton_clicked()
{
    QString path = get_dir();
    path += "user/";

    if (ui->defineListWidget->currentItem() == NULL) {
        return;
    }

    path += ui->defineListWidget->currentItem()->text();

    if (QFile::remove(path)) {
        init_define_tab();
    }
}

void ProbeDialog::on_modelLineEdit_textEdited(const QString &arg1)
{
    m_probePtr->set_model(arg1);
}

void ProbeDialog::on_serialLineEdit_textEdited(const QString &arg1)
{
    m_probePtr->set_serial(arg1);
}

void ProbeDialog::on_typeComboBox_currentIndexChanged(int index)
{
    m_probePtr->set_type(static_cast<DplFocallaw::Probe::Type>(index));
}

void ProbeDialog::on_freqDoubleSpinBox_valueChanged(double arg1)
{
    m_probePtr->set_freq(arg1);
}

void ProbeDialog::on_priElemQtySpinBox_valueChanged(int arg1)
{
    if (m_probePtr->is_pa()) {
        DplFocallaw::PaProbePointer paProbePtr = m_probePtr.staticCast<DplFocallaw::PaProbe>();
        paProbePtr->set_primary_element_qty(arg1);
    }
}

void ProbeDialog::on_secElemQtySpinBox_valueChanged(int arg1)
{
    if (m_probePtr->is_pa()) {
        DplFocallaw::PaProbePointer paProbePtr = m_probePtr.staticCast<DplFocallaw::PaProbe>();
        paProbePtr->set_secondary_element_qty(arg1);
    }
}

void ProbeDialog::on_priPitchDoubleSpinBox_valueChanged(double arg1)
{
    if (m_probePtr->is_pa()) {
        DplFocallaw::PaProbePointer paProbePtr = m_probePtr.staticCast<DplFocallaw::PaProbe>();
        paProbePtr->set_primary_pitch(arg1);
    }
}

void ProbeDialog::on_secPitchDoubleSpinBox_valueChanged(double arg1)
{
    if (m_probePtr->is_pa()) {
        DplFocallaw::PaProbePointer paProbePtr = m_probePtr.staticCast<DplFocallaw::PaProbe>();
        paProbePtr->set_secondary_pitch(arg1);
    }
}
