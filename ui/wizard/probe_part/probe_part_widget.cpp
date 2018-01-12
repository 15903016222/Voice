#include "probe_part_widget.h"

#include <QKeyEvent>
#include <QLineEdit>

#include "ui_probe_part_widget.h"
#include "ui/wizard/weld/main_weld_widget.h"
#include <ui/menu/probe_part/probe_dialog.h>    /* 探头 */
#include "ui/menu/probe_part/wedge_dialog.h"   /* 楔块 */

static const int DEFAULT_WELD_INDEX = 4;  /* VV_Weld */

ProbePartWidget::ProbePartWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProbePartWidget),
    m_type(type)
{
    ui->setupUi(this);

    ui->grooveTypeComboBox->setCurrentIndex(DEFAULT_WELD_INDEX);

    connect(ui->editWeldBtn, SIGNAL(clicked(bool)), this, SLOT(do_editWeldBtn_clicked()));
    connect(ui->tkyBtn, SIGNAL(clicked(bool)), this, SLOT(do_editWeldBtn_clicked()));
    connect(ui->shapeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(do_shapeComboBox_current_index_changed(int)));

    if(WizardSetting::UT_DETECT != type) {
        m_mainWeldWidget = new MainWeldWidget();
    }

    ui->probeModelLineEdit->installEventFilter(this);
}

ProbePartWidget::~ProbePartWidget()
{
    delete ui;

    if(WizardSetting::UT_DETECT != m_type) {
           delete m_mainWeldWidget;
    }
}

void ProbePartWidget::do_editWeldBtn_clicked()
{
    QPushButton *current = qobject_cast<QPushButton*> (sender());

    if(current->objectName() == ui->editWeldBtn->objectName()) {
        m_mainWeldWidget->show_widget(ui->grooveTypeComboBox->currentIndex(), ui->thicknessDoubleSpinBox->value());
    } else if(current->objectName() == ui->tkyBtn->objectName()) {
        m_mainWeldWidget->show_widget(ui->grooveTypeComboBox->count(), ui->thicknessDoubleSpinBox->value());
    }
}


void ProbePartWidget::do_shapeComboBox_current_index_changed(int index)
{
    if(index == PLATE) {
        ui->externalDiameterDoubleSpinBox->setEnabled(false);
        ui->innerDiameterDoubleSpinBox->setEnabled(false);
    } else {
        ui->externalDiameterDoubleSpinBox->setEnabled(true);
        ui->innerDiameterDoubleSpinBox->setEnabled(true);
    }
}


void ProbePartWidget::on_probeModelDefineBtn_clicked()
{
    ProbeDialog probeDialog(this);
    if(probeDialog.exec() == QDialog::Accepted) {
        ui->probeModelLineEdit->setText("");
    }
}


void ProbePartWidget::on_wedgeModelDefineBtn_clicked()
{
    WedgeDialog wedgeDialog(this);
    if(wedgeDialog.exec() == QDialog::Accepted) {
        ui->wedgeModelLineEdit->setText("");
    }
}

void ProbePartWidget::on_importCADBtn_clicked()
{

}

