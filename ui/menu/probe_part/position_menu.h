/**
 * @file position_menu.h
 * @brief Postion Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#ifndef __POSITION_MENU_H__
#define __POSITION_MENU_H__

#include "base_menu.h"

namespace DplProbeMenu {

class PositionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit PositionMenu(Ui::BaseMenu *ui, QObject *parent);
    ~PositionMenu();

    void show();
    void hide();

private:
    SpinMenuItem m_scanOffsetItem;
    SpinMenuItem m_indexOffsetItem;
    ComboMenuItem m_skewItem;
};

}

#endif // __POSITION_MENU_H__
