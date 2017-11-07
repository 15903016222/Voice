#ifndef __S_SCAN_IMAGE_P_H__
#define __S_SCAN_IMAGE_P_H__

#include <device/group.h>

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

class SscanImagePrivate
{
public:
    SscanImagePrivate(const DplDevice::GroupPointer &group);

    void init_linear_pointSet(int w, int h, int bytesPerLine);
    void CalcLinearScanNew(int width, int height, int bytesPerLine);
    void init_sector_pointSet(int w, int h, int bytesPerLine);
    void refresh_config(int width, int height, int beam_no_mx);

    /**
     * @brief init_linear_matrix    初始化线扫插值表
     * @param srcWidth              原图像宽度
     * @param srcHeight             原图像高度
     * @param srcBytesPerColumn     原图每列字节数
     * @param destWidth             目标图像宽度
     * @param destHeight            目标图像高度
     * @param destBytesPerLine      目标图像每行字节数
     */
    void init_linear_matrix(int srcWidth, int srcHeight, int srcBytesPerColumn, int destWidth, int destHeight, int destBytesPerLine);

    /* attributions */
    DplDevice::GroupPointer m_group;
    DplFocallaw::FocallawerPointer m_focallawer;
    PointInfo *m_pointSet;
    int m_drawPointQty;           //
    int m_pointQty;
    int m_beamQty;

    uchar* m_angleZoom;
    uchar* m_draw;
    uchar* m_drawRate;
    int *m_dataNo;
};

#endif // __S_SCAN_IMAGE_P_H__
