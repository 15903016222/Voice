#include "cursors_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplMeasurementMenu {

CursorsMenu::CursorsMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    m_selectionItem = new ComboMenuItem();

    m_rItem = new SpinMenuItem();      /* %(r) */
    m_mItem = new SpinMenuItem();      /* %(m) */

    m_urItem = new SpinMenuItem();     /* U(r) */
    m_umItem = new SpinMenuItem();     /* U(m) */

    m_srItem = new SpinMenuItem();     /* S(r) */
    m_smItem = new SpinMenuItem();     /* S(m) */

    m_irItem = new SpinMenuItem();     /* I(r) */
    m_imItem = new SpinMenuItem();     /* I(m) */

    m_angelItem = new SpinMenuItem();

    /* Selection menu item */
    QStringList selectionList;
    selectionList.append(tr("A-Scan"));
    selectionList.append(tr("B-Scan"));
    selectionList.append(tr("C-Scan"));
    selectionList.append(tr("S-Scan"));
    m_selectionItem->set(tr("Selection"), selectionList);
    connect(m_selectionItem, SIGNAL(value_changed(int)), this, SLOT(do_selections_changed(int)));

    /* %(r) menu item */
    m_rItem->set(tr("%(r)"), "%", 0, 100, 1);

    /* %(m) menu item */
    m_mItem->set(tr("%(m)"), "%", 0, 100, 1);

    /* U(r) menu item */
    m_urItem->set(tr("U(r)"), "mm", 0, 2000, 2);

    /* U(m) menu item */
    m_umItem->set(tr("U(m)"), "mm", 0, 2000, 2);

    /* S(r) menu item */
    m_srItem->set(tr("S(r)"), "s", 0, 10000, 1);

    /* S(m) menu item */
    m_smItem->set(tr("S(m)"), "s", 0, 10000, 1);

    /* I(r) menu item */
    m_irItem->set(tr("I(r)"), "mm", 0, 2000, 1);

    /* I(m) menu item */
    m_imItem->set(tr("I(m)"), "mm", 0, 2000, 1);

    /* Angle menu item */
    m_angelItem->set(tr("Angle"), "°", 25, 75, 0);
}

CursorsMenu::~CursorsMenu()
{
    delete m_selectionItem;

    delete m_rItem;      /* %(r) */
    delete m_mItem;      /* %(m) */

    delete m_urItem;     /* U(r) */
    delete m_umItem;     /* U(m) */

    delete m_srItem;     /* S(r) */
    delete m_smItem;     /* S(m) */

    delete m_irItem;     /* I(r) */
    delete m_imItem;     /* I(m) */

    delete m_angelItem;
}

void CursorsMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_selectionItem);
    m_selectionItem->show();
    switch (m_selectionItem->get_current_index()) {
    case 0:
        /* A-Scan */
        show_a_scan();
        break;
    case 1:
        /* B-Scan */
        show_b_scan();
        break;
    case 2:
        /* C-Scan */
        show_c_scan();
        break;
    case 3:
        /* S-Scan */
        show_s_scan();
        break;
    default:
        break;
    }
}

void CursorsMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_selectionItem);
    m_selectionItem->hide();
    switch (m_selectionItem->get_current_index()) {
    case 0:
        /* A-Scan */
        hide_a_scan();
        break;
    case 1:
        /* B-Scan */
        hide_b_scan();
        break;
    case 2:
        /* C-Scan */
        hide_c_scan();
        break;
    case 3:
        /* S-Scan */
        hide_s_scan();
        break;
    default:
        break;
    }
}

void CursorsMenu::show_a_scan()
{
    ui->menuItem1->layout()->addWidget(m_rItem);
    ui->menuItem2->layout()->addWidget(m_mItem);
    ui->menuItem3->layout()->addWidget(m_urItem);
    ui->menuItem4->layout()->addWidget(m_umItem);
    m_rItem->show();
    m_mItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::hide_a_scan()
{
    ui->menuItem1->layout()->removeWidget(m_rItem);
    ui->menuItem2->layout()->removeWidget(m_mItem);
    ui->menuItem3->layout()->removeWidget(m_urItem);
    ui->menuItem4->layout()->removeWidget(m_umItem);
    m_rItem->hide();
    m_mItem->hide();
    m_urItem->hide();
    m_umItem->hide();
}

void CursorsMenu::show_b_scan()
{
    ui->menuItem1->layout()->addWidget(m_srItem);
    ui->menuItem2->layout()->addWidget(m_smItem);
    ui->menuItem3->layout()->addWidget(m_urItem);
    ui->menuItem4->layout()->addWidget(m_umItem);
    m_srItem->show();
    m_smItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::hide_b_scan()
{
    ui->menuItem1->layout()->removeWidget(m_srItem);
    ui->menuItem2->layout()->removeWidget(m_smItem);
    ui->menuItem3->layout()->removeWidget(m_urItem);
    ui->menuItem4->layout()->removeWidget(m_umItem);
    m_srItem->hide();
    m_smItem->hide();
    m_urItem->hide();
    m_umItem->hide();
}

void CursorsMenu::show_c_scan()
{
    ui->menuItem1->layout()->addWidget(m_srItem);
    ui->menuItem2->layout()->addWidget(m_smItem);
    ui->menuItem3->layout()->addWidget(m_irItem);
    ui->menuItem4->layout()->addWidget(m_imItem);
    m_srItem->show();
    m_smItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::hide_c_scan()
{
    ui->menuItem1->layout()->removeWidget(m_srItem);
    ui->menuItem2->layout()->removeWidget(m_smItem);
    ui->menuItem3->layout()->removeWidget(m_irItem);
    ui->menuItem4->layout()->removeWidget(m_imItem);
    m_srItem->hide();
    m_smItem->hide();
    m_irItem->hide();
    m_imItem->hide();
}

void CursorsMenu::show_s_scan()
{
    ui->menuItem1->layout()->addWidget(m_angelItem);
    ui->menuItem2->layout()->addWidget(m_urItem);
    ui->menuItem3->layout()->addWidget(m_umItem);
    ui->menuItem4->layout()->addWidget(m_irItem);
    ui->menuItem5->layout()->addWidget(m_imItem);
    m_angelItem->show();
    m_urItem->show();
    m_umItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::hide_s_scan()
{
    ui->menuItem1->layout()->removeWidget(m_angelItem);
    ui->menuItem2->layout()->removeWidget(m_urItem);
    ui->menuItem3->layout()->removeWidget(m_umItem);
    ui->menuItem4->layout()->removeWidget(m_irItem);
    ui->menuItem5->layout()->removeWidget(m_imItem);
    m_angelItem->hide();
    m_urItem->hide();
    m_umItem->hide();
    m_irItem->hide();
    m_imItem->hide();
}

void CursorsMenu::do_selections_changed(int index)
{
    Q_UNUSED(index);
    hide_a_scan();
    hide_b_scan();
    hide_c_scan();
    hide_s_scan();
    show();
}

}
