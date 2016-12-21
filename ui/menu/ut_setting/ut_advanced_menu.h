/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#ifndef __UT_ADVANCED_MENU_H__
#define __UT_ADVANCED_MENU_H__

#include "base_menu.h"

class UtAdvancedMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit UtAdvancedMenu(Ui::BaseMenu *ui, QObject *parent);
    ~UtAdvancedMenu();

    void show();
    void hide();

private:
    MenuItem *m_eightPercentItem;
    MenuItem *m_dbRefItem;
    MenuItem *m_pointQtyItem;
    MenuItem *m_scaleFactorItem;
    MenuItem *m_sumGainItem;
};

#endif // __UT_ADVANCED_MENU_H__