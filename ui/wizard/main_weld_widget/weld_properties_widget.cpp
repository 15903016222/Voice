#include "weld_properties_widget.h"
#include "ui_weld_properties_widget.h"

#include <QObject>
#include <QDebug>
#include <math.h>

#include "base_weld_information.h"

#define MAX_SIZE    499.99
#define MIN_SIZE    0.00

WeldPropertiesWidget::WeldPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeldPropertiesWidget),
    m_thickness(0.0)
{
    ui->setupUi(this);

    show_item();

    connect(ui->weldTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_weld_type_changed(int)));

    connect(ui->H1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->H2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->H3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->R1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->R2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));


    connect(ui->T1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->T2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->X1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->Y1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->X2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->Y2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

}

WeldPropertiesWidget::~WeldPropertiesWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}


void WeldPropertiesWidget::slot_weld_type_changed(int index)
{
    Q_UNUSED(index);
    reset_value();
    show_item();
}



void WeldPropertiesWidget::slot_weld_info_changed(double value)
{
    Q_UNUSED(value);
    QMap<QString, double> valueList;

    QDoubleSpinBox *current = qobject_cast<QDoubleSpinBox*> (sender());

    switch (ui->weldTypeComboBox->currentIndex())
    {
        case DplWeld::I_Weld:
        {
            valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());
            break;
        }
        case DplWeld::V_Weld:
        {

            if(current->objectName() == ui->W1DoubleSpinBox->objectName()) {
                ui->W2DoubleSpinBox->setMaximum(value);

            } else if(current->objectName() == ui->W2DoubleSpinBox->objectName()) {
                ui->W1DoubleSpinBox->setMinimum(value);
            }

            valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
            valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
            valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

            break;
        }
        case DplWeld::U_Weld:
        {
            check_u_weld_properties_limit(current, value);

            valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
            valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
            valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
            valueList.insert(TAG_R1, ui->R1DoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

            break;
        }
        case DplWeld::VY_Weld:
        {

            if(current->objectName() == ui->W1DoubleSpinBox->objectName()) {

                ui->W2DoubleSpinBox->setMaximum(value);

            } else if(current->objectName() == ui->W2DoubleSpinBox->objectName()) {

                ui->W1DoubleSpinBox->setMinimum(value);
                ui->W3DoubleSpinBox->setMaximum(value);

            } else if(current->objectName() == ui->W3DoubleSpinBox->objectName()) {

                ui->W2DoubleSpinBox->setMinimum(value);

            } else if(current->objectName() == ui->H1DoubleSpinBox->objectName()) {

                ui->H2DoubleSpinBox->setMaximum(m_thickness - value);

            } else if(current->objectName() == ui->H2DoubleSpinBox->objectName()) {

                ui->H1DoubleSpinBox->setMaximum(m_thickness - value);

            }

            valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
            valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
            valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
            valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
            valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

            break;
        }
        case DplWeld::VV_Weld:
        {
            check_vv_weld_properties_limit(current, value);

            valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
            valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
            valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
            valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
            valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

            break;
        }
        case DplWeld::UU_Weld:
        {
            check_u_weld_properties_limit(current, value);

            valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
            valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
            valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
            valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
            valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
            valueList.insert(TAG_R1, ui->R1DoubleSpinBox->value());
            valueList.insert(TAG_R2, ui->R2DoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

            break;
        }
        case DplWeld::UV_Weld:
        {
            check_u_weld_properties_limit(current, value);

            valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
            valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
            valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
            valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
            valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
            valueList.insert(TAG_R1, ui->R1DoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

            break;
        }
        case DplWeld::TKY_Weld:
        {
            valueList.insert(TAG_T1, ui->T1DoubleSpinBox->value());
            valueList.insert(TAG_T2, ui->T2DoubleSpinBox->value());
            valueList.insert(TAG_X1, ui->X1DoubleSpinBox->value());
            valueList.insert(TAG_Y1, ui->Y1DoubleSpinBox->value());
            valueList.insert(TAG_X2, ui->X2DoubleSpinBox->value());
            valueList.insert(TAG_Y2, ui->Y2DoubleSpinBox->value());
            valueList.insert(TAG_ANGLE, ui->angleDoubleSpinBox->value());
            valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

            break;
        }
        default:
            return;
    }

    emit weld_info_changed(ui->weldTypeComboBox->currentIndex(), valueList);

}


void WeldPropertiesWidget::set_weld_info(const QMap<QString, double> &valueList)
{
    qDebug() << "[" << __FUNCTION__ << "]" << m_thickness << " new thickness : " << valueList.value(TAG_THICKNESS);

    disconnect(ui->weldTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_weld_type_changed(int)));

    ui->weldTypeComboBox->setCurrentIndex(valueList.value(TAG_TYPE));

    connect(ui->weldTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_weld_type_changed(int)));

    set_value(valueList);

    switch ((int)valueList.value(TAG_TYPE))
    {
        case DplWeld::I_Weld:
        {
            show_i_weld_item(m_valueList);
            break;
        }
        case DplWeld::V_Weld:
        {
            show_v_weld_item(m_valueList);
            break;
        }
        case DplWeld::U_Weld:
        {
            show_u_weld_item(m_valueList);
            break;
        }
        case DplWeld::VY_Weld:
        {
            show_vy_weld_item(m_valueList);
            break;
        }
        case DplWeld::VV_Weld:
        {
            show_vv_weld_item(m_valueList);
            break;
        }
        case DplWeld::UU_Weld:
        {
            show_uu_weld_item(m_valueList);
            break;
        }
        case DplWeld::UV_Weld:
        {
            show_uv_weld_item(m_valueList);
            break;
        }
        case DplWeld::TKY_Weld:
        {
            show_tky_weld_item(m_valueList);
            break;
        }
        default:
            return;
    }
}




