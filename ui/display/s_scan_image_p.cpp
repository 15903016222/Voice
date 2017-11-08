#include "s_scan_image_p.h"

SscanImagePrivate::SscanImagePrivate(const DplDevice::GroupPointer &group) :
    m_group(group),
    m_focallawer(group->focallawer()),
    m_pointSet(NULL),
    m_drawPointQty(0),
    m_pointQty(0),
    m_beamQty(0)
{

}

void SscanImagePrivate::CalcLinearScanNew(int width, int height, int bytesPerLine)
{
    if (m_pointSet) {
        delete m_pointSet;
        m_pointSet = NULL;
        m_drawPointQty = 0;
    }
    m_pointSet = new PointInfo[width * height];

    float tanAngleScaled ;   // tan value of reflect angle after scaled

    float tmpX  ;
    float xxx   ;
    int offset   ;
    float tmpDrawRate ;
    float tmpDataNo   ;

    DplFocallaw::PaProbePointer probe  = m_focallawer->probe().staticCast<DplFocallaw::PaProbe>();
    DplFocallaw::LinearScanCnfPointer scanCnf = probe->scan_configure().staticCast<DplFocallaw::LinearScanCnf>();
    DplUt::SamplePointer sample = m_group->sample();

    float angle = 0;//Dpl::degree2pi(scanCnf->angle());
    int beamQty = m_focallawer->beam_qty() - 1;
    bool direction = false;
    float realHeight  = sample->range() * qCos(angle);
    float scape = 100; //pInfo_->pExitPoint[beamQty] - pInfo_->pExitPoint[0];
    int probeDirection = scape < 0 ? -1 : 0 ;
    float realWidth   = qFabs(sample->range() * qSin(angle)) + qFabs(scape) ;

    if (beamQty == 0) {
        //           if( (angle >=0 && (!direction))
        //                   || ((angle < 0 && direction))) {
        //               //****************************************************************************
        //               //keep the location for angle line drawing
        //               CurrentLine_bottom[group][0].x = width ;
        //               CurrentLine_bottom[group][0].y = height ;

        //               //keep the location for angle line drawing
        //               CurrentLine_top[group][0].x = 0 ;
        //               CurrentLine_top[group][0].y = 0 ;
        //           } else {
        //               //****************************************************************************
        //               //keep the location for angle line drawing
        //               CurrentLine_bottom[group][0].x = 0 ;
        //               CurrentLine_bottom[group][0].y = height ;

        //               //keep the location for angle line drawing
        //               CurrentLine_top[group][0].x = width ;
        //               CurrentLine_top[group][0].y = 0 ;
        //           }
        //****************************************************************************
        return ;
    }

    float xScale = width / realWidth ;
    float yScale = height/ realHeight ;

    float xVacc = qFabs(qTan(angle) * realHeight * xScale) ;
    float beamWidth = width;// - xVacc ;
    tanAngleScaled =  xVacc / height ;
    for (int i = 0; i< height; ++i) {
        tmpX = i * tanAngleScaled ;
        tmpDataNo = (static_cast<float>(i))/ height ;
        for (int j = 0; j<width; ++j) {
            if(!direction) {
                offset  = j + i * bytesPerLine ;
            } else {
                offset  = bytesPerLine - j + i * bytesPerLine;
            }

//            if(angle < 0) {
//                xxx = j - xVacc + tmpX ;
//            } else {
//                xxx = j -  tmpX ;
//            }

//            if( xxx < 0 && xxx >= (width - xVacc)) {
//                continue;
//            }

//            tmpDrawRate = ( xxx / beamWidth ) *  beamQty ;
            tmpDrawRate = ( j / beamWidth ) *  beamQty ;

            m_pointSet[m_drawPointQty].pos = offset;
            if(probeDirection) {
                m_pointSet[m_drawPointQty].beam = beamQty - static_cast<quint8>(tmpDrawRate);
                tmpDrawRate =  qFloor(tmpDrawRate + 1) - tmpDrawRate  ;
            } else {
                m_pointSet[m_drawPointQty].beam = static_cast<quint8>(tmpDrawRate);
                tmpDrawRate =  tmpDrawRate - qFloor(tmpDrawRate);
            }
            m_pointSet[m_drawPointQty].rate = tmpDrawRate * COLOR_STEP;
            m_pointSet[m_drawPointQty].point = m_pointQty * tmpDataNo;
            ++m_drawPointQty;
        }
    }

    /*keep the points for drawing current beam line*/
    {
    //       beamWidth = beamWidth / beamQty ;
    //       int _nBeamNo ;
    //       for(i = 0 ; i<= beamQty ; i++)
    //       {
    //           if(probeDirection) _nBeamNo = beamQty - i;
    //           else _nBeamNo = i ;
    //           if((angle >=0 && (!direction)) || ((angle < 0 && direction)))
    //           {
    //                CurrentLine_top[group][_nBeamNo].x = (int) ( beamWidth * i  + 0.5) ;
    //                CurrentLine_bottom[group][_nBeamNo].x = (int)( beamWidth * i  + 0.5 + xVacc );
    //           }
    //           else
    //           {
    //                CurrentLine_bottom[group][_nBeamNo].x =  (int) (width - beamWidth * i - xVacc + 0.5);
    //                CurrentLine_top[group][_nBeamNo].x   = (int)(width - beamWidth * i + 0.5);
    //           }
    //           CurrentLine_top[group][_nBeamNo].y = 0 ;
    //           CurrentLine_bottom[group][_nBeamNo].y =	height - 1 ;
    //       }
    }
}

