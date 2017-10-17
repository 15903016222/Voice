#ifndef __BASE_IMAGE_ITEM_H__
#define __BASE_IMAGE_ITEM_H__

#include <QGraphicsItem>
#include <QReadWriteLock>

#include <display/palette_color.h>
#include <source/axis.h>
#include <source/beams.h>
#include <focallaw/scan_cnf.h>
#include <device/device.h>

#include "test_stub.h"

static const int    STORE_BUFFER_SIZE    = 256 * 1024 * 1024 ;   /* 256MB */
static const double DEFAULT_PIX_PER_BEAM = 1.0;                  /* 默认每条beam占1pix */
static const int    DEFAULT_POINT_SIZE   = 256;                  /* 默认每条beam多少个point */

static const double FLOAT_ZERO  = 0.0000001;
static const double SECOND      = 1000.0;

struct S_BEAM_INFO{
    int x;
    int y;
    QByteArray beamData;
};


class BaseImageItem : public QGraphicsObject
{
    Q_OBJECT

public:

    enum E_BEAM_TYPE {
        NORMAL_BEAM,
        LAST_BEAM
    };

    struct S_CommonProperties {
        float   ratio;      /* 每个像素代表beam中的多少个点数据 */
        double  pixCount;   /* 每条beam占多少像素,采用double进行计算具体数据 */
        int     maxIndex;   /* 最大的beam数，超出后滚动显示 */
        int     align;      /* 对齐数据（例子：width为20， pixCount为3， 则align为 width % pixCount = 2）*/
    };

    struct S_RedrawProperties {
        unsigned int currentFrameIndex; /* 当前显示的最后一帧数据的index */
        int totalFrameCount;            /* 整个storeBuffer可存放的帧数 */
        int redrawCount;                /* 需要重画的帧数 */
        int beginShowIndex;             /* 从第beginShowIndex帧开始重画 */
    };

    explicit BaseImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);
    ~BaseImageItem();

    bool set_pix_per_beam(double ratio);

    inline void set_scroll_window(bool flag) { m_scrolling = flag; }

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

    bool redraw_beams(const DplSource::BeamsPointer &beams);

    void set_beams(const DplSource::BeamsPointer &beams);

    inline DplSource::Axis::Driving driving() { return m_driving; }

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    /**
     * @brief size  获取显示大小
     * @return      大小
     */
    inline const QSize &size() const { return m_size; }

signals:
    void image_changed();

public slots:
    void set_size(const QSize &size);
    void update();

protected:

    QReadWriteLock  m_rwLock;
    QSize           m_size;
    QImage          *m_image;
    DplSource::BeamsPointer m_beamsPointer;

    volatile bool   m_scrolling;
    volatile bool   m_redrawFlag;
    volatile DplSource::Axis::Driving        m_driving;

    DplDisplay::PaletteColorPointer m_palette;
    double          m_pixPerBeamRatio;
    int             m_beamsShowedCount;
    DplDevice::GroupPointer m_group;
    volatile bool   m_initFinished;


    /**
     * @brief draw_vertical_beam    C扫的垂直显示
     */
    virtual void draw_vertical_beam() = 0;

    /**
     * @redraw_horizontal_beam 当显示大小改变，重新画垂直C扫
     */
    virtual bool redraw_vertical_beam() = 0;

    void calculate_common_properties(BaseImageItem::S_CommonProperties &commonProperties);

    virtual void set_vertical_image_data(int beamsShowedCount,
                                         const BaseImageItem::S_CommonProperties &commonProperties,
                                         E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer) = 0;

private:

    void check_scroll_window(const QSize &oldSize);

};

#endif // __BASE_IMAGE_ITEM_H__
