/**
 * @file wedge.h
 * @brief 锲块
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __WEDGE_H__
#define __WEDGE_H__

#include "focallaw_global.h"
#include <QObject>
#include <QSharedPointer>

namespace DplFocallaw {

class WedgePrivate;

class FOCALLAWSHARED_EXPORT Wedge : public QObject
{
    Q_DECLARE_PRIVATE(Wedge)
    Q_OBJECT
public:
    explicit Wedge(QObject *parent=0);
    explicit Wedge(const Wedge &w, QObject *parent=0);

    ~Wedge();

    /**
     * @brief load      加载楔块文件
     * @param fileName  文件名
     * @return          成功返回true,失败返回false
     */
    bool load(const QString &fileName);

    /**
     * @brief save      保存楔块文件
     * @param fileName  文件名
     * @return          成功返回true，失败返回false
     */
    bool save(const QString &fileName) const;

    /**
     * @brief serial    获取系列号
     * @return          系列号
     */
    const QString &serial() const;

    /**
     * @brief set_serial    设置系列号
     * @param val           系列号
     */
    void set_serial(const QString &val);

    /**
     * @brief model 获取型号
     * @return      型号
     */
    const QString &model() const;

    /**
     * @brief set_model 设置型号
     * @param val       型号
     */
    void set_model(const QString &val);

    /**
     * @brief angel 获取角度
     * @return      角度值(°)
     */
    float angle() const;

    /**
     * @brief set_angel 设置角度
     * @param val       角度值(°)
     */
    void set_angle(float val);

    /**
     * @brief roof_angle    获取roof角度，即次轴与步进轴的夹角
     * @return              角度值(°)
     */
    float roof_angle() const;

    /**
     * @brief set_root_angle    设置root angle值
     * @param val               角度值(°)
     */
    void set_root_angle(float val);

    /**
     * @brief velocity  获取纵波声速
     * @return          声速值(m/s)
     */
    quint32 velocity() const;

    /**
     * @brief set_velocity  设置纵波声速
     * @param val           声速值(m/s)
     */
    void set_velocity(quint32 val);

    /**
     * @brief primary_offset    主轴偏置
     * @return                  偏置值(mm)
     */
    float primary_offset()const;

    /**
     * @brief set_primary_offset    设置主轴偏置
     * @param val                   偏置值(mm)
     */
    void set_primary_offset(float val);

    /**
     * @brief secondary_offset  次轴偏置
     * @return                  偏置值(mm)
     */
    float secondary_offset() const;

    /**
     * @brief set_secondary_offset  设置次轴偏置
     * @param val                   偏置值(mm)
     */
    void set_secondary_offset(float val);

    /**
     * @brief first_element_height  获取第一阵元高度
     * @return                      高度值(mm)
     */
    float first_element_height() const;

    /**
     * @brief set_first_element_height  设置第一阵元高度
     * @param val                       高度值(mm)
     */
    void set_first_element_height(float val);

    /**
     * @brief length    获取长度
     * @return          长度值(mm)
     */
    float length() const;

    /**
     * @brief set_lenght    设置长度
     * @param val           长度值(mm)
     */
    void set_length(float val);

    /**
     * @brief width 获取宽度
     * @return      宽度值(mm)
     */
    float width() const;

    /**
     * @brief set_width 设置宽度值
     * @param val       宽度值(mm)
     */
    void set_width(float val);

    /**
     * @brief height    获取高度值
     * @return          高度值(mm)
     */
    float height() const;

    /**
     * @brief set_height    设置高度值
     * @param val           高度值(mm)
     */
    void set_height(float val);

    /**
     * @brief The Orientation enum  探头方向
     */
    enum Orientation {
        Normal,
        Reversal
    };

    /**
     * @brief orientation   获取探头方向
     * @return              方向
     */
    Orientation orientation() const;

    /**
     * @brief set_orientation   设置探头方向
     * @param val               方向
     */
    void set_orientation(Orientation val);

    /**
     * @brief delay 获取锲块延迟时间
     * @return      时间(ns)
     */
    int delay() const;

    /**
     * @brief set_delay 设置锲块延迟时间
     * @param val       时间(ns)
     */
    void set_delay(int val);

    Wedge &operator=(const Wedge &w);

signals:
    void delay_changed(int val);

private:
    WedgePrivate *d_ptr;
};

typedef QSharedPointer<Wedge> WedgePointer;

}

#endif // __WEDGE_H__
