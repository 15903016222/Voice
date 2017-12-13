#include "workpiece_probe_widget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QLineEdit>

#include "ui_workpiece_probe_widget.h"
#include "../wizard/main_weld_widget/main_weld_widget.h"

#include "../menu/probe_part/wedge_dialog.h"   /* 探头 */
#include "base_open_file_dialog.h"

static const int DEFAULT_WELD_INDEX = 4;  /* VV_Weld */

WorkpieceProbeWidget::WorkpieceProbeWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkpieceProbeWidget),
    m_type(type)
{
    ui->setupUi(this);

    ui->grooveTypeComboBox->setCurrentIndex(DEFAULT_WELD_INDEX);

    connect(ui->editWeldBtn, SIGNAL(clicked(bool)), this, SLOT(do_editWeldBtn_clicked()));
    connect(ui->tkyBtn, SIGNAL(clicked(bool)), this, SLOT(do_editWeldBtn_clicked()));
    connect(ui->shapeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(do_shapeComboBox_current_index_changed(int)));

    if(WizardSetting::SINGLE_DETECT != type) {

        m_mainWeldWidget = new MainWeldWidget();
    }

    ui->probeModelOtherLineEdit->installEventFilter(this);
}

WorkpieceProbeWidget::~WorkpieceProbeWidget()
{
    qDebug()<< "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;

    if(WizardSetting::SINGLE_DETECT != m_type) {

           delete m_mainWeldWidget;
    }
}

void WorkpieceProbeWidget::do_editWeldBtn_clicked()
{
    QPushButton *current = qobject_cast<QPushButton*> (sender());

    if(current->objectName() == ui->editWeldBtn->objectName()) {

        m_mainWeldWidget->show_widget(ui->grooveTypeComboBox->currentIndex(), ui->thicknessDoubleSpinBox->value());

    } else if(current->objectName() == ui->tkyBtn->objectName()) {

        m_mainWeldWidget->show_widget(ui->grooveTypeComboBox->count(), ui->thicknessDoubleSpinBox->value());
    }
}


void WorkpieceProbeWidget::do_shapeComboBox_current_index_changed(int index)
{
    if(index == PLATE) {
        ui->externalDiameterDoubleSpinBox->setEnabled(false);
        ui->innerDiameterDoubleSpinBox->setEnabled(false);
    } else {
        ui->externalDiameterDoubleSpinBox->setEnabled(true);
        ui->innerDiameterDoubleSpinBox->setEnabled(true);
    }
}


void WorkpieceProbeWidget::on_probeModelDefineBtn_clicked()
{
    WedgeDialog wedgeDialog(this);
    wedgeDialog.exec();
}


void WorkpieceProbeWidget::on_moduleModelDefineBtn_clicked()
{
    WedgeDialog wedgeDialog(this);
    wedgeDialog.exec();
}

void WorkpieceProbeWidget::on_importCADBtn_clicked()
{
    BaseOpenFileDialog fileDialog("/home/tt/TT/", this);
    fileDialog.exec();
    qDebug() << "[" << __FUNCTION__ << "]" << fileDialog.get_selected_file();
}

