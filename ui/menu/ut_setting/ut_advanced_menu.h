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

protected slots:
    void update(const DplDevice::GroupPointer &group);
    void update_scaleFactorItem();

    void do_eightPercentItem_clicked();
    void do_dbRefItem_changed(int index);
    void do_pointQtyItem(int index);

private:
    LabelMenuItem *m_eightPercentItem;
    ComboMenuItem *m_dbRefItem;
    LabelMenuItem *m_scaleFactorItem;
    SpinMenuItem *m_sumGainItem;
    ComboMenuItem *m_pointQtyItem;
    SpinMenuItem *m_userDefItem;

    DplUt::SamplePointer m_sample;
};

}
#endif // __UT_ADVANCED_MENU_H__
