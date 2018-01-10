/**
 * @file preference_menu.h
 * @brief Preference Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#ifndef __PREFERENCE_MENU_H__
#define __PREFERENCE_MENU_H__

#include "../base_menu.h"
#include "mcu/mcu.h"

namespace DplPreferenceMenu {

class PreferenceMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit PreferenceMenu(QWidget *parent);
    ~PreferenceMenu();

private:
    SpinMenuItem *m_brightItem;
    SpinMenuItem *m_opacityItem;
    ComboMenuItem *m_languageItem;
    ComboMenuItem *m_startingPageItem;
    ComboMenuItem *m_gatemodeItem;
    LabelMenuItem *m_deployItem;

    Mcu *m_mcu;

signals:
    void opacity_changed(double value);

private slots:
    void set_brightness(double value);
    void do_deployItem_changed();
    void do_gatemodeItem_value_changed(int val);

protected:
    void changeEvent(QEvent *event);
private:
    void retranslate_ui();

};

}
#endif // PREFERENCEMENU_H
