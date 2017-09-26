#ifndef __C_SCAN_SCENE_H__
#define __C_SCAN_SCENE_H__

#include <QGraphicsScene>
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

class CscanScene : public QGraphicsScene
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

    explicit CscanScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent = 0);

    inline DplSource::Axis::Driving driving() { return m_driving; }

    bool set_pix_per_beam(double ratio);
    inline void set_scroll_window(bool flag) { m_scrolling = flag; }

    virtual bool need_refresh(const DplSource::BeamsPointer &beams);

    bool redraw_beams();

    void set_beams(const DplSource::BeamsPointer &beams);

signals:
    void image_changed();

public slots:
    void set_size(const QSize &size);

protected:
    volatile DplSource::Axis::Driving        m_driving;
    volatile bool   m_scrolling;
    double          m_pixPerBeamRatio;
    QReadWriteLock  m_rwLock;

    double          m_currentStart;
    double          m_currentEnd;
    DplFocallaw::ScanCnf::Mode  m_focallawMode;

    QSize           m_size;
    QImage          *m_image;
    volatile bool   m_redrawFlag;

    DplSource::BeamsPointer m_beamsPointer;
    int             m_beamsShowedCount;

    TestStub::C_SCAN_SOURCE m_source;

    DplDevice::GroupPointer m_group;

    /**
     * @brief draw_vertical_beam    C扫的垂直显示
     */
    virtual void draw_vertical_beam();


    /**
     * @redraw_horizontal_beam 当显示大小改变，重新画垂直C扫
     */
    virtual void redraw_vertical_beam();

    void calculate_common_properties(CscanScene::S_CommonProperties &commonProperties);
    void calculate_redraw_properties(CscanScene::S_CommonProperties &commonProperties,
                                     CscanScene::S_RedrawProperties &redrawProperites);

    /**
     * @brief set_vertical_image_data   设置时间C扫的垂直显示image数据
     * @param beamsShowedCount
     * @param commonProperties
     * @param waveData
     */
    virtual void set_vertical_image_data(int beamsShowedCount,
                        const CscanScene::S_CommonProperties &commonProperties,
                                         const DplSource::BeamsPointer &beamsPointer);

    /**
     * @brief scroll_vertical_image     时间Cs扫的垂直滚动image滚动实现
     * @param commonProperties
     */
    void scroll_vertical_image(const CscanScene::S_CommonProperties &commonProperties);

    void drawBackground(QPainter *painter, const QRectF &rect);


    /**
     * @brief draw_c_scan_vertical_image_data   画指定帧的C扫
     * @param beamsShowedCount                  显示第几帧
     * @param commonProperties                  公共的参数
     * @param type                              beam的类型
     * @param beamsPointer                      当前帧数据
     */
    void draw_c_scan_vertical_image_data(int beamsShowedCount,
                                         const CscanScene::S_CommonProperties &commonProperties,
                                         E_BEAM_TYPE type,
                                         const DplSource::BeamsPointer &beamsPointer);

    /**
     * @brief get_peak_value    获取指定beam在闸门內最大值
     * @param beamPointer       正在处理的帧
     * @param beamCount         第beamCount条beam
     * @param gateValue         存储闸门最大数值
     * @return  true 获取成功； false 获取失败
     */
    bool get_peak_value(const DplSource::BeamsPointer &beamsPointer, int beamCount, double &gateValue);


private:
    DplDisplay::PaletteColorPointer m_palette;

    void check_scroll_window(const QSize &oldSize);
};

#endif // __C_SCAN_SCENE_H__
