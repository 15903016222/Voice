#include "b_scan_item.h"

#include <QPainter>

#include <device/device.h>
#include <source/scan.h>

BscanItem::BscanItem(const DplDevice::GroupPointer &group, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_size(400, 200),
    m_group(group),
    m_source(DplSource::Source::instance()),
    m_scanAxis(DplSource::Scan::instance()->scan_axis()),
    m_image(NULL)
{
    connect(this, SIGNAL(update_requested()),
            this, SLOT(update()), Qt::QueuedConnection);

    connect(m_source, SIGNAL(restarted()),
            this, SLOT(clear()));

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(draw()), Qt::DirectConnection);
}

BscanItem::~BscanItem()
{
    QMutexLocker l(&m_mutex);
    if (m_image) {
        delete m_image;
        m_image = NULL;
    }
}

QRectF BscanItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}

void BscanItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QMutexLocker l(&m_mutex);
    if (!m_image) {
        return;
    }
    painter->drawPixmap(-m_size.width()/2, -m_size.height()/2, m_pixmap);
}

void BscanItem::set_size(const QSize &size)
{
    QMutexLocker l(&m_mutex);

    if (m_size == size) {
        return;
    }

    if (m_image) {
        delete m_image;
        m_image = NULL;
    }
    m_image = new BscanImage(m_group, size,
                             DplDevice::Device::instance()->display()->palette());
    m_size = size;
    init_index();
}

void BscanItem::update()
{
    QGraphicsObject::update();
}

void BscanItem::draw()
{
    QMutexLocker l(&m_mutex);
    if (!m_image) {
        return;
    }

    if (m_scanAxis->driving() == DplSource::Axis::TIMER) {
        draw_time();
    } else {
//        draw_encoder();
    }

    m_pixmap = QPixmap::fromImage(*m_image);

    emit update_requested();
}

void BscanItem::clear()
{
    QMutexLocker l(&m_mutex);
    if (m_image) {
        m_image->clear();
        init_index();
    }
}

void BscanItem::init_index()
{
    m_preIndex = 0;
    m_startIndex = 0;
    m_stopIndex = m_image->max_lines();
}

void BscanItem::draw_time()
{
    int curIndex = m_source->elapsed() * m_source->acquisition_rate() - 1;

    if (curIndex >= m_stopIndex) {
        m_image->shift(curIndex-m_stopIndex+1);
        m_stopIndex = curIndex+1;
        m_startIndex = m_stopIndex - m_image->max_lines();
    }

    if (m_preIndex < m_startIndex) {
        m_preIndex = m_startIndex;
    }

    DplSource::BeamPointer beam;
    for (int i = m_preIndex; i <= curIndex; ++i) {
        beam = m_source->beams(m_group->index(), i)->get(m_group->current_beam_index());
        m_image->draw_wave(beam->wave(), i-m_startIndex);
    }

    m_preIndex = curIndex;
}
