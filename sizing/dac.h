/**
 * @file dac.h
 * @brief DAC(Distance Amplitude Correction) 距离幅度校准
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-12-07
 */
#ifndef __DPLSIZING_DAC_H__
#define __DPLSIZING_DAC_H__

#include <QSharedPointer>

namespace DplSizing {

class DacPrivate;
class Dac : public QObject
{
    Q_OBJECT
public:
    static const int MAX_POINT_QTY = 16;

    explicit Dac();

    /**
     * @brief position  获取指定点的位置
     * @param point     指定点索引号(0~MAX_POINT_QTY)
     * @return          位置(ns)
     */
    float position(int point);

    /**
     * @brief set_position  设置指定点的位置
     * @param point         指定点索引号(0~MAX_POINT_QTY)
     * @param pos           位置(ns)
     * @return              设置成功返回true， 失败返回false
     */
    bool set_position(int point, float pos);

    /**
     * @brief amplitude 获取指定点的幅度
     * @param point     点索引号(0~MAX_POINT_QTY)
     * @return          幅度(%)
     */
    float amplitude(int point) const;

    /**
     * @brief set_amplitude 设置指定点的幅度
     * @param point         点索引号(0~MAX_POINT_QTY)
     * @param val           幅度(%)
     * @return              设置成功的返回true, 失败返回false
     */
    bool set_amplitude(int point, float val);

signals:

public slots:

private:
    DacPrivate *d;
};

typedef QSharedPointer<Dac> DacPointer;

}

#endif // __DPLSIZING_DAC_H__
