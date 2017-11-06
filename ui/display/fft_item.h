#ifndef __FFT_ITEM_H__
#define __FFT_ITEM_H__

#include <QGraphicsItem>
#include <QReadWriteLock>
#include <device/device.h>
#include <ui/display/fft_calculator.h>

class FFTItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit FFTItem(QGraphicsItem *parent = 0);
    ~FFTItem();

    /**
     * @brief boundingRect 返回FFTItem的矩形边界
     * @return
     */
    QRectF boundingRect() const;

    /**
     * @brief paint     进行FFT波形绘制
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief size  获取显示大小
     * @return      大小
     */
    const QSize &size() const;

    /**
     * @brief set_size  设置显示大小
     * @param size      大小
     */
    void set_size(const QSize &size);

    /**
     * @brief draw  画FFT后的波形
     * @param wave  原始波形数据
     * @param gateStart  闸门起点
     * @param gateWidth  闸门宽度
     */
    void draw(const QByteArray &wave, const DplDevice::GroupPointer &group);

signals:
    void wave_changed();

private slots:

    /**
     * @brief do_wave_changed 处理波形改变后的数据
     */
    void do_wave_changed();

private:
    QSize           m_size;
    QReadWriteLock  m_locker;
    FFTCalculator   *m_fftCalculator;
    QPainterPath    m_wavePath;

    /**
     * @brief paint_value   画FFT后的结果数据
     * @param painter       painter
     */
    void paint_value(QPainter *painter);

};

#endif // __FFT_ITEM_H__
