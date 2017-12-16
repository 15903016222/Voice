#include "s_scan_display.h"
#include "vpa_item.h"
#include "s_scan_image.h"

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../color_bar/color_bar.h"
#include "../ruler/index_ruler.h"
#include "../ruler/ut_ruler.h"

#include <global.h>
#include <device/device.h>

#include <QLabel>

SscanDisplay::SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) : ScanDisplay(parent),
    m_group(grp),
    m_indexRuler(new IndexRuler(Ruler::TOP, this)),
    m_utRuler(new UtRuler(grp, Ruler::RIGHT, this)),
    m_vpaItem(new VpaItem(grp)),
    m_sScan(grp->s_scan()),
    m_image(NULL)
{
    m_leftLayout->addWidget(m_utRuler);
    m_bottomLayout->addWidget(m_indexRuler);

    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    m_scene->addItem(m_vpaItem);
    m_vpaItem->update_pos();

    m_colorBar->set_palette(DplDevice::Device::instance()->display()->palette());

    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    m_titleLabel->setText(QString("S-Scan|Grp%1").arg(m_group->index()+1));
}

SscanDisplay::~SscanDisplay()
{
    QMutexLocker l(&m_imageMutex);
    if (m_image) {
        delete m_image;
    }
}

void SscanDisplay::do_data_event(const DplSource::BeamsPointer &beams)
{
    QMutexLocker l(&m_imageMutex);
    if (!m_image) {
        return;
    }

    m_image->draw_beams(beams);
//    m_bgItem->draw(*m_image);
    m_scene->drawBackground(*m_image);
}

void SscanDisplay::resize_event(const QSize &size)
{
    m_vpaItem->update_pos();

    m_scene->setSceneRect(-size.width()/2, -size.height()/2,
                          size.width(), size.height());

    QMutexLocker l(&m_imageMutex);
    if (m_image) {
        delete m_image;
    }
    m_image = new SscanImage(m_group, size, DplDevice::Device::instance()->display()->palette());
}

