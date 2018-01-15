#include "cursors_menu.h"
#include "vpa_menu_item.h"

#include <global.h>
#include <ui/tool/tool.h>
#include <source/scan.h>

#include "cursors/amp_ref_menu_item.h"
#include "cursors/amp_meas_menu_item.h"
#include "cursors/ut_ref_menu_item.h"
#include "cursors/ut_meas_menu_item.h"
#include "cursors/scan_ref_menu_item.h"
#include "cursors/scan_meas_menu_item.h"
#include "cursors/index_ref_menu_item.h"
#include "cursors/index_meas_menu_item.h"

namespace DplMeasurementMenu {

CursorsMenu::CursorsMenu(QWidget *parent) :
    BaseMenu(parent),
    m_selectionItem(new ComboMenuItem(this, tr("Selection"))),
    m_afItem(new AmpRefMenuItem(this)),
    m_amItem(new AmpMeasMenuItem(this)),
    m_urItem(new UtRefMenuItem(this)),
    m_umItem(new UtMeasMenuItem(this)),
    m_srItem(new ScanRefMenuItem(this)),
    m_smItem(new ScanMeasMenuItem(this)),
    m_irItem(new IndexRefMenuItem(this)),
    m_imItem(new IndexMeasMenuItem(this)),
    m_vpaItem(new VpaMenuItem(this))
{
    m_layout0->addWidget(m_selectionItem);

    /* Selection menu item */
    m_selectionItem->add_item(tr("A-Scan"));
    m_selectionItem->add_item(tr("B-Scan"));
    m_selectionItem->add_item(tr("C-Scan"));
    m_selectionItem->add_item(tr("S-Scan"));
    connect(m_selectionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_selectionItem_changed(int)));
    do_selectionItem_changed(0);
}

void CursorsMenu::show_a_scan()
{
    m_layout1->addWidget(m_afItem);
    m_layout2->addWidget(m_amItem);
    m_layout3->addWidget(m_urItem);
    m_layout4->addWidget(m_umItem);
    m_afItem->show();
    m_amItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::show_b_scan()
{
    m_layout1->addWidget(m_srItem);
    m_layout2->addWidget(m_smItem);
    m_layout3->addWidget(m_urItem);
    m_layout4->addWidget(m_umItem);
    m_srItem->show();
    m_smItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::show_c_scan()
{
    m_layout1->addWidget(m_srItem);
    m_layout2->addWidget(m_smItem);
    m_layout3->addWidget(m_irItem);
    m_layout4->addWidget(m_imItem);
    m_srItem->show();
    m_smItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::show_s_scan()
{
    m_layout1->addWidget(m_vpaItem);
    m_layout2->addWidget(m_urItem);
    m_layout3->addWidget(m_umItem);
    m_layout4->addWidget(m_irItem);
    m_layout5->addWidget(m_imItem);
    m_vpaItem->show();
    m_urItem->show();
    m_umItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_selectionItem->set_title(tr("Selection"));
        return;
    }

    BaseMenu::changeEvent(e);
}

void CursorsMenu::do_selectionItem_changed(int index)
{
    m_afItem->hide();
    m_amItem->hide();
    m_urItem->hide();
    m_umItem->hide();
    m_srItem->hide();
    m_smItem->hide();
    m_irItem->hide();
    m_imItem->hide();
    m_vpaItem->hide();

    if ( 0 == index ) {
        show_a_scan();
    } else if ( 1 == index ) {
        show_b_scan();
    } else if ( 2 == index ) {
        show_c_scan();
    } else if ( 3 == index ) {
        show_s_scan();
    }
}

}
