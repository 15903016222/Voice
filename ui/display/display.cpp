#include "display.h"
#include "a_scan_display.h"

#include <source/source.h>

#include <QLayout>
#include <QDebug>

namespace DplDisplay {

Display::Display(QWidget *parent) :
    QWidget(parent),
    m_type(A_SCAN),
    m_showAllFlag(false)
{
    init_show_map();

    DplSource::Source *source = DplSource::Source::get_instance();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    show();

    source->start();
}

void Display::set_type(Display::Type type)
{
    m_type = type;
    show();
}

void Display::set_show_all(bool flag)
{
    m_showAllFlag = flag;
    show();
}

void Display::show()
{
    ShowFun fun = m_showMap[m_type];
    (this->*fun)();
}

void Display::show_a_scan()
{
    QVBoxLayout *mainLayout = dynamic_cast<QVBoxLayout *>(this->layout());

    if (m_showAllFlag) {

    } else {
        DplDevice::GroupPointer group = DplDevice::Device::get_instance()->current_group();
        AscanDisplay *aScan = new AscanDisplay(group, this);

        mainLayout->addWidget(aScan);
    }
}

void Display::show_b_scan()
{

}

void Display::show_c_scan()
{

}

void Display::show_s_scan()
{

}

void Display::init_show_map()
{
    ::memset(m_showMap, 0, sizeof(m_showMap));
    m_showMap[A_SCAN] = &Display::show_a_scan;
    m_showMap[B_SCAN] = &Display::show_b_scan;
    m_showMap[C_SCAN] = &Display::show_c_scan;
    m_showMap[S_SCAN] = &Display::show_s_scan;
}


}
