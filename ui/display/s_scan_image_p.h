#ifndef __S_SCAN_IMAGE_P_H__
#define __S_SCAN_IMAGE_P_H__

#include "s_scan_image.h"
#include <QReadWriteLock>

#define COLOR_STEP  4     /*    4  8  16  32  64*/
#define COLOR_SHIFT 2      /*    2  3   4   5   6*/

struct PointInfo
{
    int beam;
    int point;
    quint8 rate;
    float u;
    float v;
    int srcX;
    int srcY;

    int pos;
    float rate1;
    float rate2;
    float rate3;
    float rate4;
    int index1;
    int index2;
    int index3;
    int index4;
};

class SscanImagePrivate : public QObject
{
    Q_OBJECT
public:
    explicit SscanImagePrivate(SscanImage *parent, const DplDevice::GroupPointer &group, const DplDisplay::PaletteColorPointer palette);
    ~SscanImagePrivate();

public slots:
    void do_init_matrix();

    /**
     * @brief init_matrix   初始化插值表
     */
    void init_matrix();

protected:
    /**
     * @brief init_linear_matrix    初始化线扫插值表
     * @param srcWidth              原图像宽度
     * @param srcHeight             原图像高度
     * @param srcBytesPerColumn     原图每列字节数
     * @param destWidth             目标图像宽度
     * @param destHeight            目标图像高度
     */
    void init_linear_matrix(int srcWidth, int srcHeight, int srcBytesPerColumn, int destWidth, int destHeight);

    /**
     * @brief init_linear_matrix    初始化扇扫插值表
     * @param srcWidth              原图像宽度
     * @param srcHeight             原图像高度
     * @param srcBytesPerColumn     原图每列字节数
     * @param destWidth             目标图像宽度
     * @param destHeight            目标图像高度
     */
    void init_sectorial_matrix(int srcWidth, int srcHeight, int srcBytesPerColumn, int destWidth, int destHeight);

public:
    /* attributions */
    DplDevice::GroupPointer m_group;
    PointInfo *m_pointSet;
    int m_drawPointQty;
    DplDisplay::PaletteColorPointer m_palette;
    QReadWriteLock m_rwLock;
    SscanImage *q;
};

#endif // __S_SCAN_IMAGE_P_H__
