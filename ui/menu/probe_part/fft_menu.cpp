#include "fft_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplProbeMenu {

FftMenu::FftMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Gain */
    m_gainItem.set(tr("Gain"), "dB", 0, 100, 1);

    /* Start menu item */
    m_startItem.set(tr("Start"), "mm", 0, 16000, 2);

    /* Width menu item */
    m_widthItem.set(tr("Width"), "mm", 0.05, 525, 2);

    /* Switch menu item */
    m_switchItem.set(tr("Switch"), s_onOff);
}

FftMenu::~FftMenu()
{
}

void FftMenu::show()
{
    ui->menuItem0->layout()->addWidget(&m_gainItem);
    ui->menuItem1->layout()->addWidget(&m_startItem);
    ui->menuItem2->layout()->addWidget(&m_widthItem);
    ui->menuItem3->layout()->addWidget(&m_switchItem);
    m_gainItem.show();
    m_startItem.show();
    m_widthItem.show();
    m_switchItem.show();
}

void FftMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_gainItem);
    ui->menuItem1->layout()->removeWidget(&m_startItem);
    ui->menuItem2->layout()->removeWidget(&m_widthItem);
    ui->menuItem3->layout()->removeWidget(&m_switchItem);
    m_gainItem.hide();
    m_startItem.hide();
    m_widthItem.hide();
    m_switchItem.hide();
}

}
