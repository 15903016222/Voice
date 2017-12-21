#include "wizard.h"
#include "ui_wizard.h"

#include <QFileDialog>
#include <QKeyEvent>

#include "step_widget.h"
#include "base_open_file_dialog.h"

static const QString  DATA_FILE_PATH    = "/home/tt/TT/";
static const QString  CONFIG_FILE_PATH  = "/home/tt/TT/";

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


void Wizard::on_weldPADetectBtn_clicked()
{
    m_wizardSetting->show(WizardSetting::WELD_PA_DETECT);
}

void Wizard::on_currentPADetectBtn_clicked()
{
    m_wizardSetting->show(WizardSetting::CURRENT_PA_DETECT);
}


void Wizard::on_multiGroupDetectBtn_clicked()
{
    m_wizardSetting->show(WizardSetting::MULTI_GROUP_DETECT);
}


void Wizard::on_singleDetectBtn_clicked()
{
    m_wizardSetting->show(WizardSetting::SINGLE_DETECT);
}


void Wizard::on_openDataBtn_clicked()
{
    BaseOpenFileDialog fileDialog(CONFIG_FILE_PATH, this);
    fileDialog.exec();

    if(fileDialog.get_selected_file().isEmpty()) {
        return;
    }

    m_mainWindow->show();
    this->close();
}


void Wizard::on_openConfigFileBtn_clicked()
{
    BaseOpenFileDialog fileDialog(CONFIG_FILE_PATH, this);
    fileDialog.exec();

    if(fileDialog.get_selected_file().isEmpty()) {
        return;
    }

    m_mainWindow->show();
    this->close();

}

void Wizard::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
        if(ui->currentPADetectBtn->hasFocus()) {
            on_currentPADetectBtn_clicked();
        } else if(ui->multiGroupDetectBtn->hasFocus()) {
            on_multiGroupDetectBtn_clicked();
        } else if(ui->openConfigFileBtn->hasFocus()) {
            on_openConfigFileBtn_clicked();
        } else if(ui->openDataBtn->hasFocus()) {
            on_openDataBtn_clicked();
        } else if(ui->singleDetectBtn->hasFocus()) {
            on_singleDetectBtn_clicked();
        } else if(ui->weldPADetectBtn->hasFocus()) {
            on_weldPADetectBtn_clicked();
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


