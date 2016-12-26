#ifndef __CURSORS_MENU_H__
#define __CURSORS_MENU_H__

#include "base_menu.h"

namespace DplMeasurementMenu {

class CursorsMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit CursorsMenu(Ui::BaseMenu *ui, QObject *parent);
    ~CursorsMenu();

    void show();
    void hide();

private:
    ComboMenuItem *m_selectionItem;

    MenuItem *m_rItem;      /* %(r) */
    MenuItem *m_mItem;      /* %(m) */

    MenuItem *m_urItem;     /* U(r) */
    MenuItem *m_umItem;     /* U(m) */

    MenuItem *m_srItem;     /* S(r) */
    MenuItem *m_smItem;     /* S(m) */

    MenuItem *m_irItem;     /* I(r) */
    MenuItem *m_imItem;     /* I(m) */

    MenuItem *m_angelItem;

    void show_a_scan();
    void hide_a_scan();

    void show_b_scan();
    void hide_b_scan();

    void show_c_scan();
    void hide_c_scan();

    void show_s_scan();
    void hide_s_scan();

private slots:
    void do_selections_changed(int index);
};

}
#endif // __CURSORS_MENU_H__
