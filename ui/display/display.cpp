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
    m_widget(NULL)
{
    DplSource::Source *source = DplSource::Source::get_instance();

    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

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

void Display::set_layout(QWidget *w)
{
    if (NULL == w) {
        return;
    }

    if (m_widget != NULL) {
        delete m_widget;
    }
    m_widget = w;

    m_widget->setParent(this);
    layout()->addWidget(m_widget);

    DplDevice::Device *dev = DplDevice::Device::get_instance();
    int grpQty = dev->groups();

    QLayout *l = NULL;
    DplDevice::GroupPointer groupPtr;
    AscanDisplay *ascan = NULL;
    for (int i = 0; i < grpQty; ++i) {
        groupPtr = dev->get_group(i);

        /* A-SCAN */
        l = m_widget->findChild<QLayout *>(QString("A%1").arg(i+1));
        if (l != NULL) {
            ascan = new AscanDisplay(groupPtr, m_widget);
            l->addWidget(ascan);
        }

        /* B-SCAN */
        l = m_widget->findChild<QLayout *>(QString("B%1").arg(i+1));
        if (l != NULL) {
            qDebug()<<__func__<<__LINE__<<"umimplement";
//            bscan = new BscanDisplay(groupPtr, m_widget);
//            l->addWidget(bscan);
        }

        /* C-Scan */
        l = m_widget->findChild<QLayout *>(QString("C%1").arg((i+1)));
        if (l != NULL) {
            qDebug()<<__func__<<__LINE__<<"umimplement";
//            cscan = new CscanDisplay(groupPtr, m_widget);
//            l->addWidget(cscan);
        }

        /* S-Scan */
        l = m_widget->findChild<QLayout *>(QString("S%1").arg((i+1)));
        if (l != NULL) {
            qDebug()<<__func__<<__LINE__<<"umimplement";
//            sscan = new SscanDisplay(groupPtr, m_widget);
//            l->addWidget(sscan);
        }
    }
}

}
