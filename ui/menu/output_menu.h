#ifndef __OUTPUT_MENU_H__
#define __OUTPUT_MENU_H__

#include "base_menu.h"

class OutputMenu : public BaseMenu
{
public:
    OutputMenu(Ui::SubMenu *ui, QObject *parent);

    void show();
    void hide();

private:
    QStringList m_outputs;
    QStringList m_sounds;
    QStringList m_datas;

    void output_item();
    void sound_item();
    void delay_item();
    void hold_time_item();
    void group_item();
    void data_item();
};

#endif // OUTPUTMENU_H
