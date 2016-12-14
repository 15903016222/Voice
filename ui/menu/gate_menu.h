#ifndef __GATE_MENU_H__
#define __GATE_MENU_H__

#include "base_menu.h"

class GateMenu : public BaseMenu
{
public:
    GateMenu(Ui::SubMenu *ui, QObject *parent);

    void show();
    void hide();

private:
    QStringList m_gates;
    QStringList m_synchros;
    QStringList m_measureModes;

    void gate_item();
    void start_item();
    void width_item();
    void threshold_item();
    void synchro_item();
    void measure_mode_item();
};

#endif // GATEMENU_H
