#include "flaw_record_menu.h"

namespace DplMeasurementMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Label,
    MenuItem::Combo,
    MenuItem::Label,
    MenuItem::Combo,
    MenuItem::Label
};

FlawRecordMenu::FlawRecordMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Add/Delete Menu Item */
    m_menuItem[0]->set(tr("Add/Delete"), "");

    /* Flaw Image menu item */
    m_menuItem[1]->set(tr("Flaw Image"), s_onOff);

    /* Comment menu item */
    m_menuItem[2]->set(tr("Comment"), "");
    connect(m_menuItem[2], SIGNAL(clicked()), this, SLOT(do_comment_clicked()));

    /* Display Table Menu Item */
    m_menuItem[3]->set(tr("Display Table"), s_onOff);

    /* Export Record Menu Item */
    m_menuItem[4]->set(tr("Export Record"), "");

}

void FlawRecordMenu::do_comment_clicked()
{
    //    InputPanelContext inputPanel;
    //    MenuItem *widget = qobject_cast<MenuItem*>(sender());
    //    inputPanel.set_item_current_text(widget->get_label_text());
    //    inputPanel.exec();
    //    widget->set_label_text(inputPanel.get_text());
}

}
