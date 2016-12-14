#ifndef __PULSER_MENU_H__
#define __PULSER_MENU_H__

#include "base_menu.h"

class PulserMenu : public BaseMenu
{
public:
    PulserMenu(Ui::SubMenu *ui, QObject *parent);
    void show();
    void hide();

private:
    QStringList m_txRxMode;
    QStringList m_voltages;
    QStringList m_prfs;

    void txrx_item();
    void pulser_item();
    void voltage_item();
    void pw_item();
    void prf_item();
};

#endif // __PULSER_MENU_H__
