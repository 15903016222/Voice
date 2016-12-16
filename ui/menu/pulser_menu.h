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
    explicit PulserMenu(Ui::SubMenu *ui, QObject *parent);
    ~PulserMenu();

    void show();
    void hide();

private:
    MenuItem *m_txrxItem;
    MenuItem *m_pulserItem;
    MenuItem *m_voltagesItem;
    MenuItem *m_pwItem;
    MenuItem *m_prfItem;
    MenuItem *m_noneItem;

    QStringList m_txRxMode;
    QStringList m_voltages;
    QStringList m_prfs;
};

#endif // __PULSER_MENU_H__
