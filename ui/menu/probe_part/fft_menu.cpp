#include "fft_menu.h"

namespace DplProbeMenu {

static const MenuItem::Type s_type[MAX_ITEMS] = {
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Combo
};

FftMenu::FftMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_type, parent)
{
    m_menuItem[0]->set(tr("Gain"), "dB", 0, 100, 1);

    /* Start menu item */
    m_menuItem[1]->set(tr("Start"), "mm", 0, 16000, 2);

    /* Width menu item */
    m_menuItem[2]->set(tr("Width"), "mm", 0.05, 525, 2);

    /* Switch menu item */
    m_menuItem[3]->set(tr("Switch"), s_onOff);
}

}
