#ifndef __CURSORS_MENU_H__
#define __CURSORS_MENU_H__

#include "base_menu.h"

namespace DplMeasurementMenu {

class CursorsMenu : public BaseMenu
{
    Q_OBJECT
public:
    CursorsMenu(Ui::BaseMenu *ui, QObject *parent);

private:
    MenuItem *m_bSrItem;
    MenuItem *m_bSmItem;
    MenuItem *m_bUrItem;
    MenuItem *m_bUmItem;

    MenuItem *m_cSrItem;
    MenuItem *m_cSmItem;
    MenuItem *m_cIrItem;
    MenuItem *m_cImItem;

    MenuItem *m_angleItem;

    void show_a_scan();
    void show_b_scan();
    void show_c_scan();
    void show_s_scan();

private slots:
    void do_selections_changed(int index);
};

}
#endif // __CURSORS_MENU_H__
