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

    QReadLocker l(&m_locker);
    painter->fillRect(this->boundingRect(),QColor(Qt::black));
    painter->setPen(QColor(Qt::blue));
    painter->drawPath(m_path);

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
    QReadLocker l(&m_locker);
    qDebug() << "[FFTItem::draw]"
             << " m_size w = " << m_size.width()
             << " h = " << m_size.height()
             << " range = " << group->sample()->range();

    if(m_size.width() < 0
        || m_size.height() < 0) {
        return;
    }

    double ratio = m_size.width() / group->sample()->range();
    int gateStart = group->gate_a()->start() * ratio;
    int gateWidth = group->gate_a()->width() * ratio;

    qDebug() << "[FFTItem::draw]"
             << " a start = " << group->gate_a()->start()
             << " a width = " << group->gate_a()->width()
             << " ratio = " << ratio
             << " gateStart = " << gateStart
             << " gateWidth = " << gateWidth;

    if(gateStart < 0
        || gateStart > m_size.width()
        || gateWidth < 0
        || gateWidth > m_size.width()) {
        m_path.lineTo(QPointF(0.0, 0.0));
        emit wave_changed();
        return;
    }


#if 0
    int beginPos = wave.size() * gateStart / m_size.width();
    int dataLen = wave.size() * gateWidth / m_size.width();

    qDebug() << "[FFTItem::draw]"
             << " wave size = " << wave.size()
             << " beginPos = " << beginPos
             << " dataLen = " << dataLen;

    const char *data = wave.data();
    data += beginPos;


    if(!m_fftCalculator->execute(dataLen, (unsigned char*)data, m_size.width())) {
        emit wave_changed();
        return;
    }

    const FFTCalculator::S_FFT_result &fftResult = m_fftCalculator->get_result();

    float xRatio = m_size.width() / 1.0 / ( wave.size() - 1);     // n个点，分为n-1段
    float yRatio = m_size.height() / 255.0;


    emit wave_changed();


#else
    int tmpGateWidth = 473;
    int tmpShowWidth = 605;
    int pointQty     = 638;

    int dataLen = pointQty * tmpGateWidth / tmpShowWidth;

    QFile file(tr("/home/tt/TT/data.txt"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << " open file failed!!!";
        return;
    }

    unsigned char mydata[1024];
    QString byteArray;
    int i = 0;
    while(!file.atEnd()) {
        byteArray = file.readLine();
        mydata[i] = byteArray.toDouble();
        ++i;
    }

    if(!m_fftCalculator->execute(dataLen, mydata, tmpShowWidth)) {
        emit wave_changed();
        return;
    }

    const FFTCalculator::S_FFT_result &fftResult = m_fftCalculator->get_result();

    float xRatio = tmpShowWidth / 1.0 / ( pointQty - 1);     // n个点，分为n-1段
    float yRatio = m_size.height() / 255.0;

    int drawPoints = tmpShowWidth;

    qDebug() << "[FFTItem::draw] "
             << " xRatio = " << xRatio
             << " yRatio = " << yRatio;

    static int once = 0;
    if(once == 0) {
        FILE *fpt = NULL;
        fpt = fopen("/home/tt/TT/ret_qt.txt","w");

        for(i = 0 ;i < 1024 ;i++)
        {
            fprintf(fpt,"%d\n", fftResult.data[i]);
            qDebug() << " ret = " << fftResult.data[i];
        }

        fclose(fpt);

        ++once;
    }

    QPainterPath path;

    for (int i = 0; i < drawPoints; ++i) {
        path.lineTo(i * xRatio - m_size.width() / 2.0,
                    m_size.height() / 2.0 - yRatio * fftResult.data[i]);
    }

    m_path = path;
    emit wave_changed();

#endif


}

void FFTItem::do_wave_changed()
{
    update();
}
