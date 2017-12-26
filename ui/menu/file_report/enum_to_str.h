/**
 * @file    enum_to_str.h
 * @brief   报表辅助类，用于枚举转换为字符串；
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __ENUM_TO_STR_H__
#define __ENUM_TO_STR_H__

#include <QObject>

#include <source/axis.h>
#include <source/encoder.h>
#include <fpga/group.h>
#include <focallaw/focus_cnf.h>
#include <focallaw/scan_cnf.h>
#include <ut/global_transceiver.h>

class EnumToStr : public QObject
{
    Q_OBJECT
public:
    explicit EnumToStr(QObject *parent = 0);

    /**
     * @brief gate_synchro_mode 根据闸门同步枚举获取同步显示字符串
     * @param mode              闸门同步枚举
     * @return
     */
    static QString gate_synchro_mode(DplFpga::Group::SynchroMode mode);

    /**
     * @brief encoder_polarity  根据极性枚举获取编码器极性显示字符串
     * @param polarity          极性枚举
     * @return
     */
    static QString encoder_polarity(DplSource::Encoder::Polarity polarity);

    /**
     * @brief encoder_name  根据扫查驱动枚举获取编码器显示字符串
     * @param driving       扫查驱动枚举
     * @return
     */
    static QString encoder_name(DplSource::Axis::Driving driving);

    /**
     * @brief encoder_mode  编码器模式显示字符串
     * @param mode          编码器模式枚举
     * @return
     */
    static QString encoder_mode(DplSource::Encoder::Mode mode);


    /**
     * @brief focallawer_focal_type 聚焦模式显示字符串
     * @param mode                  聚焦模式枚举
     * @return
     */
    static QString focallawer_focal_type(DplFocallaw::FocusCnf::Mode mode);

    /**
     * @brief focallawer_law_type   扫查方式显示字符串
     * @param mode                  扫查模式枚举
     * @return
     */
    static QString focallawer_law_type(DplFocallaw::ScanCnf::Mode mode);


    /**
     * @brief video_filter  获取视频滤波开关状态字符串
     * @param enable        视频滤波状态
     * @return
     */
    static QString video_filter(bool enable);

    /**
     * @brief voltage   获取发射电压显示字符串
     * @param voltage   发射电压枚举值
     * @return
     */
    static QString voltage(DplUt::GlobalTransceiver::Voltage voltage);

    /**
     * @brief rectifier 获取整流器显示字符串
     * @param rectifier 整流器枚举值
     * @return
     */
    static QString rectifier(DplFpga::Group::Rectifier rectifier);

    /**
     * @brief rx_tx_mode 获取发射接收模式
     * @param mode       整流器模式枚举值
     * @return
     */
    static QString rx_tx_mode(DplUt::Transceiver::Mode mode);

    /**
     * @brief band_pass_filter  频率显示字符串
     * @param index             频率index
     * @param isPa              Pa标志
     * @return
     */
    static QString band_pass_filter(int index, bool isPa);

};


#endif // __ENUM_TO_STR_H__
