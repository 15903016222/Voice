#include "wedge_dialog.h"
#include "ui_wedge_dialog.h"

#include <QDir>
#include <QKeyEvent>
#include <QDebug>

#include <global.h>
#include <device/device.h>

WedgeDialog::WedgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WedgeDialog),
    m_wedgePtr(new DplFocallaw::Wedge())
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    init_select_tab();
    init_define_tab();

    ui->dirListWidget->installEventFilter(this);
    ui->fileListWidget->installEventFilter(this);
}

WedgeDialog::~WedgeDialog()
{
    delete ui;
}

bool WedgeDialog::eventFilter(QObject *obj, QEvent *e)
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

QString WedgeDialog::get_dir()
{
    QString path = "/opt/mercury/wedge/";
    DplDevice::GroupPointer group = DplDevice::Device::instance()->current_group();

    if (group->mode() == DplDevice::Group::PA
            || group->mode() == DplDevice::Group::UT) {
        path += "PA/";
    } else {
        path += "UT/";
    }

    return path;
}

void WedgeDialog::init_select_tab()
{
    QDir dir(get_dir());

    QStringList dirStringList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
    ui->dirListWidget->insertItems(0, dirStringList);
}

void WedgeDialog::init_define_tab()
{
    QString path = get_dir();
    path += "user";
    QDir dir(path);
    QStringList filesStringList = dir.entryList(QDir::Files|QDir::NoSymLinks, QDir::Name);
    ui->defineListWidget->clear();
    ui->defineListWidget->insertItems(0, filesStringList);

    DplDevice::GroupPointer group = DplDevice::Device::instance()->current_group();
    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        ui->orientationComboBox->hide();
        ui->OrientationLabel->hide();
        ui->velocityDoubleSpinBox->hide();
        ui->velocityLabel->hide();
        ui->primaryOffsetDoubleSpinBox->hide();
        ui->primaryOffsetLabel->hide();
        ui->sndOffsetDoubleSpinBox->hide();
        ui->sndOffsetLabel->hide();
        ui->heightDoubleSpinBox->hide();
        ui->HeightLabel->hide();
        ui->lengthDoubleSpinBox->hide();
        ui->LengthLabel->hide();
    } else {
        ui->waveTypeComboBox->hide();
        ui->waveTypeLabel->hide();
        ui->refPointLlabel->hide();
        ui->refPointDoubleSpinBox->hide();
        ui->delayLabel->hide();
        ui->delaySpinBox->hide();
    }
}

void WedgeDialog::show_pa() const
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
            + m_wedgePtr->serial() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Model") + "</th><td>"
            + m_wedgePtr->model() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Angle") + "</th><td>"
            + QString::number(m_wedgePtr->angle(), 'f', 1)
            + " &#176;</td></tr>";

    msg += "<tr><th>";
    msg += tr("Orientation") + "</th><td>";
    if (m_wedgePtr->orientation() == DplFocallaw::Wedge::Normal) {
        msg += tr("Normal");
    } else {
        msg += tr("Reversal");
    }
    msg += "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Velocity") + "</th><td>"
            + QString::number(m_wedgePtr->velocity(DplFocallaw::Wedge::Longitudinal))
            + " m/s</td></tr>";

    msg += "<tr><th>";
    msg += tr("Primary Offset") + "</th><td>"
            + QString::number(m_wedgePtr->primary_offset(), 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Secondary Offset") + "</th><td>"
            + QString::number(m_wedgePtr->secondary_offset(), 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Height") + "</th><td>"
            + QString::number(m_wedgePtr->height(), 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Length") + "</th><td>"
            + QString::number(m_wedgePtr->length(), 'f', 2)
            + " mm</td></tr>";

    msg += "</table>"
           "</body>"
           "</html>";

    ui->label->setText(msg);
}

void WedgeDialog::show_ut() const
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
            + m_wedgePtr->serial() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Model") + "</th><td>"
            + m_wedgePtr->model() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Angle") + "</th><td>"
            + QString::number(m_wedgePtr->angle(), 'f', 1)
            + " &#176;</td></tr>";

    msg += "<tr><th>";
    msg += tr("Delay") + "</th><td>"
            + QString::number(m_wedgePtr->delay()/1000.0, 'f', 3)
            + " ms</td></tr>";

    msg += "</table>"
           "</body>"
           "</html>";

    ui->label->setText(msg);
}

void WedgeDialog::on_dirListWidget_currentTextChanged(const QString &currentText)
{
    QString path = get_dir() + currentText;

    QDir dir(path);
    QStringList filesStringList = dir.entryList(QDir::Files|QDir::NoSymLinks, QDir::Name);

    ui->fileListWidget->clear();
    ui->fileListWidget->insertItems(0, filesStringList);
}

void WedgeDialog::on_fileListWidget_currentTextChanged(const QString &currentText)
{
    m_path = get_dir();
    m_path += ui->dirListWidget->currentItem()->text() + "/";
    m_path += currentText;

    if (! m_wedgePtr->load(m_path)) {
        m_path.clear();
        ui->label->setText(tr("Ultrasonic phased array wedge family."));
        return;
    }

    DplDevice::GroupPointer group = DplDevice::Device::instance()->current_group();
    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        show_ut();
    } else {
        show_pa();
    }
}

void WedgeDialog::on_okPushButton_clicked()
{
    this->accept();
}

void WedgeDialog::on_cancelPushButton_clicked()
{
    this->reject();
}

void WedgeDialog::on_cancelDefinePushButton_clicked()
{
    this->reject();
}

void WedgeDialog::on_savePushButton_clicked()
{
    if (ui->modelLineEdit->text().isEmpty()
            || ui->serialLineEdit->text().isEmpty()) {
        return;
    }

    DplDevice::GroupPointer group = DplDevice::Device::instance()->current_group();
    QString path = get_dir();

    path += "user/";
    path += ui->modelLineEdit->text();

    m_wedgePtr->set_serial(ui->serialLineEdit->text());
    m_wedgePtr->set_model(ui->modelLineEdit->text());
    m_wedgePtr->set_angle(ui->angleDoubleSpinBox->value());

    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        path += ".ouw";
        m_wedgePtr->set_delay(ui->delaySpinBox->value());
//        m_wedgePtr->set_wave_type(static_cast<DplFocallaw::Wedge::WaveType>(ui->waveTypeComboBox->currentIndex()));
//        m_wedgePtr->set_ref_point(ui->refPointDoubleSpinBox->value());
    } else {
        path += ".opw";
        m_wedgePtr->set_orientation(static_cast<DplFocallaw::Wedge::Orientation>(ui->orientationComboBox->currentIndex()));
//        m_wedgePtr->set_velocity(ui->velocityDoubleSpinBox->value());
        m_wedgePtr->set_primary_offset(ui->primaryOffsetDoubleSpinBox->value());
        m_wedgePtr->set_secondary_offset(ui->sndOffsetDoubleSpinBox->value());
        m_wedgePtr->set_height(ui->heightDoubleSpinBox->value());
        m_wedgePtr->set_length(ui->lengthDoubleSpinBox->value());
    }

    if (m_wedgePtr->save(path)) {
        init_define_tab();
    }
}

void WedgeDialog::on_saveApplyPushButton_clicked()
{
    if (ui->modelLineEdit->text().isEmpty()
            || ui->serialLineEdit->text().isEmpty()) {
        return;
    }

    on_savePushButton_clicked();

    this->accept();
}

void WedgeDialog::on_delPushButton_clicked()
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
