#include "display.h"
#include "a_scan_display.h"

#include <source/source.h>

#include <QLayout>
#include <QDebug>

namespace DplDisplay {

Display::Display(QWidget *parent) : QWidget(parent)
{
    DplSource::Source *source = DplSource::Source::get_instance();
    connect(source, SIGNAL(data_event()), this, SLOT(do_source_data_event()));

    DplDevice::Device *dev = DplDevice::Device::get_instance();
    if (dev->groups() == 0) {
        dev->add_group();
    }
    m_scanDisplay = new AscanDisplay(dev->get_group(0), this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_scanDisplay);

    source->start();
}

bool Display::set_type(Display::Type type)
{
    m_type = type;
    return true;
}

void Display::set_show_all(bool flag)
{
    m_showAll = flag;
}

void Display::do_source_data_event()
{
    DplSource::Source *source = DplSource::Source::get_instance();
    DplSource::Beam beam;
    source->get_group(0)->get_beam(0, beam);

    ((AscanDisplay *)m_scanDisplay)->show(beam);
}

}
