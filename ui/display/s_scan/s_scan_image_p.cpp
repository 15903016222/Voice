#include "s_scan_image_p.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtConcurrent/QtConcurrent>
#else
#include <QtConcurrentRun>
#endif

SscanImagePrivate::SscanImagePrivate(SscanImage *parent,
                                     const DplDevice::GroupPointer &group,
                                     const DplDisplay::PaletteColorPointer palette) :
    m_group(group),
    m_pointSet(new PointInfo[parent->width()*parent->height()]),
    m_drawPointQty(0),
    m_palette(palette),
    q(parent)
{
    do_init_matrix();
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(point_qty_changed(int)),
            this, SLOT(do_init_matrix()));
    connect(static_cast<DplDisplay::Sscan *>(m_group->s_scan().data()),
            SIGNAL(xy_changed()),
            this, SLOT(do_init_matrix()));
    connect(this, SIGNAL(matrix_changed()),
            this, SLOT(do_init_matrix_changed()), Qt::QueuedConnection);
}

SscanImagePrivate::~SscanImagePrivate()
{
    QWriteLocker l(&m_rwLock);
    if (m_pointSet) {
        delete m_pointSet;
        m_drawPointQty = 0;
    }
}

void SscanImagePrivate::do_init_matrix()
{
    QtConcurrent::run(this,&SscanImagePrivate::init_matrix);
}

void SscanImagePrivate::do_init_matrix_changed()
{
    q->fill(Qt::black);
}

/**
 * @brief init_matrix   初始化插值表
 */
void SscanImagePrivate::init_matrix()
{
    QWriteLocker l(&m_rwLock);
    m_drawPointQty = 0;

    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
        init_linear_matrix(m_group->focallawer()->beam_qty(),
                           m_group->sample()->point_qty(),
                           m_group->sample()->point_qty() + DplSource::Beam::MEASURE_SIZE,
                           q->width(), q->height());
    } else {
        init_sectorial_matrix(m_group->focallawer()->beam_qty(),
                              m_group->sample()->point_qty(),
                              m_group->sample()->point_qty() + DplSource::Beam::MEASURE_SIZE,
                              q->width(), q->height());
    }
    emit matrix_changed();
}

/**
 * @brief init_linear_matrix    初始化线扫插值表
 * @param srcWidth              原图像宽度
 * @param srcHeight             原图像高度
 * @param srcBytesPerColumn     原图每列字节数
 * @param destWidth             目标图像宽度
 * @param destHeight            目标图像高度
 */
void SscanImagePrivate::init_linear_matrix(int srcWidth, int srcHeight,
                                           int srcBytesPerColumn, int destWidth,
                                           int destHeight)
{
    /**
     * formula
     * f'(srcX+u, srcY+v) = (1-u)(1-v)f(srcX, srcY)
     *                   + (1-u)vf(srcX, srcY+1)
     *                   + u(1-v)f(srcX+1, srcY)
     *                   + uvf(srcX+1, srcY+1)
     */
    double widthRatio = (srcWidth-1.0) / (destWidth-1.0);
    double heightRatio = (srcHeight-1.0) / (destHeight-1.0);

    float u = 0.0;
    float v = 0.0;
    int srcX = 0;
    int srcY = 0;

    for (int i = 0; i < destWidth; ++i) {
        u = i * widthRatio;
        srcX = qFloor(u);
        u = u - srcX;
        for (int j = 0; j < destHeight; ++j) {
            v = j * heightRatio;
            srcY = qFloor(v);
            v = v - srcY;

            m_pointSet[m_drawPointQty].pos = j*destWidth + i;

            m_pointSet[m_drawPointQty].rate1 = (1-u)*(1-v);
            m_pointSet[m_drawPointQty].rate2 = (1-u)*v;
            m_pointSet[m_drawPointQty].rate3 = u*(1-v);
            m_pointSet[m_drawPointQty].rate4 = u*v;

            m_pointSet[m_drawPointQty].index1 = srcX * srcBytesPerColumn + srcY;
            m_pointSet[m_drawPointQty].index2 = srcX * srcBytesPerColumn;

            if (srcX + 1 >= srcWidth) {
                m_pointSet[m_drawPointQty].index3 = srcX * srcBytesPerColumn;
                m_pointSet[m_drawPointQty].index4 = srcX * srcBytesPerColumn;
            } else {
                m_pointSet[m_drawPointQty].index3 = (srcX + 1) * srcBytesPerColumn;
                m_pointSet[m_drawPointQty].index4 = (srcX + 1) * srcBytesPerColumn;
            }

            m_pointSet[m_drawPointQty].index3 += srcY;
            if (srcY + 1 >= srcHeight) {
                m_pointSet[m_drawPointQty].index2 += srcY;
                m_pointSet[m_drawPointQty].index4 += srcY;
            } else {
                m_pointSet[m_drawPointQty].index2 += (srcY+1);
                m_pointSet[m_drawPointQty].index4 += (srcY+1);
            }

            ++m_drawPointQty;
        }
    }
}

