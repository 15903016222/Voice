/**
 * @file pulser_menu.h
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#ifndef __PULSER_MENU_H__
#define __PULSER_MENU_H__

#include "base_menu.h"

class PulserMenu : public BaseMenu
{
    Q_OBJECT
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
