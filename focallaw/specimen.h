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
        Transverse
    };

    /**
     * @brief velocity  获取声速
     * @param type      波类型
     * @return          声速值(m/s)
     */
    uint velocity(WaveType type);

    /**
     * @brief set_velocity  设置声速
     * @param type          波类型
     * @param val           声速值(m/s)
     */
    void set_velocity(WaveType type, uint v);

private:
    SpecimenPrivate *d_ptr;

    Q_DISABLE_COPY(Specimen)
};

typedef QSharedPointer<Specimen> SpecimenPointer;

}
#endif // __SPECIMEN_H__
