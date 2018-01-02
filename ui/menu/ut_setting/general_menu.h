/**
 * @file general_menu.h
 * @brief Ut Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#ifndef __GENERAL_MENU_H__
#define __GENERAL_MENU_H__

#include "../base_menu.h"

#include <device/device.h>

class GainMenuItem;
class StartMenuItem;
class RangeMenuItem;
class VelocityMenuItem;
class DelayMenuItem;
class UnitMenuItem;

namespace DplUtSettingMenu {

class GeneralMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GeneralMenu(QWidget *parent = 0);

private:
    GainMenuItem *m_gainItem;
    StartMenuItem *m_startItem;
    RangeMenuItem *m_rangeItem;
    VelocityMenuItem *m_velocityItem;
    DelayMenuItem *m_wedgeDelayItem;
    UnitMenuItem *m_utUnitItem;
};

}
#endif // GENERALMENU_H
