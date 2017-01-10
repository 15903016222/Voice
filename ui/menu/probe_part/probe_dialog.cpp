#include "probe_dialog.h"
#include "ui_probe_dialog.h"

#include <QDir>
#include <QKeyEvent>
#include <QDebug>

#include <device/device.h>
#include <probe/probe.h>

ProbeDialog::ProbeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProbeDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    QDir dir(get_path());

    QStringList dirStringList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name);
    ui->dirListWidget->insertItems(0, dirStringList);

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

QString ProbeDialog::get_path()
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

void ProbeDialog::on_dirListWidget_currentTextChanged(const QString &currentText)
{
    QString path = get_path() + currentText;

    QDir dir(path);
    QStringList filesStringList = dir.entryList(QDir::Files|QDir::NoSymLinks, QDir::Name);

    ui->fileListWidget->clear();
    ui->fileListWidget->insertItems(0, filesStringList);
}

void ProbeDialog::on_fileListWidget_currentTextChanged(const QString &currentText)
{
    m_probePath = get_path();
    m_probePath += ui->dirListWidget->currentItem()->text() + "/";
    m_probePath += currentText;

    DplProbe::Probe probe;
    if (probe.load(m_probePath)) {
        ui->label->setText(probe.show());
        m_probePath.clear();
    } else {
        ui->label->setText(tr("Ultrasonic phased array probe family."));
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