void WeldPropertiesWidget::slot_max_W1(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_max_W1]" << value;
    disconnect(ui->W1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    /* 若最大值小于当前值 故应设置W1的最大值、R1的最大值*/
    if(value < ui->W1DoubleSpinBox->value()) {
        check_u_weld_properties_limit(ui->W1DoubleSpinBox, value);
    }

    ui->W1DoubleSpinBox->setMaximum(value);
    connect(ui->W1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

}


void WeldPropertiesWidget::slot_max_W2(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_max_W2]" << value;
    disconnect(ui->W2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    ui->W2DoubleSpinBox->setMaximum(value);
    connect(ui->W2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    qDebug() << "[WeldPropertiesWidget::slotMaxW2] end";
}


void WeldPropertiesWidget::slot_max_W3(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_max_W3]" << value;
    disconnect(ui->W3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    /* 若最大值小于当前值 故应设置W2的最大值、R2的最大值*/
    if(value < ui->W3DoubleSpinBox->value()) {
        check_u_weld_properties_limit(ui->W3DoubleSpinBox, value);
    }

    ui->W3DoubleSpinBox->setMaximum(value);

    connect(ui->W3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::slot_min_H1(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_min_H1]"  << value;

    disconnect(ui->H1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    if(ui->H1DoubleSpinBox->value() < value) {
        ui->H1DoubleSpinBox->setMinimum(ui->H1DoubleSpinBox->value());
    } else {
        ui->H1DoubleSpinBox->setMinimum(value);
    }

    connect(ui->H1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::slot_min_H2(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_min_H2]"  << value;

    disconnect(ui->H2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    if(ui->H2DoubleSpinBox->value() < value) {
        ui->H2DoubleSpinBox->setMinimum(ui->H2DoubleSpinBox->value());
    } else {
        ui->H2DoubleSpinBox->setMinimum(value);
    }

    connect(ui->H2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}



void WeldPropertiesWidget::slot_min_R1(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_min_R1]"  << value;

    disconnect(ui->R1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    ui->R1DoubleSpinBox->setMinimum(value);

    connect(ui->R1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}



void WeldPropertiesWidget::slot_min_R2(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_min_R2]"  << value;

    disconnect(ui->R2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    ui->R2DoubleSpinBox->setMinimum(value);

    connect(ui->R2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::slot_min_X1(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_min_X1]"  << value;

    disconnect(ui->X1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    ui->X1DoubleSpinBox->setMinimum(value);
    connect(ui->X1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::slot_max_Y1(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_max_Y1]"  << value;

    disconnect(ui->Y1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    ui->Y1DoubleSpinBox->setMaximum(value);
    connect(ui->Y1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::slot_min_X2(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_min_X2]"  << value;

    disconnect(ui->X2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    ui->X2DoubleSpinBox->setMinimum(value);
    connect(ui->X2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}

void WeldPropertiesWidget::slot_max_Y2(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_max_Y2]"  << value;

    disconnect(ui->Y2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    ui->Y2DoubleSpinBox->setMaximum(value);
    connect(ui->Y2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::slot_min_angle(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_min_angle]"  << value;

    disconnect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    ui->angleDoubleSpinBox->setMinimum(value);
    connect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::slot_max_angle(double value)
{
    qDebug() << "[WeldPropertiesWidget::slot_max_angle]"  << value;

    disconnect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    ui->angleDoubleSpinBox->setMaximum(value);
    connect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}


void WeldPropertiesWidget::set_thickness(double value)
{
    m_thickness = value;
}



void WeldPropertiesWidget::show_item()
{
    m_valueList.clear();

    switch (ui->weldTypeComboBox->currentIndex())
    {
        case DplWeld::I_Weld:
        {
            show_i_weld_item(m_valueList);
            break;
        }
        case DplWeld::V_Weld:
        {
            show_v_weld_item(m_valueList);
            break;
        }
        case DplWeld::U_Weld:
        {
            show_u_weld_item(m_valueList);
            break;
        }
        case DplWeld::VY_Weld:
        {
            show_vy_weld_item(m_valueList);
            break;
        }
        case DplWeld::VV_Weld:
        {
            show_vv_weld_item(m_valueList);
            break;
        }
        case DplWeld::UU_Weld:
        {
            show_uu_weld_item(m_valueList);
            break;
        }
        case DplWeld::UV_Weld:
        {
            show_uv_weld_item(m_valueList);
            break;
        }
        case DplWeld::TKY_Weld:
        {
            show_tky_weld_item(m_valueList);
            break;
        }
        default:
            return;
    }

    m_valueList.insert(TAG_THICKNESS, m_thickness);

    emit weld_info_changed(ui->weldTypeComboBox->currentIndex(), m_valueList);
}


void WeldPropertiesWidget::show_i_weld_item(QMap<QString, double> &valueList)
{
    ui->T1DoubleSpinBox->hide();
    ui->T2DoubleSpinBox->hide();
    ui->X1DoubleSpinBox->hide();
    ui->Y1DoubleSpinBox->hide();
    ui->X2DoubleSpinBox->hide();
    ui->Y2DoubleSpinBox->hide();
    ui->angleDoubleSpinBox->hide();

    ui->T1Label->hide();
    ui->T2Label->hide();
    ui->X1Label->hide();
    ui->Y1Label->hide();
    ui->X2Label->hide();
    ui->Y2Label->hide();
    ui->angleLabel->hide();

    ui->H1DoubleSpinBox->hide();
    ui->H2DoubleSpinBox->hide();
    ui->H3DoubleSpinBox->hide();
    ui->R1DoubleSpinBox->hide();
    ui->R2DoubleSpinBox->hide();
    ui->W2DoubleSpinBox->hide();
    ui->W3DoubleSpinBox->hide();

    ui->H1Label->hide();
    ui->H2Label->hide();
    ui->H3Label->hide();
    ui->R1Label->hide();
    ui->R2Label->hide();
    ui->W2Label->hide();
    ui->W3Label->hide();

    ui->W1DoubleSpinBox->show();
    ui->W1Label->show();
    ui->formLayout_2->insertRow(1, ui->W1Label, ui->W1DoubleSpinBox);

    valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());
}

void WeldPropertiesWidget::show_v_weld_item(QMap<QString, double> &valueList)
{

    ui->T1DoubleSpinBox->hide();
    ui->T2DoubleSpinBox->hide();
    ui->X1DoubleSpinBox->hide();
    ui->Y1DoubleSpinBox->hide();
    ui->X2DoubleSpinBox->hide();
    ui->Y2DoubleSpinBox->hide();
    ui->angleDoubleSpinBox->hide();

    ui->T1Label->hide();
    ui->T2Label->hide();
    ui->X1Label->hide();
    ui->Y1Label->hide();
    ui->X2Label->hide();
    ui->Y2Label->hide();
    ui->angleLabel->hide();

    ui->H1DoubleSpinBox->show();
    ui->W2DoubleSpinBox->show();
    ui->H1Label->show();
    ui->W2Label->show();

    ui->H2DoubleSpinBox->hide();
    ui->H3DoubleSpinBox->hide();
    ui->R1DoubleSpinBox->hide();
    ui->R2DoubleSpinBox->hide();
    ui->W3DoubleSpinBox->hide();

    ui->H2Label->hide();
    ui->H3Label->hide();
    ui->R1Label->hide();
    ui->R2Label->hide();
    ui->W3Label->hide();

    ui->W1DoubleSpinBox->show();
    ui->W1Label->show();


    ui->formLayout_2->insertRow(1, ui->W1Label, ui->W1DoubleSpinBox);
    ui->formLayout_2->insertRow(2, ui->W2Label, ui->W2DoubleSpinBox);
    ui->formLayout_2->insertRow(3, ui->H1Label, ui->H1DoubleSpinBox);

    valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
    valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
    valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

}


void WeldPropertiesWidget::show_u_weld_item(QMap<QString, double> &valueList)
{
    ui->T1DoubleSpinBox->hide();
    ui->T2DoubleSpinBox->hide();
    ui->X1DoubleSpinBox->hide();
    ui->Y1DoubleSpinBox->hide();
    ui->X2DoubleSpinBox->hide();
    ui->Y2DoubleSpinBox->hide();
    ui->angleDoubleSpinBox->hide();

    ui->T1Label->hide();
    ui->T2Label->hide();
    ui->X1Label->hide();
    ui->Y1Label->hide();
    ui->X2Label->hide();
    ui->Y2Label->hide();
    ui->angleLabel->hide();

    ui->W2DoubleSpinBox->show();
    ui->H1DoubleSpinBox->show();
    ui->R1DoubleSpinBox->show();
    ui->W2Label->show();
    ui->H1Label->show();
    ui->R1Label->show();


    ui->H2DoubleSpinBox->hide();
    ui->H3DoubleSpinBox->hide();
    ui->R2DoubleSpinBox->hide();
    ui->W3DoubleSpinBox->hide();
    ui->H2Label->hide();
    ui->H3Label->hide();
    ui->R2Label->hide();
    ui->W3Label->hide();

    ui->W1DoubleSpinBox->show();
    ui->W1Label->show();

    ui->formLayout_2->insertRow(1, ui->W1Label, ui->W1DoubleSpinBox);
    ui->formLayout_2->insertRow(2, ui->W2Label, ui->W2DoubleSpinBox);
    ui->formLayout_2->insertRow(3, ui->H1Label, ui->H1DoubleSpinBox);
    ui->formLayout_2->insertRow(4, ui->R1Label, ui->R1DoubleSpinBox);

    valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
    valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
    valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
    valueList.insert(TAG_R1, ui->R1DoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

}


void WeldPropertiesWidget::show_vy_weld_item(QMap<QString, double> &valueList)
{
    ui->T1DoubleSpinBox->hide();
    ui->T2DoubleSpinBox->hide();
    ui->X1DoubleSpinBox->hide();
    ui->Y1DoubleSpinBox->hide();
    ui->X2DoubleSpinBox->hide();
    ui->Y2DoubleSpinBox->hide();
    ui->angleDoubleSpinBox->hide();

    ui->T1Label->hide();
    ui->T2Label->hide();
    ui->X1Label->hide();
    ui->Y1Label->hide();
    ui->X2Label->hide();
    ui->Y2Label->hide();
    ui->angleLabel->hide();

    ui->H1DoubleSpinBox->show();
    ui->H2DoubleSpinBox->show();
    ui->W2DoubleSpinBox->show();
    ui->W3DoubleSpinBox->show();

    ui->H1Label->show();
    ui->H2Label->show();
    ui->W2Label->show();
    ui->W3Label->show();

    ui->H3DoubleSpinBox->hide();
    ui->R1DoubleSpinBox->hide();
    ui->R2DoubleSpinBox->hide();

    ui->H3Label->hide();
    ui->R1Label->hide();
    ui->R2Label->hide();

    ui->W1DoubleSpinBox->show();
    ui->W1Label->show();

    ui->formLayout_2->insertRow(1, ui->W1Label, ui->W1DoubleSpinBox);
    ui->formLayout_2->insertRow(2, ui->W2Label, ui->W2DoubleSpinBox);
    ui->formLayout_2->insertRow(3, ui->W3Label, ui->W3DoubleSpinBox);
    ui->formLayout_2->insertRow(4, ui->H1Label, ui->H1DoubleSpinBox);
    ui->formLayout_2->insertRow(5, ui->H2Label, ui->H2DoubleSpinBox);

    valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
    valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
    valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
    valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
    valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());
}


void WeldPropertiesWidget::show_vv_weld_item(QMap<QString, double> &valueList)
{
    ui->T1DoubleSpinBox->hide();
    ui->T2DoubleSpinBox->hide();
    ui->X1DoubleSpinBox->hide();
    ui->Y1DoubleSpinBox->hide();
    ui->X2DoubleSpinBox->hide();
    ui->Y2DoubleSpinBox->hide();
    ui->angleDoubleSpinBox->hide();

    ui->T1Label->hide();
    ui->T2Label->hide();
    ui->X1Label->hide();
    ui->Y1Label->hide();
    ui->X2Label->hide();
    ui->Y2Label->hide();
    ui->angleLabel->hide();

    ui->H1DoubleSpinBox->show();
    ui->H2DoubleSpinBox->show();
    ui->W2DoubleSpinBox->show();
    ui->W3DoubleSpinBox->show();

    ui->H1Label->show();
    ui->H2Label->show();
    ui->W2Label->show();
    ui->W3Label->show();

    ui->H3DoubleSpinBox->hide();
    ui->R1DoubleSpinBox->hide();
    ui->R2DoubleSpinBox->hide();

    ui->H3Label->hide();
    ui->R1Label->hide();
    ui->R2Label->hide();

    ui->W1DoubleSpinBox->show();
    ui->W1Label->show();

    ui->formLayout_2->insertRow(1, ui->W1Label, ui->W1DoubleSpinBox);
    ui->formLayout_2->insertRow(2, ui->W2Label, ui->W2DoubleSpinBox);
    ui->formLayout_2->insertRow(3, ui->W3Label, ui->W3DoubleSpinBox);
    ui->formLayout_2->insertRow(4, ui->H1Label, ui->H1DoubleSpinBox);
    ui->formLayout_2->insertRow(5, ui->H2Label, ui->H2DoubleSpinBox);

    valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
    valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
    valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
    valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
    valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

}


void WeldPropertiesWidget::show_uu_weld_item(QMap<QString, double> &valueList)
{
    ui->T1DoubleSpinBox->hide();
    ui->T2DoubleSpinBox->hide();
    ui->X1DoubleSpinBox->hide();
    ui->Y1DoubleSpinBox->hide();
    ui->X2DoubleSpinBox->hide();
    ui->Y2DoubleSpinBox->hide();
    ui->angleDoubleSpinBox->hide();

    ui->T1Label->hide();
    ui->T2Label->hide();
    ui->X1Label->hide();
    ui->Y1Label->hide();
    ui->X2Label->hide();
    ui->Y2Label->hide();
    ui->angleLabel->hide();

    ui->H1DoubleSpinBox->show();
    ui->H2DoubleSpinBox->show();
    ui->W2DoubleSpinBox->show();
    ui->W3DoubleSpinBox->show();
    ui->R1DoubleSpinBox->show();
    ui->R2DoubleSpinBox->show();

    ui->H1Label->show();
    ui->H2Label->show();
    ui->W2Label->show();
    ui->W3Label->show();
    ui->R1Label->show();
    ui->R2Label->show();

    ui->H3DoubleSpinBox->hide();
    ui->H3Label->hide();

    ui->W1DoubleSpinBox->show();
    ui->W1Label->show();


    ui->formLayout_2->insertRow(1, ui->W1Label, ui->W1DoubleSpinBox);
    ui->formLayout_2->insertRow(2, ui->W2Label, ui->W2DoubleSpinBox);
    ui->formLayout_2->insertRow(3, ui->W3Label, ui->W3DoubleSpinBox);
    ui->formLayout_2->insertRow(4, ui->H1Label, ui->H1DoubleSpinBox);
    ui->formLayout_2->insertRow(5, ui->H2Label, ui->H2DoubleSpinBox);
    ui->formLayout_2->insertRow(6, ui->R1Label, ui->R1DoubleSpinBox);
    ui->formLayout_2->insertRow(7, ui->R2Label, ui->R2DoubleSpinBox);

    valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
    valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
    valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
    valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
    valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
    valueList.insert(TAG_R1, ui->R1DoubleSpinBox->value());
    valueList.insert(TAG_R2, ui->R2DoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());
}


void WeldPropertiesWidget::show_uv_weld_item(QMap<QString, double> &valueList)
{
    ui->T1DoubleSpinBox->hide();
    ui->T2DoubleSpinBox->hide();
    ui->X1DoubleSpinBox->hide();
    ui->Y1DoubleSpinBox->hide();
    ui->X2DoubleSpinBox->hide();
    ui->Y2DoubleSpinBox->hide();
    ui->angleDoubleSpinBox->hide();

    ui->T1Label->hide();
    ui->T2Label->hide();
    ui->X1Label->hide();
    ui->Y1Label->hide();
    ui->X2Label->hide();
    ui->Y2Label->hide();
    ui->angleLabel->hide();

    ui->H1DoubleSpinBox->show();
    ui->H2DoubleSpinBox->show();
    ui->W2DoubleSpinBox->show();
    ui->W3DoubleSpinBox->show();
    ui->R1DoubleSpinBox->show();
    ui->H1Label->show();
    ui->H2Label->show();
    ui->W2Label->show();
    ui->W3Label->show();
    ui->R1Label->show();


    ui->H3DoubleSpinBox->hide();
    ui->R2DoubleSpinBox->hide();
    ui->H3Label->hide();
    ui->R2Label->hide();

    ui->W1DoubleSpinBox->show();
    ui->W1Label->show();

    ui->formLayout_2->insertRow(1, ui->W1Label, ui->W1DoubleSpinBox);
    ui->formLayout_2->insertRow(2, ui->W2Label, ui->W2DoubleSpinBox);
    ui->formLayout_2->insertRow(3, ui->W3Label, ui->W3DoubleSpinBox);
    ui->formLayout_2->insertRow(4, ui->H1Label, ui->H1DoubleSpinBox);
    ui->formLayout_2->insertRow(5, ui->H2Label, ui->H2DoubleSpinBox);
    ui->formLayout_2->insertRow(6, ui->R1Label, ui->R1DoubleSpinBox);

    valueList.insert(TAG_W1, ui->W1DoubleSpinBox->value());
    valueList.insert(TAG_W2, ui->W2DoubleSpinBox->value());
    valueList.insert(TAG_W3, ui->W3DoubleSpinBox->value());
    valueList.insert(TAG_H1, ui->H1DoubleSpinBox->value());
    valueList.insert(TAG_H2, ui->H2DoubleSpinBox->value());
    valueList.insert(TAG_R1, ui->R1DoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());
}


void WeldPropertiesWidget::show_tky_weld_item(QMap<QString, double> &valueList)
{

    ui->H1DoubleSpinBox->hide();
    ui->H2DoubleSpinBox->hide();
    ui->W1DoubleSpinBox->hide();
    ui->W2DoubleSpinBox->hide();
    ui->W3DoubleSpinBox->hide();
    ui->R1DoubleSpinBox->hide();
    ui->H3DoubleSpinBox->hide();
    ui->R2DoubleSpinBox->hide();

    ui->H1Label->hide();
    ui->H2Label->hide();
    ui->W1Label->hide();
    ui->W2Label->hide();
    ui->W3Label->hide();
    ui->R1Label->hide();
    ui->H3Label->hide();
    ui->R2Label->hide();


    ui->T1DoubleSpinBox->show();
    ui->T2DoubleSpinBox->show();
    ui->X1DoubleSpinBox->show();
    ui->Y1DoubleSpinBox->show();
    ui->X2DoubleSpinBox->show();
    ui->Y2DoubleSpinBox->show();
    ui->angleDoubleSpinBox->show();

    ui->T1Label->show();
    ui->T2Label->show();
    ui->X1Label->show();
    ui->Y1Label->show();
    ui->X2Label->show();
    ui->Y2Label->show();
    ui->angleLabel->show();


    ui->formLayout_2->insertRow(1, ui->T1Label, ui->T1DoubleSpinBox);
    ui->formLayout_2->insertRow(2, ui->T2Label, ui->T2DoubleSpinBox);
    ui->formLayout_2->insertRow(3, ui->X1Label, ui->X1DoubleSpinBox);
    ui->formLayout_2->insertRow(4, ui->Y1Label, ui->Y1DoubleSpinBox);
    ui->formLayout_2->insertRow(5, ui->X2Label, ui->X2DoubleSpinBox);
    ui->formLayout_2->insertRow(6, ui->Y2Label, ui->Y2DoubleSpinBox);
    ui->formLayout_2->insertRow(7, ui->angleLabel, ui->angleDoubleSpinBox);

    valueList.insert(TAG_T1, ui->T1DoubleSpinBox->value());
    valueList.insert(TAG_T2, ui->T2DoubleSpinBox->value());
    valueList.insert(TAG_X1, ui->X1DoubleSpinBox->value());
    valueList.insert(TAG_Y1, ui->Y1DoubleSpinBox->value());
    valueList.insert(TAG_X2, ui->X2DoubleSpinBox->value());
    valueList.insert(TAG_Y2, ui->Y2DoubleSpinBox->value());
    valueList.insert(TAG_ANGLE, ui->angleDoubleSpinBox->value());
    valueList.insert(TAG_TYPE, ui->weldTypeComboBox->currentIndex());

}


void WeldPropertiesWidget::reset_value()
{
    disconnect(ui->H1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->H2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->H3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->R1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->R2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->W1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->W2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->W3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    disconnect(ui->T1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->T2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->X1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->Y1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->X2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->Y2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    ui->H1DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->H1DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->H1DoubleSpinBox->setValue(0.00);

    ui->H2DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->H2DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->H2DoubleSpinBox->setValue(0.00);

    ui->H3DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->H3DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->H3DoubleSpinBox->setValue(0.0);

    ui->R1DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->R1DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->R1DoubleSpinBox->setValue(0.00);

    ui->R2DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->R2DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->R2DoubleSpinBox->setValue(0.00);

    ui->W1DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->W1DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->W1DoubleSpinBox->setValue(0.00);

    ui->W2DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->W2DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->W2DoubleSpinBox->setValue(0.00);

    ui->W3DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->W3DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->W3DoubleSpinBox->setValue(0.00);

    ui->H1DoubleSpinBox->setMaximum(m_thickness);
    ui->H2DoubleSpinBox->setMaximum(m_thickness);
    ui->H3DoubleSpinBox->setMaximum(m_thickness);

    if(ui->weldTypeComboBox->currentIndex() == DplWeld::U_Weld) {
        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->R1DoubleSpinBox->setValue(2.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::UV_Weld) {

        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->W3DoubleSpinBox->setValue(2.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->H2DoubleSpinBox->setValue(3.0);
        ui->R1DoubleSpinBox->setValue(2.0);

        ui->W3DoubleSpinBox->setMinimum(ui->W3DoubleSpinBox->value());

    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::UU_Weld) {

        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->W3DoubleSpinBox->setValue(2.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->H2DoubleSpinBox->setValue(3.0);
        ui->R1DoubleSpinBox->setValue(2.0);
        ui->R2DoubleSpinBox->setValue(2.0);

        ui->W1DoubleSpinBox->setMinimum(1.0);
        ui->W3DoubleSpinBox->setMinimum(1.0);
        ui->R1DoubleSpinBox->setMaximum(2.0);
        ui->R2DoubleSpinBox->setMaximum(2.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::VV_Weld) {
        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->W3DoubleSpinBox->setValue(2.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->H2DoubleSpinBox->setValue(3.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::VY_Weld) {
        ui->W1DoubleSpinBox->setValue(5.0);
        ui->W2DoubleSpinBox->setValue(2.0);
        ui->W3DoubleSpinBox->setValue(1.0);
        ui->H1DoubleSpinBox->setValue(2.0);
        ui->H2DoubleSpinBox->setValue(2.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::V_Weld) {
        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->H1DoubleSpinBox->setValue(3.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::TKY_Weld) {
        ui->T1DoubleSpinBox->setValue(30.0);
        ui->T2DoubleSpinBox->setValue(20.0);
        ui->X1DoubleSpinBox->setValue(5.0);
        ui->Y1DoubleSpinBox->setValue(5.0);
        ui->X2DoubleSpinBox->setValue(5.0);
        ui->Y2DoubleSpinBox->setValue(5.0);
        ui->angleDoubleSpinBox->setValue(90.0);
    }

    connect(ui->H1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->H2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->H3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->R1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->R2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    connect(ui->T1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->T2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->X1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->Y1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->X2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->Y2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}

void WeldPropertiesWidget::set_value(const QMap<QString, double> &valueList)
{
    disconnect(ui->H1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->H2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->H3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->R1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->R2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->W1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->W2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->W3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    disconnect(ui->T1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->T2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->X1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->Y1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->X2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->Y2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    disconnect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    ui->H1DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->H1DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->H1DoubleSpinBox->setValue(0.00);

    ui->H2DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->H2DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->H2DoubleSpinBox->setValue(0.00);

    ui->H3DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->H3DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->H3DoubleSpinBox->setValue(0.0);

    ui->R1DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->R1DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->R1DoubleSpinBox->setValue(0.00);

    ui->R2DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->R2DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->R2DoubleSpinBox->setValue(0.00);

    ui->W1DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->W1DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->W1DoubleSpinBox->setValue(0.00);

    ui->W2DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->W2DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->W2DoubleSpinBox->setValue(0.00);

    ui->W3DoubleSpinBox->setMinimum(MIN_SIZE);
    ui->W3DoubleSpinBox->setMaximum(MAX_SIZE);
    ui->W3DoubleSpinBox->setValue(0.00);

    ui->H1DoubleSpinBox->setMaximum(valueList.value(TAG_THICKNESS));
    ui->H2DoubleSpinBox->setMaximum(valueList.value(TAG_THICKNESS));
    ui->H3DoubleSpinBox->setMaximum(valueList.value(TAG_THICKNESS));

    m_thickness = valueList.value(TAG_THICKNESS);

    if(ui->weldTypeComboBox->currentIndex() == DplWeld::U_Weld) {
        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->R1DoubleSpinBox->setValue(2.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::UV_Weld) {

        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->W3DoubleSpinBox->setValue(2.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->H2DoubleSpinBox->setValue(3.0);
        ui->R1DoubleSpinBox->setValue(2.0);

        ui->W3DoubleSpinBox->setMinimum(ui->W3DoubleSpinBox->value());

    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::UU_Weld) {

        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->W3DoubleSpinBox->setValue(2.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->H2DoubleSpinBox->setValue(3.0);
        ui->R1DoubleSpinBox->setValue(2.0);
        ui->R2DoubleSpinBox->setValue(2.0);

        ui->W1DoubleSpinBox->setMinimum(1.0);
        ui->W3DoubleSpinBox->setMinimum(1.0);
        ui->R1DoubleSpinBox->setMaximum(2.0);
        ui->R2DoubleSpinBox->setMaximum(2.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::VV_Weld) {
        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->W3DoubleSpinBox->setValue(2.0);
        ui->H1DoubleSpinBox->setValue(3.0);
        ui->H2DoubleSpinBox->setValue(3.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::VY_Weld) {
        ui->W1DoubleSpinBox->setValue(5.0);
        ui->W2DoubleSpinBox->setValue(2.0);
        ui->W3DoubleSpinBox->setValue(1.0);
        ui->H1DoubleSpinBox->setValue(2.0);
        ui->H2DoubleSpinBox->setValue(2.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::V_Weld) {
        ui->W1DoubleSpinBox->setValue(2.0);
        ui->W2DoubleSpinBox->setValue(1.0);
        ui->H1DoubleSpinBox->setValue(3.0);
    } else if(ui->weldTypeComboBox->currentIndex() == DplWeld::TKY_Weld) {
        ui->T1DoubleSpinBox->setValue(30.0);
        ui->T2DoubleSpinBox->setValue(20.0);
        ui->X1DoubleSpinBox->setValue(5.0);
        ui->Y1DoubleSpinBox->setValue(5.0);
        ui->X2DoubleSpinBox->setValue(5.0);
        ui->Y2DoubleSpinBox->setValue(5.0);
        ui->angleDoubleSpinBox->setValue(90.0);
    }

    connect(ui->H1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->H2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->H3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->R1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->R2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->W3DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));

    connect(ui->T1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->T2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->X1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->Y1DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->X2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->Y2DoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
    connect(ui->angleDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slot_weld_info_changed(double)));
}



void WeldPropertiesWidget::check_vv_weld_properties_limit(const QDoubleSpinBox *current, double value)
{
    if(current->objectName() == ui->W1DoubleSpinBox->objectName()) {
        /* 设置W2最大值不克超过W1、W3中的最小值 */
        if(value < ui->W3DoubleSpinBox->value()) {
            ui->W2DoubleSpinBox->setMaximum(value);
        } else {
            ui->W2DoubleSpinBox->setMaximum(ui->W3DoubleSpinBox->value());
        }

    } else if(current->objectName() == ui->W2DoubleSpinBox->objectName()) {

        /* 设置W1、W3中的最小值，不能小于W2值 */
        ui->W1DoubleSpinBox->setMinimum(value);
        ui->W3DoubleSpinBox->setMinimum(value);

    } else if(current->objectName() == ui->W3DoubleSpinBox->objectName()) {

        /* 设置W2最大值不克超过W1、W3中的最小值 */
        if(value < ui->W1DoubleSpinBox->value()) {
            ui->W2DoubleSpinBox->setMaximum(value);
        } else {
            ui->W2DoubleSpinBox->setMaximum(ui->W1DoubleSpinBox->value());
        }

    } else if(current->objectName() == ui->H1DoubleSpinBox->objectName()) {

         ui->H2DoubleSpinBox->setMaximum(m_thickness - value);

    } else if(current->objectName() == ui->H2DoubleSpinBox->objectName()) {

        ui->H1DoubleSpinBox->setMaximum(m_thickness - value);
    }
}


void WeldPropertiesWidget::check_u_weld_properties_limit(const QDoubleSpinBox *current, double value)
{
    if(current->objectName() == ui->W1DoubleSpinBox->objectName()) {

        if((DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::U_Weld
                || (DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::UV_Weld) {

            ui->W2DoubleSpinBox->setMaximum(value - 0.01);

        } else if((DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::UU_Weld) {

            /* 计算 W1与W3哪个比较小，用于设置W2的最大值 */
            double tmpValue = MIN(ui->W1DoubleSpinBox->value(), ui->W3DoubleSpinBox->value());
            ui->W2DoubleSpinBox->setMaximum(tmpValue - 0.01);
        }

        /* 求W2与H1构成的斜边，若斜边小于alue，则设置成R1的最大值。 */
        double hypotenuse = sqrt(pow(ui->W2DoubleSpinBox->value(), 2) + pow(ui->H1DoubleSpinBox->value(), 2));
        qDebug() << "[" << __FUNCTION__ << "]" << " hypotenuse = " << hypotenuse << " change W1 set max R1 ";

        if(hypotenuse < value) {
            ui->R1DoubleSpinBox->setMaximum(hypotenuse);
        } else {
            ui->R1DoubleSpinBox->setMaximum(value);
        }

    } else if(current->objectName() == ui->W2DoubleSpinBox->objectName()) {

        ui->W1DoubleSpinBox->setMinimum(value + 0.01); /* W1 永远要大于 W2，当前精度为两位，故减0.01 */

        double hypotenuse = sqrt(pow(ui->W2DoubleSpinBox->value(), 2) + pow(ui->H1DoubleSpinBox->value(), 2));
        qDebug() << "[" << __FUNCTION__ << "]" << " hypotenuse = " << hypotenuse << " change W2 set max R1 ";

        if(hypotenuse < ui->W1DoubleSpinBox->value()) {
            ui->R1DoubleSpinBox->setMaximum(hypotenuse);
        } else {
            ui->R1DoubleSpinBox->setMaximum(ui->W1DoubleSpinBox->value());
        }

        if((DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::UU_Weld) {

            ui->W3DoubleSpinBox->setMinimum(value + 0.01); /* W3 永远要大于 W2，当前精度为两位，故减0.01 */

            hypotenuse = sqrt(pow(ui->W3DoubleSpinBox->value(), 2) + pow(ui->H2DoubleSpinBox->value(), 2));

            if(hypotenuse < ui->W3DoubleSpinBox->value()) {
                ui->R2DoubleSpinBox->setMaximum(hypotenuse);
            } else {
                ui->R2DoubleSpinBox->setMaximum(ui->W3DoubleSpinBox->value());
            }
        }
    }
    else if(current->objectName() == ui->R1DoubleSpinBox->objectName()) {

        if((DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::U_Weld) {

            ui->W2DoubleSpinBox->setMaximum(value - 0.01);
            ui->W1DoubleSpinBox->setMinimum(value);

        } else if ((DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::UU_Weld) {

            ui->W1DoubleSpinBox->setMinimum(value);

            if(value < ui->R2DoubleSpinBox->value()) {
                ui->W2DoubleSpinBox->setMaximum(value - 0.01);
            }

        } else if((DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::UV_Weld) {

            ui->W2DoubleSpinBox->setMaximum(value - 0.01);
            ui->W1DoubleSpinBox->setMinimum(value);
        }

     } else if(current->objectName() == ui->H1DoubleSpinBox->objectName()) {

        double hypotenuse = sqrt(pow(ui->W2DoubleSpinBox->value(), 2) + pow(ui->H1DoubleSpinBox->value(), 2));

        if(hypotenuse < ui->W1DoubleSpinBox->value()) {
            ui->R1DoubleSpinBox->setMaximum(hypotenuse);
        } else {
            ui->R1DoubleSpinBox->setMaximum(ui->W1DoubleSpinBox->value());
        }

        if((DplWeld::WeldType)ui->weldTypeComboBox->currentIndex() == DplWeld::UU_Weld) {

            hypotenuse = sqrt(pow(ui->W2DoubleSpinBox->value(), 2) + pow(ui->H2DoubleSpinBox->value(), 2));

            if(hypotenuse < ui->W3DoubleSpinBox->value()) {
                ui->R2DoubleSpinBox->setMaximum(hypotenuse);
            } else {
                ui->R2DoubleSpinBox->setMaximum(ui->W3DoubleSpinBox->value());
            }

            ui->H2DoubleSpinBox->setMaximum(m_thickness - value);
        }
    } else if(current->objectName() == ui->W3DoubleSpinBox->objectName()) {

        double tmpValue = MIN(ui->W1DoubleSpinBox->value(), ui->W3DoubleSpinBox->value());
        ui->W2DoubleSpinBox->setMaximum(tmpValue - 0.01);

        /* 求W3与H2构成的斜边，若斜边小于value，则设置成R2的最大值。 */
        double hypotenuse = sqrt(pow(ui->W3DoubleSpinBox->value(), 2) + pow(ui->H2DoubleSpinBox->value(), 2));

        if(hypotenuse < value) {
            ui->R2DoubleSpinBox->setMaximum(hypotenuse);
        } else {
            ui->R2DoubleSpinBox->setMaximum(value);
        }

    } else if(current->objectName() == ui->H2DoubleSpinBox->objectName()) {

        double hypotenuse = sqrt(pow(ui->W2DoubleSpinBox->value(), 2) + pow(ui->H2DoubleSpinBox->value(), 2));

        if(hypotenuse < ui->W3DoubleSpinBox->value()) {
            ui->R2DoubleSpinBox->setMaximum(hypotenuse);
        } else {
            ui->R2DoubleSpinBox->setMaximum(ui->W3DoubleSpinBox->value());
        }

        ui->H1DoubleSpinBox->setMaximum(m_thickness - value);
        ui->H2DoubleSpinBox->setMaximum(m_thickness - ui->H1DoubleSpinBox->value());

    } else if(current->objectName() == ui->R2DoubleSpinBox->objectName()) {

        ui->W3DoubleSpinBox->setMinimum(value);

        if(value < ui->R1DoubleSpinBox->value()) {
            ui->W2DoubleSpinBox->setMaximum(value - 0.01);
        }
    }
}

