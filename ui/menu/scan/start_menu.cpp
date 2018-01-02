#include "start_menu.h"

#include <device/device.h>
#include <fpga/fpga.h>
#include <source/source.h>

namespace DplScanMenu {

StartMenu::StartMenu(QWidget *parent) :
    BaseMenu(parent),
    m_startItem(new LabelMenuItem(this, tr("Start"))),
    m_pauseItem(new LabelMenuItem(this, tr("Pause")))
{
    m_layout0->addWidget(m_startItem);
    m_layout1->addWidget(m_pauseItem);
    connect(m_startItem, SIGNAL(clicked()),
            this, SLOT(do_startItem_clicked()));
    connect(m_pauseItem, SIGNAL(clicked()),
            this, SLOT(do_pauseItem_clicked()));
}

StartMenu::~StartMenu()
{
}

void StartMenu::do_startItem_clicked()
{
    DplFpga::Fpga::instance()->reset_encoder();
    DplSource::Source::instance()->restart();
}

void StartMenu::do_pauseItem_clicked()
{
    if (DplDevice::Device::instance()->is_running()) {
        DplDevice::Device::instance()->stop();
    } else {
        DplDevice::Device::instance()->start();
    }
}

}
