#include "s_scan_image_p.h"
#include <QtConcurrentRun>

SscanImagePrivate::SscanImagePrivate(SscanImage *parent, const DplDevice::GroupPointer &group, const DplDisplay::PaletteColorPointer palette) :
    m_group(group),
    m_pointSet(new PointInfo[parent->width()*parent->height()]),
    m_drawPointQty(0),
    m_palette(palette),
    q(parent)
{
    connect(static_cast<DplFocallaw::Focallawer *>(m_group->focallawer().data()),
            SIGNAL(focallawed()),
            this, SLOT(do_init_matrix()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(point_qty_changed(int)),
            this, SLOT(do_init_matrix()));
    init_matrix();
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
}

void SscanImagePrivate::init_linear_matrix(int srcWidth, int srcHeight, int srcBytesPerColumn, int destWidth, int destHeight)
{
    /**
     * formula
     * f(srcX+u, srcY+v) = (1-u)(1-v)f(srcX, srcY)
     *                   + (1-u)vf(srcX, srcY+1)
     *                   + u(1-v)f(srcX+1, srcY)
     *                   + uvf(srcX+1, srcY+1)
     */
    double widthRatio = static_cast<double>(srcWidth) / destWidth;
    double heightRatio = static_cast<double>(srcHeight) / destHeight;

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

void SscanImagePrivate::init_sectorial_matrix(int srcWidth, int srcHeight, int srcBytesPerColumn, int destWidth, int destHeight)
{
    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    DplFocallaw::SectorialScanCnfPointer scanCnf = probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
    DplUt::SamplePointer sample = m_group->sample();

    float angleStart = Dpl::degree2pi(scanCnf->first_angle());
    float angleStop = Dpl::degree2pi(scanCnf->last_angle());
    float angleStep = Dpl::degree2pi(scanCnf->angle_step());

    float sampleStart = sample->start();
    float sampleRange = sample->range();
    float sampleStop = sampleStart + sampleRange;
    int beamQty = srcWidth;
    int pointQty = srcHeight;
    float inPoint[beamQty];                 // 入射点X值
    for (int i = 0; i < beamQty; ++i) {
        inPoint[i] = 0.0;
    }

    /* 计算真实的坐标点 */
    float realStartX = 0.0;     // 真实开始X值
    float realStopX = 0.0;      // 真实结束X值
    float realStartY= 0.0;      // 真实开始Y值
    float realStopY = 0.0;      // 真实结束Y值
    if (angleStart * angleStop <= 0) {
        realStartX = inPoint[0] + sampleStop * qSin(angleStart);
        realStopX  = inPoint[beamQty - 1] + sampleStop * qSin(angleStop);
        realStopY  = sampleStop;
        if (qFabs(angleStart) > qFabs(angleStop)) {
            realStartY = sample->start() * qCos(angleStart);
        } else {
            realStartY = sample->start() * qCos(angleStop);
        }
    } else if( angleStart < 0 && angleStop < 0) {
        realStartX = inPoint[0] + sampleStop * qSin(angleStart);
        realStopX  = inPoint[beamQty -1] + sample->start() * qSin(angleStop);
        realStartY = sample->start() * qCos(angleStart);
        realStopY  = sampleStop * qCos(angleStop);
    } else { //( _nAngleStart > 0 && _nAngleStop > 0)
        realStartX = inPoint[0] + sample->start() * qSin(angleStart) ;
        realStopX  = inPoint[beamQty - 1] + sampleStop * qSin(angleStop);
        realStartY = sample->start() * qCos(angleStop);
        realStopY  = sampleStop * qCos(angleStart);
    }

    /* 计算真实长宽与显示的长宽的比例系数 */
    float widthRatio = (realStopX - realStartX) / (destWidth);
    float heightRatio = (realStopY - realStartY) / (destHeight);
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
        curPoint.set_y(realStartY + heightRatio*i);

        /* 计算经过当前点与X轴平等的直线与各beam线的交叉点位置 */
        for (int k = 0; k < beamQty; ++k) {
            juncPoint[k].set(inPoint[k] + qTan(angle[k]) * curPoint.y(),
                             curPoint.y());
//            qDebug("%s[%d]: junctionPoint(%f, %f)",__func__, __LINE__, juncPoint[k].x(), juncPoint[k].y());
        }

        curBeam = 0;
        for (int j = 0; j < destWidth; ++j) {
            curPoint.set_x(realStartX + widthRatio*j);

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