/**
 * @brief init_linear_matrix    初始化扇扫插值表
 * @param srcWidth              原图像宽度
 * @param srcHeight             原图像高度
 * @param srcBytesPerColumn     原图每列字节数
 * @param destWidth             目标图像宽度
 * @param destHeight            目标图像高度
 */
void SscanImagePrivate::init_sectorial_matrix(int srcWidth, int srcHeight,
                                              int srcBytesPerColumn,
                                              int destWidth, int destHeight)
{
    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    DplFocallaw::SectorialScanCnfPointer scanCnf = probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
    DplUt::SamplePointer sample = m_group->sample();
    DplDisplay::SscanPointer sScan = m_group->s_scan();

    float angleStart = Dpl::degree2pi(scanCnf->first_angle());
    float angleStep = Dpl::degree2pi(scanCnf->angle_step());

    float sampleStart = sample->start();
    float sampleRange = sample->range();
    float sampleStop = sampleStart + sampleRange;
    int beamQty = srcWidth;
    int pointQty = srcHeight;
    float inPoint[beamQty];                 // 入射点X值
    QList<DplFocallaw::BeamPointer> beams = m_group->focallawer()->beams();
    for (int i = 0; i < beamQty; ++i) {
        inPoint[i] = beams[i]->field_distance();
    }

    /* 计算真实长宽与显示的长宽的比例系数 */
    float widthRatio = sScan->width() / (destWidth);
    float heightRatio = sScan->height() / (destHeight);
    if (qFuzzyIsNull(widthRatio) || qFuzzyIsNull(heightRatio)) {
        return;
    }

    /* 计算每条beam的入射角度 */
    float angle[beamQty];
    for (int i = 0; i < beamQty; ++i) {
        angle[i] = angleStart + i*angleStep;
    }

    /* 计算每两条beam的交点位置 */
    DplFocallaw::Point<float> crossPoints[beamQty-1];
    for (int i = 0; i < beamQty-1; ++i) {
        crossPoints[i].set((inPoint[i+1]*qTan(angle[i]) - inPoint[i]*qTan(angle[i+1]))
                / (qTan(angle[i]) - qTan(angle[i+1])),
                (inPoint[i+1] - inPoint[i])
                / (qTan(angle[i]) - qTan(angle[i+1])));
        qDebug("%s[%d]: crossPoint(%f, %f)",__func__, __LINE__, crossPoints[i].x(), crossPoints[i].y());
    }

    int curBeam = 0;

    DplFocallaw::Point<float> curPoint; // 当前真实点
    DplFocallaw::Point<float> juncPoint[beamQty];

    float len = 0.0;
    float u = 0.0;
    float v = 0.0;
    int srcX = 0;
    int srcY = 0;
    float curAngle = 0;

    for (int i = 0; i < destHeight; ++i) {
        curPoint.set_y(sScan->start_y() + heightRatio*i);

        /* 计算经过当前点与X轴平等的直线与各beam线的交叉点位置 */
        for (int k = 0; k < beamQty; ++k) {
            juncPoint[k].set(inPoint[k] + qTan(angle[k]) * curPoint.y(),
                             curPoint.y());
//            qDebug("%s[%d]: junctionPoint(%f, %f)",__func__, __LINE__, juncPoint[k].x(), juncPoint[k].y());
        }

        curBeam = 0;
        for (int j = 0; j < destWidth; ++j) {
            curPoint.set_x(sScan->start_x() + widthRatio*j);

            for (; curBeam < beamQty-1; ++curBeam) {
                if (curPoint.x() > juncPoint[beamQty-1].x()
                        || curPoint.x() < juncPoint[0].x()) {
//                    qDebug("%s[%d]: juncPoint(%f, %f)",__func__, __LINE__, juncPoint[0].x(), juncPoint[beamQty-1].x());
                    break;
                }
                if (curPoint.x() < juncPoint[curBeam].x()
                        || curPoint.x() > juncPoint[curBeam+1].x()) {
                    continue;
                }

                if (qFuzzyIsNull(juncPoint[curBeam].distance(crossPoints[curBeam]))) {
                    len = 0.0;
                } else {
                    len = curPoint.distance(crossPoints[curBeam])
                            * juncPoint[curBeam].distance(DplFocallaw::Point<float>(inPoint[curBeam]))
                            /juncPoint[curBeam].distance(crossPoints[curBeam]);
                }
                if (len > sampleStop || len < sampleStart) {
                    break;
                }
                v = pointQty * (len-sampleStart)/sampleRange;
                srcY = qFloor(v);
                v = v - srcY;
                curAngle = qAtan2((curPoint.y() - crossPoints[curBeam].y()),(curPoint.x() - crossPoints[curBeam].x()));
                srcX = curBeam;
//                qDebug("%s[%d]: curAgnel(%f)",__func__, __LINE__, curAngle*180/M_PI);
                u = (M_PI - (M_PI_2 + angle[curBeam]) - curAngle) / angleStep;
//                qDebug("%s[%d]: curAngle(%f) len(%f) src(%d, %d) uv(%f, %f)", __func__, __LINE__,
//                       curAngle*180/M_PI, len,
//                       srcX, srcY, u, v);

                m_pointSet[m_drawPointQty].pos = i*destWidth + j;

                m_pointSet[m_drawPointQty].rate1 = (1-u)*(1-v);
                m_pointSet[m_drawPointQty].rate2 = (1-u)*v;
                m_pointSet[m_drawPointQty].rate3 = u*(1-v);
                m_pointSet[m_drawPointQty].rate4 = u*v;

                m_pointSet[m_drawPointQty].index1 = srcX * srcBytesPerColumn + srcY;
                m_pointSet[m_drawPointQty].index2 = srcX * srcBytesPerColumn;

                if (srcX + 1 >= srcWidth) {
                    m_pointSet[m_drawPointQty].index3 = srcX * srcBytesPerColumn;
                    m_pointSet[m_drawPointQty].index4 = srcX * srcBytesPerColumn;
                } else {
                    m_pointSet[m_drawPointQty].index3 = (srcX + 1) * srcBytesPerColumn;
                    m_pointSet[m_drawPointQty].index4 = (srcX + 1) * srcBytesPerColumn;
                }

                m_pointSet[m_drawPointQty].index3 += srcY;
                if (srcY + 1 >= srcHeight) {
                    m_pointSet[m_drawPointQty].index2 += srcY;
                    m_pointSet[m_drawPointQty].index4 += srcY;
                } else {
                    m_pointSet[m_drawPointQty].index2 += (srcY+1);
                    m_pointSet[m_drawPointQty].index4 += (srcY+1);
                }

                ++m_drawPointQty;
                break;
            }
        }
    }
}
