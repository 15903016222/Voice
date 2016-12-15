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
    UtAdvancedMenu(Ui::SubMenu *ui, QObject *parent);
    void show();
    void hide();

private:
    QStringList m_pointQtyList;

    void eight_percent_item();
    void db_ref_item();
    void point_number_item();
    void scale_factor_item();
    void sum_gain_item();
};

#endif // __UT_ADVANCED_MENU_H__
