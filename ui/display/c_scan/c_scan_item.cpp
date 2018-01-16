#include "c_scan_item.h"

#include <QPainter>

#include <device/device.h>
#include <source/scan.h>

CscanItem::CscanItem(const DplDevice::GroupPointer &group, QGraphicsItem *parent) :
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

    connect(static_cast<DplSource::Axis *>(m_scanAxis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(clear()));

    connect(static_cast<DplSource::Axis *>(m_scanAxis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(clear()));

    connect(static_cast<DplSource::Axis *>(m_scanAxis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(clear()));

    connect(static_cast<DplSource::Axis *>(m_scanAxis.data()),
            SIGNAL(resolution_changed(float)),
            this, SLOT(clear()));

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(draw()), Qt::DirectConnection);
}

CscanItem::~CscanItem()
{
    QMutexLocker l(&m_mutex);
    if (m_image) {
        delete m_image;
        m_image = NULL;
    }
}

QRectF CscanItem::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void CscanItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QMutexLocker l(&m_mutex);
    if (!m_image) {
        return;
    }
    painter->drawPixmap(0, 0, m_pixmap);
}

void CscanItem::set_size(const QSize &size)
{
    QMutexLocker l(&m_mutex);

    if (m_size == size) {
        return;
    }

    if (m_image) {
        delete m_image;
        m_image = NULL;
    }
    m_image = new CscanImage(size, DplDevice::Device::instance()->display()->palette());
    m_size = size;

    init_index();
}

void CscanItem::update()
{
    QGraphicsObject::update();
}

void CscanItem::draw()
{
    QMutexLocker l(&m_mutex);
    if (!m_image) {
        return;
    }

    if (m_scanAxis->driving() == DplSource::Axis::TIMER) {
        draw_time();
    } else {
        draw_encoder();
    }

    m_pixmap = QPixmap::fromImage(*m_image);

    emit update_requested();
}

void CscanItem::clear()
{
    QMutexLocker l(&m_mutex);
    if (m_image) {
        m_image->clear();
        init_index();
    }
}

void CscanItem::init_index()
{
    if (m_scanAxis->driving() == DplSource::Axis::TIMER) {
        m_preIndex = 0;
        m_startIndex = 0;
        m_stopIndex = m_image->max_lines();
    } else {
        m_startIndex = 0;
        m_stopIndex = (m_scanAxis->end() - m_scanAxis->start())/m_scanAxis->resolution();
        if (m_image->height() < m_stopIndex) {
            m_stopIndex = m_image->height();
            m_ratio = 1.0;
        } else {
            m_ratio = 1.0 * m_image->height() / m_stopIndex;
        }
        m_preIndex = m_startIndex;
    }
}

void CscanItem::draw_time()
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

    DplSource::BeamsPointer beams;
    DplSource::BeamPointer beam;
    int gates[1024] = {0};

    for (int i = m_preIndex; i <= curIndex; ++i) {
        beams = m_source->beams(m_group->index(), i);
        if (beams.isNull()) {
            continue;
        }
        for (int j = 0; j < beams->beam_qty(); ++j) {
            beam = beams->get(j);
            if (beam.isNull()) {
                break;
            }
            gates[j] = beam->gate_peak(DplSource::Beam::GATE_A) * 255.0 / 200;
        }
        m_image->draw(gates, beams->beam_qty(), i-m_startIndex);
    }

    m_preIndex = curIndex;
}

void CscanItem::draw_encoder()
{
    double curX  = 0.0;

    if (m_scanAxis->driving() == DplSource::Axis::ENCODER_X) {
        curX = m_group->current_beam()->encoder_x();
    } else {
        curX = m_group->current_beam()->encoder_y();
    }

    if (curX > m_scanAxis->end()) {
        curX = m_scanAxis->end();
    } else if ( curX < m_scanAxis->start()) {
        curX = m_scanAxis->start();
    }

    int curIndex = (curX - m_scanAxis->start()) / m_scanAxis->resolution() + 0.5;

    if (curIndex > m_stopIndex) {
        m_image->shift(curIndex-m_stopIndex+1);
        m_stopIndex = curIndex+1;
        m_startIndex = m_stopIndex - m_image->max_lines();
    } else if (curIndex < m_startIndex) {
        m_image->shift(curIndex-m_startIndex);
        m_startIndex = curIndex;
        m_stopIndex = m_startIndex + m_image->max_lines();
    }

    if (m_preIndex < m_startIndex) {
        m_preIndex = m_startIndex;
    } else if( m_preIndex > m_stopIndex) {
        m_preIndex = m_stopIndex;
    }

    DplSource::BeamsPointer beams;

    int start = 0;
    int stop = 0;
    if (m_preIndex < curIndex) {
        start = m_preIndex;
        stop = curIndex;
    } else {
        start = curIndex;
        stop = m_preIndex;
    }

    int gate[1024] = {0};
    for (int i = start; i <= stop; ++i) {
        beams = m_source->beams(m_group->index(), i);
        if (beams.isNull()) {
            continue;
        }

        for (int j = 0; j < beams->beam_qty(); ++j) {
            gate[j] = beams->get(j)->gate_peak(DplSource::Beam::GATE_A) * 255.0 / 200;
        }

        for (int j = (i-m_startIndex)*m_ratio+0.5;
             j < (i-m_startIndex+1)*m_ratio + 0.5; ++j) {
            m_image->draw(gate, beams->beam_qty(), j);
        }
    }

    m_preIndex = curIndex;
}
