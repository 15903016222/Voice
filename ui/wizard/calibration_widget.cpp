#include "calibration_widget.h"

#include <QDebug>
#include <QVBoxLayout>
#include "ui_calibration_widget.h"

#include "encoder_properties_widget.h"
#include "sound_velocity_properties_widget.h"
#include "delay_properties_widget.h"
#include "acg_properties_widget.h"
#include "tcg_properties_widget.h"

#include "tofd_properties_widget.h"
#include "angle_properties_widget.h"


CalibrationWidget::CalibrationWidget(WizardSetting::E_WIZARD_TYPE type, bool isSubCalibrationWidget, QWidget *parent) :
    CommonSettingWidget(type, parent),
    ui(new Ui::CalibrationWidget),
    m_currentIndex(0),
    m_isSubWidget(isSubCalibrationWidget)
{
    ui->setupUi(this);

    initItem();
}

CalibrationWidget::~CalibrationWidget()
{
    delete ui;
}

void CalibrationWidget::on_backBtn_clicked()
{
    emit back_clicked();
}

void CalibrationWidget::on_finishedBtn_clicked()
{
    emit finished_clicked();
}


void CalibrationWidget::do_optionComboBox_current_index_changed(int index)
{
    m_widgetMap.value(m_currentIndex)->hide();

    QWidget *currentWidget = m_widgetMap.value(index);
    currentWidget->setGeometry(0, 0, ui->propertiesWidget->width(), ui->propertiesWidget->height());
    currentWidget->show();

    m_currentIndex = index;

}

void CalibrationWidget::do_nextGroupBtn_clicked()
{
    emit next_group_clicked();
}


void CalibrationWidget::do_utDetectSettingWidget_current_mode_changed(int index)
{
    m_mode = (CommonSettingWidget::E_DETECT_MODE)index;

    if(CommonSettingWidget::TOFD == index) {

        ui->optionLabel->setHidden(true);
        ui->optionComboBox->setHidden(true);

        m_widgetMap.value(SINGLE_DETECT_SOUND_VELOVITY_PROPERTIES)->hide();
        m_widgetMap.value(SINGLE_DETECT_DELAY_PROPERTIES)->hide();
        m_widgetMap.value(SINGLE_DETECT_ANGLE_PROPERTIES)->hide();
        m_widgetMap.value(SINGLE_DETECT_TOFD_PROPERTIES)->show();


    } else if(CommonSettingWidget::PE == index) {

        ui->optionLabel->setHidden(false);
        ui->optionComboBox->setHidden(false);

        m_widgetMap.value(SINGLE_DETECT_TOFD_PROPERTIES)->hide();

        m_widgetMap.value(ui->optionComboBox->currentIndex())->show();
        m_currentIndex = ui->optionComboBox->currentIndex();
    }
}


void CalibrationWidget::initItem()
{
    if(WizardSetting::SINGLE_DETECT == m_type) {

        disconnect(ui->optionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));
        disconnect(ui->optionComboBox, SIGNAL(activated(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));

        ui->optionComboBox->clear();
        ui->optionComboBox->addItem(tr("Sound Velocity"));
        ui->optionComboBox->addItem(tr("Delay"));
        ui->optionComboBox->addItem(tr("Angle"));

        m_widgetMap.insert(SINGLE_DETECT_SOUND_VELOVITY_PROPERTIES, new SoundVelocityPropertiesWidget(m_type, ui->propertiesWidget));
        m_widgetMap.insert(SINGLE_DETECT_DELAY_PROPERTIES, new DelayPropertiesWidget(m_type, ui->propertiesWidget));
        m_widgetMap.insert(SINGLE_DETECT_ANGLE_PROPERTIES, new AnglePropertiesWidget(ui->propertiesWidget));
        m_widgetMap.insert(SINGLE_DETECT_TOFD_PROPERTIES, new TOFDPropertiesWidget(ui->propertiesWidget));

        connect(ui->optionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));
        connect(ui->optionComboBox, SIGNAL(activated(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));

        if(CommonSettingWidget::TOFD == m_mode) {

            ui->optionLabel->hide();
            ui->optionComboBox->hide();

            m_currentIndex = SINGLE_DETECT_TOFD_PROPERTIES; /* TOFD */

        } else if(CommonSettingWidget::PE == m_mode) {

            ui->optionLabel->setHidden(false);
            ui->optionComboBox->setHidden(false);

        } else {
            return;
        }
    } else {

        disconnect(ui->optionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));
        disconnect(ui->optionComboBox, SIGNAL(activated(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));

        ui->optionComboBox->clear();
        ui->optionComboBox->addItem(tr("Encoder"));
        ui->optionComboBox->addItem(tr("Sound Velocity"));
        ui->optionComboBox->addItem(tr("Delay"));
        ui->optionComboBox->addItem(tr("ACG"));
        ui->optionComboBox->addItem(tr("TCG"));

        connect(ui->optionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));
        connect(ui->optionComboBox, SIGNAL(activated(int)), this, SLOT(do_optionComboBox_current_index_changed(int)));

        m_widgetMap.insert(PA_ENCODER_PROPERTIES, new EncoderPropertiesWidget(ui->propertiesWidget));
        m_widgetMap.insert(PA_SOUND_VELOVITY_PROPERTIES, new SoundVelocityPropertiesWidget(m_type, ui->propertiesWidget));
        m_widgetMap.insert(PA_DELAY_PROPERTIES, new DelayPropertiesWidget(m_type, ui->propertiesWidget));
        m_widgetMap.insert(PA_ACG_PROPERTIES, new ACGPropertiesWidget(ui->propertiesWidget));
        m_widgetMap.insert(PA_TCG_PROPERTIES, new TCGPropertiesWidget(ui->propertiesWidget));
    }

    if(m_isSubWidget) {
        QPushButton *newGroupBtn = new QPushButton(tr("Next Group"), this);
        newGroupBtn->setSizePolicy(ui->acceptBtn->sizePolicy());
        ui->btnHorizontalLayout->addWidget(newGroupBtn);
        connect(newGroupBtn, SIGNAL(clicked(bool)), this, SLOT(do_nextGroupBtn_clicked()));
    }

    m_widgetMap.value(m_currentIndex)->show();
}