void SscanImagePrivate::init_sector_pointSet(int width, int height, int bytesPerLine)
{
    if (m_pointSet) {
        delete m_pointSet;
        m_pointSet = 0;
        m_drawPointQty = 0;
    }
    m_pointSet = new PointInfo[width * height];

    if (m_group->mode() != DplDevice::Group::PA) {
        return;
    }

    DplFocallaw::FocallawerPointer focallawer = m_group->focallawer();
    DplFocallaw::PaProbePointer probe = focallawer->probe().staticCast<DplFocallaw::PaProbe>();
    DplFocallaw::SectorialScanCnfPointer scanCnf = probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
    DplUt::SamplePointer sample = m_group->sample();
    float currentY;
    float currentX;
    float tmp;
    float junction[256];
    float angles[256];
    // get real window size
    float  angleStart = Dpl::degree2pi(scanCnf->first_angle()); // pInfo_->nStartAngle ;
    float  angleStop  = Dpl::degree2pi(scanCnf->last_angle()); // pInfo_->nStopAngle  ;
    float  angleStep  = Dpl::degree2pi(scanCnf->angle_step()); //pInfo_->nStepAngle  ;
    int    beamQty    = focallawer->beam_qty();
    float  sampleStart= sample->start(); // pInfo_->nSampleStart;
    float  sampleRange= sample->range(); // pInfo_->nSampleRange;
    float  sampleStop = sampleStart + sampleRange ;
    float exitPoint[] = {1, 2, 3, 4, 5, 6, 7};//  = pInfo_->pExitPoint;
    int   direction  = 0; //pInfo_->direction; // 扫查方向
    float startX = 0.0;
    float stopX = 0.0;
    float startY = 0.0;
    float stopY = 0.0;
    float stepX = 0.0;
    float stepY = 0.0;

    // get juction of each two beam
    float topLocation[256] = {0.0};
    for(int i = 0 ; i < beamQty - 1; ++i) {
        topLocation[i] = (exitPoint[i] + exitPoint[i+1]) / 2;
    }

    // get real window size
    if (angleStart * angleStop <= 0) {
        startX = exitPoint[0] + sampleStop * qSin(angleStart);
        stopX  = exitPoint[beamQty - 1] + sampleStop * qSin(angleStop);
        stopY  = sampleStop;
        if (qFabs(angleStart) > qFabs(angleStop)) {
            startY = sampleStart * qCos(angleStart);
        } else {
            startY = sampleStart * qCos(angleStop);
        }
    } else if( angleStart < 0 && angleStop < 0) {
        startX = exitPoint[0] + sampleStop * qSin(angleStart);
        stopX  = exitPoint[beamQty -1] + sampleStart * qSin(angleStop);
        startY = sampleStart * qCos(angleStart)  ;
        stopY  = sampleStop * qCos(angleStop) ;
    } else { //( _nAngleStart > 0 && _nAngleStop > 0)
        startX = exitPoint[0] + sampleStart * qSin(angleStart) ;
        stopX  = exitPoint[beamQty - 1] + sampleStop * qSin(angleStop);
        startY = sampleStart * qCos(angleStop)  ;
        stopY  = sampleStop * qCos(angleStart)  ;
    }

    // get real step of each pixel
    stepX = (stopX - startX) / (width - 1) ;
    stepY = (stopY - startY) / (height - 1) ;
    if (qFuzzyIsNull(stepX) || qFuzzyIsNull(stepY)) {
        return;
        //        for (int i = 0; i< beamQty; ++i) {
        //            /* CurrentLine_top/bottom 标尺开始和结束信息 */
        //            CurrentLine_top[group][i].x = 0 ;
        //            CurrentLine_bottom[group][i].x = width  ;

        //            CurrentLine_top[group][i].y = 0 ;
        //            CurrentLine_bottom[group][i].y = height  ;

        //            if (direction) {
        //                CurrentLine_top[group][i].x    = width - CurrentLine_top[group][i].x ;
        //                CurrentLine_bottom[group][i].x = width - CurrentLine_bottom[group][i].x ;
        //            }
        //            return ;
        //        }
    }

    // get all values of angle
    for (int i = 0 ; i < beamQty ; ++i) {
        angles[i] = angleStart + i * angleStep;
    }

    unsigned char t;
    for (int i = 0; i < height; ++i) {
        // current y position
        currentY = startY + i * stepY ;

        // beam junctions with current y coordinates
        for (int k = 0 ; k < beamQty ; k++) {
            junction[k] = exitPoint[k] + qTan(angles[k]) * currentY  ;
        }

        // calculate matrix
        t = 0 ;
        for (int j = 0; j < width; ++j) {
            // get current pixel position in real coordinate
            currentX = startX + stepX * j ;
            for ( ; t< beamQty - 1; t++) {
                // if current position is less than minimun or bigger than maximum  get out
                if (currentX > junction[beamQty - 1] || currentX < junction[0] ) {
                    break;
                }

                if (currentX >= junction[t] && currentX <= junction[t+1] ) {
                    if(direction) {
                        // if draw direction is inverse , transfer the x coordinate
                        m_pointSet[m_drawPointQty].pos = bytesPerLine - j + i * bytesPerLine;
                    } else {
                        m_pointSet[m_drawPointQty].pos = j + i * bytesPerLine;
                    }

                    //                    pAngleZoom[group][tmpIndex] = t;
                    m_pointSet[m_drawPointQty].beam = t;

                    tmp = currentX - topLocation[t];
                    tmp = qSqrt(qPow(currentY, 2)+ qPow(tmp, 2));
                    if (tmp > sampleStop || tmp < sampleStart) {
                        // if current position is out of sample range , get out
                        break;
                    }

                    // get current point data index in data block
                    //                    pDataNo[group][tmpIndex]   = m_pointQty * (tmp - sampleStart) / sampleRange;
                    m_pointSet[m_drawPointQty].point = m_pointQty * (tmp - sampleStart) / sampleRange;
                    if ( qFuzzyIsNull(junction[t+1] - currentX) ) {
                        //                        pDrawRate[group][tmpIndex] = COLOR_STEP;
                        m_pointSet[m_drawPointQty].rate = COLOR_STEP;
                    } else {
                        tmp = qCos(angles[t]) * (currentX - junction[t]) / ( qCos(angles[t+1]) * (junction[t+1] - currentX));
                        tmp = tmp / (1 + tmp) ;
                        //                        pDrawRate[group][tmpIndex] =  tmp * COLOR_STEP ;
                        m_pointSet[m_drawPointQty].rate = tmp * COLOR_STEP;
                    }
                    ++ m_drawPointQty;
                    //                    pDraw[group][tmpIndex]  = -1 ;
                    break ;
                }
            }
        }
    }

    // get each beam start and end pixels
    //    for(int i = 0 ; i< beamQty ; i++) {
    //        tmp  = exitPoint[i] + sampleStart * qSin(angles[i]);
    //        CurrentLine_top[group][i].x = (tmp - startX ) / stepX;
    //        tmp  = exitPoint[i] + sampleStop * qSin( angles[i] );
    //        CurrentLine_bottom[group][i].x = (tmp - startX ) / stepX;

    //        tmp  =  sampleStart * qCos( angles[i] );
    //        CurrentLine_top[group][i].y = (tmp - startY ) / stepY;
    //        tmp  = sampleStop * cos( angles[i] );
    //        CurrentLine_bottom[group][i].y = (tmp - startY ) / stepY;
    //        if(direction) {
    //            CurrentLine_top[group][i].x    = width - CurrentLine_top[group][i].x ;
    //            CurrentLine_bottom[group][i].x = width - CurrentLine_bottom[group][i].x ;
    //        }
    //    }
}

