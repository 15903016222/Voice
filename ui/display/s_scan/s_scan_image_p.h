#ifndef __S_SCAN_IMAGE_P_H__
#define __S_SCAN_IMAGE_P_H__

#include "s_scan_image.h"
#include <QReadWriteLock>

struct PointInfo
{
    int pos;        // bits位置
    float rate1;
    float rate2;
    float rate3;
    float rate4;
    int index1;     // 数据索引值1,2,3,4
    int index2;
    int index3;
    int index4;
};

class SscanImagePrivate : public QObject
{
    Q_OBJECT
public:
    explicit SscanImagePrivate(SscanImage *parent,
                               const DplDevice::GroupPointer &group,
                               const DplDisplay::PaletteColorPointer palette);
    ~SscanImagePrivate();

public slots:
    void do_init_matrix();
    void do_init_matrix_changed();

signals:
    void matrix_changed();

protected:
    void init_matrix();
    void init_linear_matrix(int srcWidth, int srcHeight,
                            int srcBytesPerColumn, int destWidth,
                            int destHeight);
    void init_sectorial_matrix(int srcWidth, int srcHeight,
                               int srcBytesPerColumn, int destWidth,
                               int destHeight);

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
