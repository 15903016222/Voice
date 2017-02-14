#include "display.h"
#include "a_scan_display.h"

#include <source/source.h>

#include <QLayout>
#include <QDebug>

namespace DplDisplay {

Display * Display::s_display = NULL;
QMutex Display::s_mutex;

Display::Display(QWidget *parent) :
    QWidget(parent),
    m_type(A_SCAN),
    m_showAllFlag(false),
    m_widget(NULL)
{
    init_show_map();

    DplSource::Source *source = DplSource::Source::get_instance();

    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    show();

    source->start();
}

Display *Display::get_instance()
{
    QMutexLocker l(&s_mutex);
    if (s_display == NULL) {
        s_display = new Display();
    }
    return s_display;
}

void Display::set_mode(Display::Mode mode)
{
    if (m_type == mode) {
        return;
    }
    m_type = mode;
    show();
}

void Display::set_show_all(bool flag)
{
    if (flag == m_showAllFlag) {
        return;
    }

    m_showAllFlag = flag;
    show();
}

void Display::show()
{
    if (NULL != m_widget) {
        delete m_widget;
        m_widget = NULL;
    }

    QVBoxLayout *topLayout = static_cast<QVBoxLayout *>(layout());
    m_widget = new QWidget(this);
    m_vboxLayout = new QVBoxLayout(m_widget);
    m_vboxLayout->setContentsMargins(0, 0, 0, 0);
    m_vboxLayout->setSpacing(0);
    topLayout->addWidget(m_widget);

    ShowFun fun = m_showMap[m_type];
    (this->*fun)();
}

void Display::init_show_map()
{
    ::memset(m_showMap, 0, sizeof(m_showMap));
    m_showMap[A_SCAN]   = &Display::show_single_scan<AscanDisplay>;
//    m_showMap[B_SCAN]   = &Display::show_single_scan<BscanDisplay>;
//    m_showMap[C_SCAN]   = &Display::show_single_scan<CscanDisplay>;
//    m_showMap[S_SCAN]   = &Display::show_single_scan<SscanDisplay>;
    m_showMap[AB_SCAN]  = &Display::show_ab_scan;
}

template <typename T>
void Display::show_single_scan()
{
    DplDevice::Device *dev = DplDevice::Device::get_instance();
    int num = dev->groups();

    if (m_showAllFlag
            && num != 1) {

        QHBoxLayout *hboxLayout1 = new QHBoxLayout();
        QHBoxLayout *hboxLayout2 = new QHBoxLayout();

        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setSpacing(0);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setSpacing(0);

        for (int i = 0; i < num/2; ++i) {
            AscanDisplay *a = new AscanDisplay(dev->get_group(i), m_widget);
            AscanDisplay *b = new AscanDisplay(dev->get_group(i+num/2+num%2), m_widget);
            hboxLayout1->addWidget(a);
            hboxLayout2->addWidget(b);
        }

        if (num%2) {
            AscanDisplay *a = new AscanDisplay(dev->get_group(num/2), m_widget);
            hboxLayout1->addWidget(a);
        }

        m_vboxLayout->addLayout(hboxLayout1);
        m_vboxLayout->addLayout(hboxLayout2);
    } else {
        AscanDisplay *ascan = new AscanDisplay(dev->current_group(), m_widget);
        m_vboxLayout->addWidget(ascan);
    }
}

void Display::show_ab_scan()
{
    DplDevice::Device *dev = DplDevice::Device::get_instance();
    int num = dev->groups();

    if (m_showAllFlag) {

    } else {
        AscanDisplay *a = new AscanDisplay(dev->current_group(), m_widget);
        AscanDisplay *b = new AscanDisplay(dev->current_group(), m_widget);
        m_vboxLayout->addWidget(a);
        m_vboxLayout->addWidget(b);
    }
}

}
