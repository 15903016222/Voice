#ifndef __DPLUT_RECEIVER_H__
#define __DPLUT_RECEIVER_H__

#include <fpga/group.h>

namespace DplUt {

class ReceiverPrivate;
class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(const DplFpga::GroupPointer &fpgaGrp);
    ~Receiver();

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

signals:
    void filter_changed(int);
    void recitifier_changed(DplFpga::Group::Rectifier);
    void video_filter_changed(bool);

private:
    ReceiverPrivate *d;
};

typedef QSharedPointer<Receiver> ReceiverPointer;
}
#endif // __DPLUT_RECEIVER_H__