void SscanImagePrivate::init_linear_matrix(int srcWidth, int srcHeight, int srcBytesPerColumn, int destWidth, int destHeight, int destBytesPerLine)
{
    /**
     * formula
     * f(srcX+u, srcY+v) = (1-u)(1-v)f(srcX, srcY)
     *                   + (1-u)vf(srcX, srcY+1)
     *                   + u(1-v)f(srcX+1, srcY)
     *                   + uvf(srcX+1, srcY+1)
     */

    if (m_pointSet) {
        delete m_pointSet;
        m_pointSet = NULL;
    }
    m_pointSet = new PointInfo[destHeight*destWidth];
    m_drawPointQty = 0;

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

            m_pointSet[m_drawPointQty].pos = j*destBytesPerLine + i;

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

void SscanImagePrivate::init_sectorial_matrix(int destWidth, int destHeight)
{
//    DplFocallaw::PaProbePointer probe = m_focallawer->probe().staticCast<DplFocallaw::PaProbe>();
//    DplFocallaw::SectorialScanCnfPointer scanCnf = probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
//    DplUt::SamplePointer sample = m_group->sample();

//    float angleStart = Dpl::degree2pi(scanCnf->first_angle());
//    float angleStop = Dpl::degree2pi(scanCnf->last_angle());
//    float angleStep = Dpl::degree2pi(scanCnf->angle_step());

//    if (m_pointSet) {
//        delete m_pointSet;
//        m_pointSet = NULL;
//    }
//    m_pointSet = new PointInfo[destHeight*destWidth];
//    m_drawPointQty = 0;

//    float r = sample->start() + sample->range();

//    float realStartX = 0.0;     // 真实开始X值
//    float realStopX = 0.0;      // 真实结束X值
//    float realStartY= 0.0;      // 真实开始Y值
//    float realStopY = 0.0;      // 真实结束Y值

//    int beamQty = m_focallawer->beam_qty();
//    float exitPoint[beamQty] = {0.0};

//    if (angleStart * angleStop <= 0) {
//        realStartX = exitPoint[0] + r * qSin(angleStart);
//        realStopX  = exitPoint[beamQty - 1] + r * qSin(angleStop);
//        realStopY  = r;
//        if (qFabs(angleStart) > qFabs(angleStop)) {
//            realStartY = sample->start() * qCos(angleStart);
//        } else {
//            realStartY = sample->start() * qCos(angleStop);
//        }
//    } else if( angleStart < 0 && angleStop < 0) {
//        realStartX = exitPoint[0] + r * qSin(angleStart);
//        realStopX  = exitPoint[beamQty -1] + sample->start() * qSin(angleStop);
//        realStartY = sample->start() * qCos(angleStart)  ;
//        realStopY  = r * qCos(angleStop) ;
//    } else { //( _nAngleStart > 0 && _nAngleStop > 0)
//        realStartX = exitPoint[0] + sample->start() * qSin(angleStart) ;
//        realStopX  = exitPoint[beamQty - 1] + r * qSin(angleStop);
//        realStartY = sample->start() * qCos(angleStop)  ;
//        realStopY  = r * qCos(angleStart)  ;
//    }

//    float widthRatio = (realStopX - realStartX) / (destWidth);
//    float heightRatio = (realStopY - realStopY) / (destHeight);
//    if (qFuzzyIsNull(widthRatio) || qFuzzyIsNull(heightRatio)) {
//        return;
//    }

//    /**
//     * formula
//     * f(srcX+u, srcY+v) = (1-u)(1-v)f(srcX, srcY)
//     *                   + (1-u)vf(srcX, srcY+1)
//     *                   + u(1-v)f(srcX+1, srcY)
//     *                   + uvf(srcX+1, srcY+1)
//     */

//    /**
//     * u = (atan2(y,x)-thetamin)*(thetamax-thetamin)
//     * v = (sqrt(x^2+y^2)-rmin)*(rmax-rmin)
//     */

//    float angle[beamQty] = {0.0};
//    for (int i = 0; i < beamQty; ++i) {
//        angle[i] = angleStart + i*angleStep;
//    }

////#include <QMatrix2x2>

////    QPointF po;
//    float xo[beamQty-1] = {0.0};    //
//    float yo[beamQty-1] = {0.0};
//    for (int i = 0; i < beamQty-1; ++i) {
//        xo[i] = (exitPoint[i+1]*qTan(angle[i]) - exitPoint[i]*qTan(angle[i+1]))
//                / (qTan(angle[i]) - qTan(angle[i+1]));
//        yo[i] = (exitPoint[i+1] - exitPoint[i])
//                / (qTan(angle[i]) - qTan(angle[i+1]));
//    }

//    float realCurrentY = 0.0;
//    float realCrurrentX = 0.0;
//    int beam = 0;

//    float junction[beamQty] = {0.0};
//    float tmp = 0.0;




//    for (int i = 0; i < destHeight; ++i) {
//        realCurrentY = realStartX + heightRatio*i;

//        for (int k = 0; k < beamQty; ++k) {
//            junction[k] = exitPoint[k] + qTan(angle[k]) * realCurrentY;
//        }

//        beam = 0;
//        for (int j = 0; j < destWidth; ++j) {
//            realCrurrentX = realStartX + widthRatio*j;

//            for (; beam < beamQty; ++beam) {
//                if (realCrurrentX > junction[beamQty-1]
//                        || realCrurrentX < junction[0]) {
//                    /* 当前点不在范围内 */
//                    break;
//                }


//            }
//        }
//    }
}
