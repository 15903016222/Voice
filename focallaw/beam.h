/**
 * @file beam.h
 * @brief 光束
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __FOCALLAW_BEAM_H__
#define __FOCALLAW_BEAM_H__

#include "focallaw_global.h"
#include <QSharedPointer>

namespace DplFocallaw {

class BeamPrivate;
class FOCALLAWSHARED_EXPORT Beam
{
    Q_DECLARE_PRIVATE(Beam)
public:
    explicit Beam();
    ~Beam();

    /**
     * @brief txdelay   获取各阵元的发送延迟时间(ns)
     * @return          延迟时间链表
     */
    const QList<float> &txdelay() const;

    /**
     * @brief rxdelay   获取各阵元的接收延迟时间(ns)
     * @return          延迟时间链表
     */
    const QList<float> &rxdelay() const;

    /**
     * @brief clear 清除阵元延迟时间
     */
    void clear();

    /**
     * @brief delay BeamDelay
     * @return      时间(ns)
     */
    float delay() const;

    /**
     * @brief first_tx_element  获取开始发射的阵元号
     * @return                  阵元号，从０开始
     */
    uint first_tx_element() const;

    /**
     * @brief first_rx_element  获取开始接收的阵元号
     * @return                  阵元号，从０开始
     */
    uint first_rx_element() const;

protected:
    friend class FocallawerPrivate;
    BeamPrivate *data() { return d_ptr; }

private:
    BeamPrivate *d_ptr;

};

typedef QSharedPointer<Beam> BeamPointer;

}

#endif // __FOCALLAW_BEAM_H__
