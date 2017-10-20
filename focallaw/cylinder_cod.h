/**
 * @file cylinder_cod.h
 * @brief  曲面工件外面扫查类
 * @author Long Wen Zhi <longwenzhi@cndoppler.cn>
 * @date 2017-09-28
 */
#ifndef __CYLINDERCOD_H__
#define __CYLINDERCOD_H__

#include "cylinder.h"

namespace DplFocallaw {

class FOCALLAWSHARED_EXPORT CylinderCOD: public Cylinder
{
public:
    explicit CylinderCOD();
    ~CylinderCOD(){}
    InspectionFrom inspection_from() const {return COD;}
};

}
#endif // CYLINDERCOD_H
