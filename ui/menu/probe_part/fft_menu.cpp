#include "fft_menu.h"
#include "ui_base_menu.h"
#include <device/device.h>
#include <QMessageBox>

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

    connect(m_switchItem, SIGNAL(value_changed(int)), this, SLOT(do_switchItem_changed(int)));
}

FftMenu::~FftMenu()
{
}

void FftMenu::do_switchItem_changed(int val)
{
    DplDisplay::DisplayPointer  displayPointer = DplDevice::Device::instance()->display();
    if(val) {
        displayPointer->set_layout(DplDisplay::Display::A, displayPointer->grps());
    } else {
//        if((DplDevice::Device::instance()->current_group()->transceiver()->rectifier()/* == DplFpga::Group::Rectifier*/)
//                && (1 == DplDevice::Device::instance()->current_group()->sample()->range() / 10 / DplDevice::Device::instance()->current_group()->current_beam()->point_qty())) {

            displayPointer->set_layout(DplDisplay::Display::AFFT, displayPointer->grps());
//        } else {
//            QMessageBox::warning(this, tr("Warning"), "Range is too large Or Not RF mode.");
//            disconnect(m_switchItem, SIGNAL(value_changed(int)), this, SLOT(do_switchItem_changed(int)));
//            m_switchItem->set_current_index(!val);
//            connect(m_switchItem, SIGNAL(value_changed(int)), this, SLOT(do_switchItem_changed(int)));
//        }
    }
}

}
