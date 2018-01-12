#include "wizard.h"
#include "ui_wizard.h"

#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>

#include "step_widget.h"

#include <configuration/configuration.h>
#include <ui/dialog/dpl_message_box.h>
#include <ui/dialog/file_dialog.h>

static const QString  CONFIG_FILE_PATH = "/opt/mercury/configs/";
static const QString  DATA_FILE_PATH = "/opt/mercury/usr/data/";

static const QString WELD_PA_ICO = ":/resource/wizard/weld_pa.png";
static const QString COMMON_PA_ICO = ":/resource/wizard/common_pa.png";
static const QString MULTI_GROUP_ICO = ":/resource/wizard/multi_group.png";
static const QString UT_ICO = ":/resource/wizard/ut.png";
static const QString OPEN_DATA_ICO = ":/resource/wizard/open_data.png";
static const QString OPEN_CONFIG_ICO = ":/resource/wizard/open_config.png";

Wizard::Wizard(QWidget *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wizard),
    m_mainWindow(mainWindow),
    m_wizardSetting(new WizardSetting(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(m_wizardSetting, SIGNAL(finished_wizard_setting(WizardSetting::E_WIZARD_TYPE)),
            this, SLOT(slot_finished_wizard_setting(WizardSetting::E_WIZARD_TYPE)));
    connect(m_wizardSetting, SIGNAL(cancle_wizard_setting()), this, SLOT(show()));

}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return) {
        if(ui->commonPADetectPushButton->hasFocus()) {
            on_commonPADetectPushButton_clicked();
        } else if(ui->multiGroupDetectPushButton->hasFocus()) {
            on_multiGroupDetectPushButton_clicked();
        } else if(ui->openConfigPushButton->hasFocus()) {
            on_openConfigPushButton_clicked();
        } else if(ui->openDataPushButton->hasFocus()) {
            on_openDataPushButton_clicked();
        } else if(ui->utDetectPushButton->hasFocus()) {
            on_utDetectPushButton_clicked();
        } else if(ui->weldPADetectPushButton->hasFocus()) {
            on_weldPADetectPushButton_clicked();
        } else {
            return QWidget::keyPressEvent(event);
        }
        return;
    }
    return QWidget::keyPressEvent(event);
}

void Wizard::slot_finished_wizard_setting(WizardSetting::E_WIZARD_TYPE type)
{
    Q_UNUSED(type);
    m_mainWindow->show();
}

void Wizard::on_weldPADetectPushButton_clicked()
{
    m_wizardSetting->show(WizardSetting::WELD_PA_DETECT);
}

void Wizard::on_commonPADetectPushButton_clicked()
{
    m_wizardSetting->show(WizardSetting::COMMON_PA_DETECT);
}

void Wizard::on_multiGroupDetectPushButton_clicked()
{
    m_wizardSetting->show(WizardSetting::MULTI_GROUP_DETECT);
}

void Wizard::on_utDetectPushButton_clicked()
{
    m_wizardSetting->show(WizardSetting::UT_DETECT);
}

void Wizard::on_openDataPushButton_clicked()
{
    FileDialog::S_FileDialogParameters param;
    param.cancelButtonText  = tr("Cancel");
    param.okButtonText      = tr("Open");
    param.filePath          = DATA_FILE_PATH;
    param.title             = tr("Data Files");
    param.nameFilters       = QStringList("*.data");

    FileDialog fileDialog(param);

    if(fileDialog.exec() == QMessageBox::Accepted) {
        m_mainWindow->show();
        this->close();
        return;
    }
}

void Wizard::on_openConfigPushButton_clicked()
{
    FileDialog::S_FileDialogParameters param;
    param.cancelButtonText  = tr("Cancel");
    param.okButtonText      = tr("Open");
    param.filePath          = CONFIG_FILE_PATH;
    param.title             = tr("Setup Files");
    param.nameFilters       = QStringList("*.cfg");
    param.operation         = FileDialog::Config;

    FileDialog fileDialog(param);

    if(fileDialog.exec() == QMessageBox::Accepted) {
        Config::Configuration config;
        if(config.load_config(fileDialog.get_selected_file_name())) {
            DplMessageBox messageBox(QMessageBox::Information, tr("Open Config File"), tr("Open Success!"));
            messageBox.exec();
            m_mainWindow->show();
            this->close();
            return;
        }

        DplMessageBox messageBox(QMessageBox::Warning, tr("Open Config File"), tr("Open Failed!"));
        messageBox.exec();
    }
}
