/**
 * @file delay_properties_widget.h
 * @brief 延迟属性设置Widget，用于设置延时的相关属性数据。
 */

#ifndef __DELAY_PROPERTIES_WIDGET_H__
#define __DELAY_PROPERTIES_WIDGET_H__

#include <QWidget>
#include "wizard_setting.h"

namespace Ui {
class DelayPropertiesWidget;
}

class DelayPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DelayPropertiesWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~DelayPropertiesWidget();

private:
    Ui::DelayPropertiesWidget *ui;
};

#endif // __DELAY_PROPERTIES_WIDGET_H__
