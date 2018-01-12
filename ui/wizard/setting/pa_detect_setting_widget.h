/**
 * @file pa_detect_setting_widget.h
 * @brief PA检测设置Widget，提供PA检测属性设置。
 */

#ifndef __DETECT_SETTING_WIDGET_H__
#define __DETECT_SETTING_WIDGET_H__

#include <QWidget>
#include "wizard_setting.h"

namespace Ui {
class PADetectSettingWidget;
}

class PADetectSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PADetectSettingWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~PADetectSettingWidget();

private slots:
    void do_checkBox_pressed();

private:
    Ui::PADetectSettingWidget *ui;
};

#endif // __DETECT_SETTING_WIDGET_H__
