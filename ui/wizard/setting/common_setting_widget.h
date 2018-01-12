/**
 * @file common_setting_widget.h
 * @brief 公共属性设置Widget，用于保存当前设置的类型。
 */

#ifndef __COMMON_SETTING_WIDGET_H__
#define __COMMON_SETTING_WIDGET_H__

#include <QWidget>
#include "wizard_setting.h"

namespace Ui {
class CommonSettingWidget;
}

class CommonSettingWidget : public QWidget
{
    Q_OBJECT

public:
    enum E_DETECT_MODE {
        TOFD = 0,
        PE
    };

public:
    explicit CommonSettingWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~CommonSettingWidget();

    /**
     * @brief set_mod
     * @param mode      检测类型
     */
    void set_mode(E_DETECT_MODE mode);

protected:
    WizardSetting::E_WIZARD_TYPE    m_type;
    E_DETECT_MODE                   m_mode;

    virtual void initModeWidget();

};

#endif // __COMMON_SETTING_WIDGET_H__
