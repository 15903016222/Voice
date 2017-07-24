#include "fft_menu.h"
#include "ui_base_menu.h"

namespace DplProbeMenu {

FftMenu::FftMenu(QWidget *parent) :
    BaseMenu(parent),
    m_gainItem(new SpinMenuItem(this, tr("Gain"), tr("dB"))),
    m_startItem(new SpinMenuItem(this, tr("Start"), "mm")),
    m_widthItem(new SpinMenuItem(this, tr("Width"), "mm")),
    m_switchItem(new ComboMenuItem(this, tr("Switch")))
{
    ui->layout0->addWidget(m_gainItem);
    ui->layout1->addWidget(m_startItem);
    ui->layout2->addWidget(m_widthItem);
    ui->layout3->addWidget(m_switchItem);

    /* Gain */
    m_gainItem->set(0, 100, 1);

    /* Start menu item */
    m_startItem->set(0, 16000, 2);

    /* Width menu item */
    m_widthItem->set(0.05, 525, 2);

    /* Switch menu item */
    m_switchItem->set(s_onOff);
}

FftMenu::~FftMenu()
{
}

}
