#include "b_scan_display.h"

#include <device/device.h>

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../color_bar/color_bar.h"
#include "../ruler/ruler.h"

#include <QLabel>

BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    ScanDisplay(parent),
    m_group(grp),
    m_source(DplSource::Source::instance()),
    m_image(NULL),
    m_preIndex(0)
{
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    m_colorBar->set_palette(DplDevice::Device::instance()->display()->palette());
    m_titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    connect(m_source, SIGNAL(restarted()),
            this, SLOT(restart()));
}

BscanDisplay::~BscanDisplay()
{
    QMutexLocker l(&m_imageMutex);
    if (m_image) {
        delete m_image;
    }
}

void BscanDisplay::restart()
{
    QMutexLocker l(&m_imageMutex);
    if (m_image) {
        m_image->clear();
        m_preIndex = 0;
        m_startIndex = 0;
        m_stopIndex = m_image->max_lines();
    }
}

void BscanDisplay::resize_event(const QSize &size)
{
    QMutexLocker l(&m_imageMutex);
    if (m_image) {
        delete m_image;
    }
    m_image = new BscanImage(m_group, size,
                             DplDevice::Device::instance()->display()->palette());
    /* timer */
    m_preIndex = 0;
    m_startIndex = 0;
    m_stopIndex = m_image->max_lines();
}

void BscanDisplay::do_data_event(const DplSource::BeamsPointer &beams)
{
    Q_UNUSED(beams);
    QMutexLocker l(&m_imageMutex);
    if (!m_image) {
        return;
    }

    /* Timer */
    int curIndex = m_source->elapsed() * m_source->acquisition_rate();

    if(curIndex >= m_stopIndex) {
        m_image->shift(curIndex-m_stopIndex+1);
        m_stopIndex = curIndex+1;
        m_startIndex = m_stopIndex - m_image->max_lines();
    }

    for (int i = m_preIndex; i <= curIndex; ++i) {
        m_image->draw_wave(m_group->current_beam()->wave(), i-m_startIndex);
    }
    m_preIndex = curIndex;

    m_scene->drawBackground(*m_image);
}
