#ifndef __CYLINDRER_H__
#define __CYLINDRER_H__

#include "specimen.h"

namespace DplFocallaw {

class CylinderPrivate;
class FOCALLAWSHARED_EXPORT Cylinder : public Specimen
{
    Q_DECLARE_PRIVATE(Cylinder)
public:
    explicit Cylinder();
    ~Cylinder();

    Type type() const { return CYLINDER; }

    /**
     * @brief inside    获取圆柱内径
     * @return          内径值(mm)
     */
    float inside() const;

    /**
     * @brief set_inside    设置圆柱内径
     * @param val           内径值(mm)
     */
    void set_inside(float val);

    /**
     * @brief outside   获取圆柱外径
     * @return          外径值(mm)
     */
    float outside() const;

    /**
     * @brief set_outside   设置圆柱外径
     * @param val           外径值(mm)
     */
    void set_outside(float val);

    /**
     * @brief length    获取圆柱长度
     * @return          长度(mm)
     */
    float length() const;

    /**
     * @brief set_length    设置圆柱长度
     * @param val           长度(mm)
     */
    void set_length(float val);

private:
    CylinderPrivate *d_ptr;
    Q_DISABLE_COPY(Cylinder)
};

}

#endif // __CYLINDRICAL_SPECIMEN_H__
