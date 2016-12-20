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
    explicit OutputMenu(Ui::BaseMenu *ui, QObject *parent);
    ~OutputMenu();

    void show();
    void hide();

private:
    MenuItem *m_outputItem;
    MenuItem *m_soundItem;
    MenuItem *m_delayItem;
    MenuItem *m_holdTimeItem;
    MenuItem *m_groupItem;
    MenuItem *m_dataItem;
};

#endif // __OUTPUT_MENU_H__
