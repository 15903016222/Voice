/**
 * @file output_menu.h
 * @brief Gate/Curves ouput menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __OUTPUT_MENU_H__
#define __OUTPUT_MENU_H__

#include "base_menu.h"

class OutputMenu : public BaseMenu
{
    Q_OBJECT
public:
    OutputMenu(Ui::SubMenu *ui, QObject *parent);
};

#endif // OUTPUTMENU_H
