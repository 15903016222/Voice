/**
 * @file cylinder_cid.h
 * @brief  曲面工件凹面扫查类
 * @author Long Wen Zhi <longwenzhi@cndoppler.cn>
 * @date 2017-09-28
 */
#ifndef __CYLINDERCID_H__
#define __CYLINDERCID_H__

#include "cylinder.h"

namespace DplFocallaw {

class FOCALLAWSHARED_EXPORT CylinderCID: public Cylinder
{
public:
   explicit CylinderCID();
    ~CylinderCID(){}
    InspectionFrom inspection_from() const {return CID;}
};

}


#endif // CYLINDERCID_H
