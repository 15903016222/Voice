#include "law_config_menu.h"

namespace DplFocalLawMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Combo
};

LawConfigMenu::LawConfigMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Law Type Menu Item */
    QStringList lawTypes;
    lawTypes.append(tr("Azimuthal"));
    lawTypes.append(tr("Linear"));
    m_menuItem[0]->set(tr("Law Type"), lawTypes);

    /* Pulse Connection menu item */
    m_menuItem[1]->set(tr("Pulse Connection"), "mm", 1, 113, 0);

    /* Receiver Connection menu item */
    m_menuItem[2]->set(tr("Receiver Connection"), "mm", 1, 113, 0);

    /* Wave Type Menu Item */
    QStringList waveTypes;
    waveTypes.append(tr("LW"));
    waveTypes.append(tr("SW"));
    m_menuItem[3]->set(tr("Wave Type"), waveTypes);
}

}
