/**
 * @file specimen.h
 * @brief 工件基类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-23
 */
#ifndef __SPECIMEN_H__
#define __SPECIMEN_H__

#include "focallaw_global.h"
#include <QSharedPointer>

namespace DplFocallaw {

class SpecimenPrivate;
class FOCALLAWSHARED_EXPORT Specimen
{
    Q_DECLARE_PRIVATE(Specimen)
public:
    explicit Specimen();
    virtual ~Specimen();

    enum Type {
        FLAT,
        CYLINDER
    };

    virtual Type type() const = 0;

    /**
     * @brief The WaveType enum 波类型
     */
    enum WaveType {
        Longitudinal,
        Shear
    };

    /**
     * @brief wave_type 获取在试块传播的波类型
     * @return          波类型
     */
    WaveType wave_type() const;

    /**
     * @brief set_wave_type 设置在试块传播的波类型
     * @param type          波类型
     */
    void set_wave_type(WaveType type);

    /**
     * @brief velocity  获取对应波类型的声速
     * @return          声速值(m/s)
     */
    uint velocity() const;

    /**
     * @brief set_velocity  设置对应波类型的声速
     * @param val           声速值(m/s)
     */
    void set_velocity(uint v);

private:
    SpecimenPrivate *d_ptr;

    Q_DISABLE_COPY(Specimen)
};

typedef QSharedPointer<Specimen> SpecimenPointer;

}
#endif // __SPECIMEN_H__
