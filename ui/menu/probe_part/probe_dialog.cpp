#include "probe_dialog.h"
#include "ui_probe_dialog.h"

#include <QDir>
#include <QKeyEvent>
#include <QDebug>

#include <device/device.h>
#include <probe/probe.h>

ProbeDialog::ProbeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProbeDialog),
    m_probePtr(new DplProbe::Probe())
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

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
    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();

    if (group->mode() == DplDevice::Group::PA
            || group->mode() == DplDevice::Group::UT) {
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

    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();
    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        ui->typeComboBox->hide();
        ui->typeLabel->hide();
        ui->elemQtyLabel->hide();
        ui->elemQtySpinBox->hide();
        ui->refPointDoubleSpinBox->hide();
        ui->refPointLabel->hide();
        ui->pitchLabel->setText(tr("Element Size"));
    }
}

void ProbeDialog::show_pa() const
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
    case DplProbe::Probe::CUSTOM:
        msg += "Custom";
        break;
    case DplProbe::Probe::ANGLE_BEAM:
        msg += "Angle Beam";
        break;
    case DplProbe::Probe::CONTACT:
        msg += "Contact";
        break;
    case DplProbe::Probe::IMMERSION:
        msg += "Immersion";
        break;
    default:
        msg += "Unkown";
        break;
    }
    msg += "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Element Qty") + "</th><td>"
            + QString::number(m_probePtr->element_qty())
            + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Freq") + "</th><td>"
            + QString::number(m_probePtr->freq()/1000.0, 'f', 2)
            + " MHz</td></tr>";

    msg += "<tr><th>";
    msg += tr("Pitch") + "</th><td>"
            + QString::number(m_probePtr->pitch()/1000.0, 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Ref Point") + "</th><td>"
            + QString::number(m_probePtr->refpoint()/1000.0, 'f', 2)
            + " mm</td></tr>";

    msg += "</table>"
           "</body>"
           "</html>";

    ui->label->setText(msg);
}

void ProbeDialog::show_ut() const
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
    msg += tr("Freq") + "</th><td>"
            + QString::number(m_probePtr->freq()/1000.0, 'f', 2)
            + " MHz</td></tr>";

    msg += tr("Element Size") + "</th><td>"
            + QString::number(m_probePtr->element_size(), 'f', 2)
            + " mm</td></tr>";

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
    m_probePath = get_dir();
    m_probePath += ui->dirListWidget->currentItem()->text() + "/";
    m_probePath += currentText;

    if (!m_probePtr->load(m_probePath)) {
        m_probePath.clear();
        ui->label->setText(tr("Ultrasonic phased array probe family."));
    }

    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();
    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        show_ut();
    } else {
        show_pa();
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

    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();
    DplProbe::Probe probe;
    QString path = get_dir();

    path += "user/";
    path += ui->modelLineEdit->text();

    probe.set_serial(ui->serialLineEdit->text());
    probe.set_model(ui->modelLineEdit->text());
    probe.set_freq(ui->freqDoubleSpinBox->value()*1000);

    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        path += ".oup";
        probe.set_type(DplProbe::Probe::CONVENTION);
        probe.set_element_size(ui->pitchDoubleSpinBox->value()*1000);
    } else {
        path += ".opp";
        switch (ui->typeComboBox->currentIndex()) {
        case 1:
            probe.set_type(DplProbe::Probe::CUSTOM);
            break;
        case 3:
            probe.set_type(DplProbe::Probe::ANGLE_BEAM);
            break;
        case 5:
            probe.set_type(DplProbe::Probe::CONTACT);
            break;
        case 6:
            probe.set_type(DplProbe::Probe::IMMERSION);
            break;
        default:
            probe.set_type(DplProbe::Probe::UNKNOWN);
            break;
        }
        probe.set_element_qty(ui->elemQtySpinBox->value());
        probe.set_pitch(ui->pitchDoubleSpinBox->value()*1000);
        probe.set_refpoint(ui->refPointDoubleSpinBox->value()*1000);
    }

    if (probe.save(path)) {
        init_define_tab();
        m_probePath = path;
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
