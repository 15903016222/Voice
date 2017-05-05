/**
 * @file probe.h
 * @brief 探头基类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */
#ifndef __PROBE_H__
#define __PROBE_H__

#include "focallaw_global.h"
#include <QSharedPointer>

namespace DplFocallaw {

class ProbePrivate;
class FOCALLAWSHARED_EXPORT Probe : public QObject
{
    Q_DECLARE_PRIVATE(Probe)
    Q_OBJECT
public:   
    explicit Probe(QObject *parent = 0);
    ~Probe();

    virtual bool is_pa() const = 0;

    /**
     * @brief load  加载探头文件
     * @param file  探头文件
     * @return      成功返回true， 否则false
     */
    virtual bool load(const QString &fileName);

    /**
     * @brief save  保存探头数据
     * @param file  保存文件
     * @return      成功返回true，否则false
     */
    virtual bool save(const QString &fileName);

    /**
     * @brief serial    获取探头系列号
     * @return          探头系列号
     */
    const QString &serial() const;

    /**
     * @brief set_serial    设置探头系列号
     * @param serial        探头系列号
     */
    void set_serial(const QString &serial);

    /**
     * @brief model 获取探头型号
     * @return      型号
     */
    const QString &model() const;

    /**
     * @brief set_model 设置探头型号
     * @param model     探头型号
     */
    void set_model(const QString &model);

    /**
     * @brief The Type enum 探头类型
     */
    enum Type {
        CONTACT,    /* 直接接触式类型 */
        DELAY,      /* 延迟块式 */
        IMMERSION,  /* 水浸式 */
        ANGLE_BEAM, /* 角度声速类型 */
        DUAL,       /* 双晶探头，UT专有 */
        TOFD        /* Tofd探头，UT专有 */
    };

    /**
     * @brief type  获取探头类型
     * @return      探头类型
     */
    Type type() const;

    /**
     * @brief set_type  设置探头类型
     * @param type      探头类型
     */
    void set_type(Type type);

    /**
     * @brief freq  获取频率
     * @return      频率(MHz)
     */
    double freq() const;

    /**
     * @brief set_freq  设置频率
     * @param val       频率(MHz)
     */
    void set_freq(double val);

    /**
     * @brief pulser_index  获取发射通道索引号
     * @return              索引号，从０开始
     */
    uint pulser_index() const;

    /**
     * @brief set_pulser_index  设置发射通道索引号
     * @param index             索引号，从０开始
     */
    void set_pulser_index(uint index);

    /**
     * @brief receiver_index    获取接收通道索引号
     * @return                  索引号，从０开始
     */
    uint receiver_index() const;

    /**
     * @brief set_receiver_index    设置接收通道索引号
     * @param index                 索引号，从０开始
     */
    void set_receiver_index(uint index);

private:
    ProbePrivate *d_ptr;
};

typedef QSharedPointer<Probe> ProbePointer;

}
#endif // PROBE_H
