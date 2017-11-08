#include "fft_item.h"

#include <QPainter>
#include <QFile>
#include <source/source.h>
#include <ui/display/fft_calculator.h>

FFTItem::FFTItem(QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_fftCalculator(new FFTCalculator)
{
    connect(this, SIGNAL(wave_changed()), this, SLOT(do_wave_changed()));
}

FFTItem::~FFTItem()
{
    delete m_fftCalculator;
}

QRectF FFTItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}

void FFTItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QWriteLocker l(&m_locker);

    painter->fillRect(this->boundingRect(),QColor(Qt::black));

    paint_value(painter);

    painter->setPen(QColor(Qt::blue));
    painter->drawPath(m_wavePath);
}

inline const QSize &FFTItem::size() const
{
    return m_size;
}

void FFTItem::set_size(const QSize &size)
{
    m_size = size;
    update();
}


void FFTItem::draw(const QByteArray &wave, const DplDevice::GroupPointer &group)
{
    QWriteLocker l(&m_locker);

    if(m_size.width() < 0
        || m_size.height() < 0) {
        return;
    }

    double ratio = m_size.width() / group->sample()->range();
    int gateStart = group->gate_a()->start() * ratio;
    int gateWidth = group->gate_a()->width() * ratio;

    if(gateStart < 0
        || gateStart > m_size.width()
        || gateWidth < 0
        || gateWidth > m_size.width()) {
        QPainterPath path;
        m_wavePath = path;
        emit wave_changed();
        return;
    }

    int beginPos = wave.size() * gateStart / m_size.width();
    int dataLen = wave.size() * gateWidth / m_size.width();

    const char *data = wave.data();
    data += beginPos;

    /* 计算FPGA采样频率 */
    double dataHz = 1.0 / (DplDevice::Device::instance()->current_group()->sample()->precision() / pow(1000.0, 3));
    double dataMHz = dataHz / 1000000.0;
    if(!m_fftCalculator->execute(dataLen, (unsigned char*)data, m_size.width(), dataMHz)) {
        emit wave_changed();
        return;
    }

    const FFTCalculator::S_FFT_result &fftResult = m_fftCalculator->get_result();

    float yRatio = m_size.height() / 255.0;

    QPainterPath path;
    path.moveTo(-m_size.width() / 2.0, -m_size.height() / 2.0);
    for (int i = 0; i < m_size.width(); ++i) {
        path.lineTo(i - m_size.width() / 2.0,
                    m_size.height() / 2.0 - yRatio * fftResult.data[i]);
    }

    m_wavePath = path;
    emit wave_changed();
}

double FFTItem::get_Mhz_ratio()
{
    return m_fftCalculator->get_result().MhzRatio;
}

void FFTItem::do_wave_changed()
{
    update();
}


void FFTItem::paint_value(QPainter *painter)
{
    QFont font("Arial", 8, QFont::Normal);
    painter->setFont(font);
    painter->setPen(QColor(Qt::white));

    double height = 10;
    double margin = 80;
    double width = (m_size.width() - 2 * margin) / 7.0;
    double offsetY = -m_size.height() / 2.0;
    double offsetX = -m_size.width() / 2.0;

    const FFTCalculator::S_FFT_result &fftResult = m_fftCalculator->get_result();

    painter->drawText(QRect(margin + offsetX,
                            height + offsetY,
                            width,
                            5 * height),
                      tr("\n-6db\n\n-20db"));

    painter->drawText(QRect(margin + offsetX + width,
                            height + offsetY,
                            width,
                            5 * height),
                      QString("Lower\n%1 Mhz\n\n%2 Mhz")
                      .arg(QString::number(fftResult.min6dbFrequency,'f',2))
                      .arg(QString::number(fftResult.min20dbFrequency,'f',2)));

    painter->drawText(QRect(margin + offsetX + 2 * width,
                            height + offsetY,
                            width,
                            5 * height),
                      QString("Higher\n%1 Mhz\n\n%2 Mhz")
                      .arg(QString::number(fftResult.max6dbFrequency,'f',2))
                      .arg(QString::number(fftResult.max20dbFrequency,'f',2)));

    painter->drawText(QRect(margin + offsetX + 3 * width,
                            height + offsetY,
                            width,
                            5 * height),
                      QString("Center\n%1 Mhz\n\n%2 Mhz")
                      .arg(QString::number(fftResult.centerFrequency6db,'f',2))
                      .arg(QString::number(fftResult.centerFrequency20db,'f',2)));

    painter->drawText(QRect(margin + offsetX + 4 * width,
                            height + offsetY,
                            width,
                            5 * height),
                      QString("Bandwidth\n%1 Mhz\n\n%2 Mhz")
                      .arg(QString::number(fftResult.bandWidth6db,'f',2))
                      .arg(QString::number(fftResult.bandWidth20db,'f',2)));

    painter->drawText(QRect(margin + offsetX + 5 * width,
                            height + offsetY,
                            width,
                            5 * height),
                      QString("Bandwidth\n%1%\n\n%2%")
                      .arg(QString::number(fftResult.bandWidth6dbPercent,'f',2))
                      .arg(QString::number(fftResult.bandWidth20dbPercent,'f',2)));

    painter->drawText(QRect(margin + offsetX + 6 * width,
                            height + offsetY,
                            width,
                            5 * height),
                      QString("MAX: %1 Mhz").arg(QString::number(fftResult.peakFrequency,'f',2)));

}


