#ifndef __BEAM_H__
#define __BEAM_H__

#include "focallaw_global.h"
#include <QSharedPointer>

namespace DplFocallaw {

class BeamData;
class FOCALLAWSHARED_EXPORT Beam
{
public:
    explicit Beam();
    ~Beam();

    /**
     * @brief elements_delay    获取各阵元延迟时间
     * @return                  延迟时间链表
     */
    const QList<double> &elements_delay() const;

    /**
     * @brief clear 清除阵元延迟时间
     */
    void clear();

    /**
     * @brief delay BeamDelay
     * @return      BeamDelay
     */
    double delay() const;

    BeamData *data() { return d_ptr; }

private:
    BeamData *d_ptr;

};

typedef QSharedPointer<Beam> BeamPointer;

}

#endif // __BEAM_H__
