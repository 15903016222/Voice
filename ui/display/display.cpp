#include "display.h"
#include "a_scan_display.h"

#include <source/source.h>

#include <QDebug>

namespace DplDisplay {

Display * Display::s_display = NULL;
QMutex Display::s_mutex;

Display::Display(QWidget *parent) :
    QWidget(parent),
    m_scanLayout(NULL)
{
    DplSource::Source *source = DplSource::Source::get_instance();

    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    ScanLayout *l = new ScanLayout;
    QList<int> grpId;
    grpId.append(0);
    l->set_mode(ScanLayout::A, grpId);
    set_layout(l);

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

void Display::set_layout(ScanLayout *scanlayout)
{
    if (NULL == scanlayout) {
        return;
    }

    if (m_scanLayout != NULL) {
        delete m_scanLayout;
    }
    m_scanLayout = scanlayout;

    m_scanLayout->setParent(this);
    layout()->addWidget(m_scanLayout);

    DplDevice::Device *dev = DplDevice::Device::get_instance();

    QLayout *l = NULL;
    DplDevice::GroupPointer groupPtr;
    AscanDisplay *ascan = NULL;
    QList<int> grpIds = scanlayout->get_groups_id();

    for (int i = 0; i < grpIds.size(); ++i) {
        groupPtr = dev->get_group(grpIds[i]);
        /* A-SCAN */
        l = m_scanLayout->findChild<QLayout *>(QString("A%1").arg(grpIds[i]));
        if (l != NULL) {
            ascan = new AscanDisplay(groupPtr, m_scanLayout);
            l->addWidget(ascan);
        }

        /* B-SCAN */
        l = m_scanLayout->findChild<QLayout *>(QString("B%1").arg(grpIds[i]));
        if (l != NULL) {
            qDebug()<<__func__<<__LINE__<<"umimplement";
//            bscan = new BscanDisplay(groupPtr, m_scanLayout);
            AscanDisplay *bscan = new AscanDisplay(groupPtr, m_scanLayout);
            l->addWidget(bscan);
        }

        /* C-Scan */
        l = m_scanLayout->findChild<QLayout *>(QString("C%1").arg(grpIds[i]));
        if (l != NULL) {
            qDebug()<<__func__<<__LINE__<<"umimplement";
            AscanDisplay *cscan = new AscanDisplay(groupPtr, m_scanLayout);
//            cscan = new CscanDisplay(groupPtr, m_scanLayout);
            l->addWidget(cscan);
        }

        /* S-Scan */
        l = m_scanLayout->findChild<QLayout *>(QString("S%1").arg(grpIds[i]));
        if (l != NULL) {
            qDebug()<<__func__<<__LINE__<<"umimplement";
//            sscan = new SscanDisplay(groupPtr, m_scanLayout);
            AscanDisplay *sscan = new AscanDisplay(groupPtr, m_scanLayout);
            l->addWidget(sscan);
        }
    }
}

}
