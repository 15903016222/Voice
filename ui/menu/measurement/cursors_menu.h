#ifndef __CURSORS_MENU_H__
#define __CURSORS_MENU_H__

#include "../base_menu.h"

namespace DplMeasurementMenu {

class CursorsMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit CursorsMenu(QWidget *parent);
    ~CursorsMenu();

private:
    ComboMenuItem *m_selectionItem;

    SpinMenuItem *m_rItem;      /* %(r) */
    SpinMenuItem *m_mItem;      /* %(m) */

    SpinMenuItem *m_urItem;     /* U(r) */
    SpinMenuItem *m_umItem;     /* U(m) */

    SpinMenuItem *m_srItem;     /* S(r) */
    SpinMenuItem *m_smItem;     /* S(m) */

    SpinMenuItem *m_irItem;     /* I(r) */
    SpinMenuItem *m_imItem;     /* I(m) */

    SpinMenuItem *m_angelItem;

    void show_scan();

    void show_a_scan();
    void hide_a_scan();

    void show_b_scan();
    void hide_b_scan();

    void show_c_scan();
    void hide_c_scan();

    void show_s_scan();
    void hide_s_scan();

private slots:
    void do_selectionItem_changed(int index);
};

}
#endif // __CURSORS_MENU_H__
