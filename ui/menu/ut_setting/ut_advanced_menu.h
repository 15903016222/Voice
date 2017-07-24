/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#ifndef __UT_ADVANCED_MENU_H__
#define __UT_ADVANCED_MENU_H__

#include "../base_menu.h"

#include <device/device.h>

namespace DplUtSettingMenu {

class UtAdvancedMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit UtAdvancedMenu(QWidget *parent);
    ~UtAdvancedMenu();

    void show();
    void hide();

private:
    LabelMenuItem *m_eightPercentItem;
    ComboMenuItem *m_dbRefItem;
    ComboMenuItem *m_pointQtyItem;
    LabelMenuItem *m_scaleFactorItem;
    SpinMenuItem *m_sumGainItem;

    DplUt::SamplePointer m_sample;

private slots:
    void update(const DplDevice::GroupPointer &group);
    void update_scale_factor_item();

};

}
#endif // __UT_ADVANCED_MENU_H__
