/**
 * @file transceiver.h
 * @brief 收发器
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-28
 */
#ifndef __TRANSCEIVER_H__
#define __TRANSCEIVER_H__

#include <fpga/group.h>

namespace DplUt {

class TransceiverPrivate;
class Transceiver : public QObject
{
    Q_OBJECT
public:
    explicit Transceiver(const DplFpga::GroupPointer &fpgaGrp);
    ~Transceiver();

    enum Mode {
        PE,
        PC,
        TT,
        TOFD
    };

    /**
     * @brief mode  获取收发模式
     * @return      模式
     */
    Mode mode() const;

    /**
     * @brief set_mode  设置收发模式
     * @param mode
     */
    void set_mode(Mode mode);

    /**
     * @brief pw    获取脉冲宽度
     * @return      宽度(ns)
     */
    float pw() const;

    /**
     * @brief set_pw    设置脉冲宽度
     * @param w         宽度(ns)
     */
    void set_pw(float w);

    /**
     * @brief filter    获取滤波器对应探头的频率
     * @return          探头频率(KHz)
     */
    int filter() const;

    /**
     * @brief set_filter    设置滤波器对应探头频率
     * @param freq          探头频率(KHz)
     */
    void set_filter(int freq);

    /**
     * @brief rectifier    获取整流器类型
     * @return             类型
     */
    DplFpga::Group::Rectifier rectifier() const;

    /**
     * @brief set_rectifier    设置整流器类型
     * @param val              类型
     */
    void set_rectifier(DplFpga::Group::Rectifier val);
    /**
     * @brief video_filter  获取视频过滤状态
     * @return              开启视频过滤返回true, 否则为false
     */
    bool video_filter() const;

    /**
     * @brief set_video_filter  设置视频过滤状态
     * @param flag              true为开启,false为关闭
     */
    void set_video_filter(bool flag);

    /**
     * @brief averaging 获取平均值类型
     * @return          平均值类型
     */
    DplFpga::Group::Averaging averaging() const;

    /**
     * @brief set_averaging 设置平均值类型
     * @param type          平均值类型
     */
    void set_averaging(DplFpga::Group::Averaging type);

    /**
     * @brief work_time 工作时间
     * @return          时间(ns)
     */
    int work_time(void) const;

signals:
    void mode_changed(DplUt::Transceiver::Mode);
    void pw_changed(float);
    void filter_changed(int);
    void recitifier_changed(DplFpga::Group::Rectifier);
    void video_filter_changed(bool);
    void work_time_changed();

private:
    TransceiverPrivate *d;
};

typedef QSharedPointer<Transceiver> TransceiverPointer;

}

#endif // __TRANSCEIVER_H__
