#include "wedge_dialog.h"
#include "ui_wedge_dialog.h"

#include <QDir>
#include <QKeyEvent>
#include <QDebug>

#include <global.h>
#include <device/device.h>

WedgeDialog::WedgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WedgeDialog)
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
    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();

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

    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();
    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
    }
}

const QString WedgeDialog::show(const DplProbe::Wedge &wedge)
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
           "margin:5px;"
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
            + wedge.serial() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Model") + "</th><td>"
            + wedge.model() + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Wave Type") + "</th><td>";
    if (wedge.wave_type() == DplProbe::Wedge::Longitudinal) {
        msg += tr("Longitudinal");
    } else if (wedge.wave_type() == DplProbe::Wedge::Transverse) {
        msg += tr("Transverse");
    } else {
        msg += tr("Unkown");
    }
    msg += "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Angle") + "</th><td>"
            + QString::number(wedge.angel(), 'f', 1)
            + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Delay") + "</th><td>"
            + QString::number(wedge.delay()/1000.0, 'f', 2)
            + "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Orientation") + "</th><td>";
    if (wedge.orientation() == DplProbe::Wedge::Normal) {
        msg += tr("Normal");
    } else {
        msg += tr("Reversal");
    }
    msg += "</td></tr>";

    msg += "<tr><th>";
    msg += tr("Velocity") + "</th><td>"
            + QString::number(wedge.velocity())
            + " m/s</td></tr>";

    msg += "<tr><th>";
    msg += tr("Primary Offset") + "</th><td>"
            + QString::number(wedge.primary_offset(), 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Secondary Offset") + "</th><td>"
            + QString::number(wedge.secondary_offset(), 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Height") + "</th><td>"
            + QString::number(wedge.height(), 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Length") + "</th><td>"
            + QString::number(wedge.length(), 'f', 2)
            + " mm</td></tr>";

    msg += "<tr><th>";
    msg += tr("Ref Point") + "</th><td>"
            + QString::number(wedge.ref_point(), 'f', 2)
            + " mm</td></tr>";

    msg += "</table>"
           "</body>"
           "</html>";

    return msg;
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
    m_wedgePath = get_dir();
    m_wedgePath += ui->dirListWidget->currentItem()->text() + "/";
    m_wedgePath += currentText;

    DplProbe::Wedge wedge;
    if (wedge.load(m_wedgePath)) {
        ui->label->setText(show(wedge));
    } else {
        m_wedgePath.clear();
        ui->label->setText(tr("Ultrasonic phased array wedge family."));
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

    return ;

    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();
    DplProbe::Wedge wedge;
    QString path = get_dir();

    path += "user/";
    path += ui->modelLineEdit->text();

    if (group->mode() == DplDevice::Group::UT1
            || group->mode() == DplDevice::Group::UT2) {
        path += ".oup";
    } else {
        path += ".opp";
    }

    if (wedge.save(path)) {
        init_define_tab();
        m_wedgePath = path;
    }
}

void WedgeDialog::on_saveApplyPushButton_clicked()
{
    on_savePushButton_clicked();

    if (ui->modelLineEdit->text().isEmpty()
            || ui->serialLineEdit->text().isEmpty()) {
        return;
    }

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
