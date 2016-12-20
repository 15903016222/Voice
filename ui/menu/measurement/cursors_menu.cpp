#include "cursors_menu.h"

namespace DplMeasurementMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin
};

CursorsMenu::CursorsMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Selection menu item */
    QStringList selectionList;
    selectionList.append(tr("A-Scan"));
    selectionList.append(tr("B-Scan"));
    selectionList.append(tr("C-Scan"));
    selectionList.append(tr("S-Scan"));
    m_menuItem[0]->set(tr("Selection"), selectionList);
    connect(m_menuItem[0], SIGNAL(value_changed(int)), this, SLOT(do_selections_changed(int)));
    /* %(r) menu item */
    m_menuItem[1]->set(tr("%(r)"), "%", 0, 100, 1);
    /* %(m) menu item */
    m_menuItem[2]->set(tr("%(m)"), "%", 0, 100, 1);
    /* U(r) menu item */
    m_menuItem[3]->set(tr("U(r)"), "mm", 0, 2000, 2);
    /* U(m) menu item */
    m_menuItem[4]->set(tr("U(m)"), "mm", 0, 2000, 2);
    BaseMenu::show();
    ui->menuItem5->layout()->removeWidget(m_menuItem[5]);
    m_menuItem[5]->hide();

}

void CursorsMenu::show_a_scan()
{
    /* %(r) menu item */
    m_menuItem[1]->set(tr("%(r)"), "%", 0, 100, 1);
    /* %(m) menu item */
    m_menuItem[2]->set(tr("%(m)"), "%", 0, 100, 1);
    /* U(r) menu item */
    m_menuItem[3]->set(tr("U(r)"), "mm", 0, 2000, 2);
    /* U(m) menu item */
    m_menuItem[4]->set(tr("U(m)"), "mm", 0, 2000, 2);
    BaseMenu::show();
    ui->menuItem5->layout()->removeWidget(m_menuItem[5]);
    m_menuItem[5]->hide();
}

void CursorsMenu::show_b_scan()
{
    /* S(r) menu item */
    m_menuItem[1]->set(tr("S(r)"), "s", 0, 10000, 1);
    /* S(m) menu item */
    m_menuItem[2]->set(tr("S(m)"), "s", 0, 10000, 1);
    /* U(r) menu item */
    m_menuItem[3]->set(tr("U(r)"), "mm", 0, 2000, 2);
    /* U(m) menu item */
    m_menuItem[4]->set(tr("U(m)"), "mm", 0, 2000, 2);

    BaseMenu::show();
    ui->menuItem5->layout()->removeWidget(m_menuItem[5]);
    m_menuItem[5]->hide();
}

void CursorsMenu::show_c_scan()
{
    /* S(r) menu item */
    m_menuItem[1]->set(tr("S(r)"), "s", 0, 10000, 1);

    /* S(m) menu item */
    m_menuItem[2]->set(tr("S(m)"), "s", 0, 10000, 1);

    /* I(r) menu item */
    m_menuItem[3]->set(tr("I(r)"), "mm", 0, 2000, 1);

    /* I(m) menu item */
    m_menuItem[4]->set(tr("I(m)"), "mm", 0, 2000, 1);
    BaseMenu::show();
    ui->menuItem5->layout()->removeWidget(m_menuItem[5]);
    m_menuItem[5]->hide();
}

void CursorsMenu::show_s_scan()
{
    /* Angle menu item */
    m_menuItem[1]->set(tr("Angle"), "°", 25, 75, 0);

    /* U(r) menu item */
    m_menuItem[2]->set(tr("U(r)"), "mm", 0, 2000, 2);

    /* U(m) menu item */
    m_menuItem[3]->set(tr("U(m)"), "mm", 0, 2000, 2);

    /* I(r) menu item */
    m_menuItem[4]->set(tr("I(r)"), "mm", 0, 2000, 1);

    /* I(m) menu item */
    m_menuItem[5]->set(tr("I(m)"), "mm", 0, 2000, 1);

    BaseMenu::show();
}

void CursorsMenu::do_selections_changed(int index)
{
    BaseMenu::hide();
    switch (index) {
    case 0: /* A-Scan */
        show_a_scan();
        break;
    case 1: /* B-Scan */
        show_b_scan();
        break;
    case 2: /* C-Scan */
        show_c_scan();
        break;
    case 3: /* S-Scan */
        show_s_scan();
        break;
    default:
        break;
    }
}

}
