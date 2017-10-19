/**
 * @file measure.h
 * @brief 测量计算类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-19
 */

#ifndef __MEASURE_H__
#define __MEASURE_H__

#include <device/group.h>

#include <QObject>
#include <QMutex>

#define MEASURE_DATA_ND    987654321.123

class Measure : public QObject
{
    Q_OBJECT

public:   
    static Measure *instance();

    enum Type {
        Gate_A_Peak,                            //闸门 A 中测得的信号的峰值波幅
        Gate_AdBA,                              //闸门 A 内峰值幅度与闸门阈值幅度之差(dB)
        Gate_AdBr,                              //闸门 A 内峰值幅度与参考信号幅度之差(dB)
        Gate_B_Peak,                            //闸门 B 中测得的信号的峰值波幅
        Gate_BdBB,                              //闸门 B 内峰值幅度与闸门阈值幅度之差(dB)
        Gate_BdBr,                              //闸门 B 内峰值幅度与参考信号幅度之差(dB)
        Gate_A_Position,                        //闸门 A 内的信号峰值位置
        Gate_B_Position,                        //闸门 B 内的信号峰值位置
        Gate_I_Position,                        //闸门 I 内信号的前沿位置
        Gate_I_Water_Position,                  //闸门 I 内信号的前沿位置(水)
        Thickness,                              //厚度
        ML,                                     //材料损失百分比
        Reference_Cursor_Amplitude,             //参考光标位置的幅度值
        Measurement_Cursor_Amplitude,           //测量光标位置的幅度值
        Measurement_Reference,                  //测量光标减去参考光标的幅度值
        Reference_Cursor_UT_Position,           //参考光标在超声轴上的位置
        Measurement_Cursor_UT_Position,         //测量光标在超声轴上的位置
        Measurement_Reference_UT_Position,      //超声轴上测量光标位置与参考光标位置之差
        Reference_Cursor_Probe_Position,        //相对于参考光标的探头位置
        Measurement_Cursor_Probe_Position,      //相对于测量光标的探头位置
        Measurement_Reference_Probe_position,   //探头相对于测量光标位置与参考光标位置的差值
        Reference_Cursor_Scan_Position,         //扫查轴上参考光标的位置
        Measurement_Cursor_Scan_Position,       //扫查轴上测量光标的位置
        Measurement_Reference_Scan_Position,    //扫查轴上的测量光标位置与参考光标位置之差
        Reference_Cursor_Index_Position,        //步进轴上的参考光标位置
        Measurement_Cursor_Index_Position,      //步进轴上的测量光标位置
        Measurement_Reference_Index_Position,   //步进轴上的测量光标位置与参考光标位置之差
        RA,                                     //声束出射点与闸门A内检测到的缺陷之间的距离
        RB,                                     //声束出射点与闸门B内检测到的缺陷之间的距离
        PA,                                     //探头前表面与闸门A内检测到的缺陷之间的距离
        PB,                                     //探头前表面与闸门B内检测到的缺陷之间的距离
        DA,                                     //闸门A内检测到的缺陷在工件中的深度
        DB,                                     //闸门B内检测到的缺陷在工件中的深度
        SA,                                     //声束出射点与闸门A内检测到的缺陷之间的声程
        SB,                                     //声束出射点与闸门B内检测到的缺陷之间的声程
        ViA,                                    //闸门A中测得的信号指示在步进轴上的空间位置
        ViB,                                    //闸门B中测得的信号指示在步进轴上的空间位置
        VsA,                                    //闸门A中测得的信号指示在扫查轴上的空间位置
        VsB,                                    //闸门B中测得的信号指示在扫查轴上的空间位置
        LA,                                     //从声束入射点到闸门A中测得的信号指示之间声波反射的次数
        LB,                                     //从声束入射点到闸门B中测得的信号指示之间声波反射的次数
        E,                                      //闸门 A 中包络线的峰值波幅
        AWS_DA,                                 //根据 AWS-D1.5 A 标准规定的指示电平
        AWS_DB,                                 //根据 AWS-D1.5 B 标准的零点参考电平
        AWS_DC,                                 //根据 AWS-D1.5 C 标准的衰减系数
        AWS_DD,                                 //根据 AWS-D1.5 D 标准的衰减系数
        AWS_D45,                                //根据 AWS-D1.5 45°标准的不连续性严重等级
        AWS_D60,                                //根据 AWS-D1.5 60°标准的不连续性严重等级
        AWS_D70,                                //根据 AWS-D1.5 70°标准的不连续性严重等级
        AWS_DCL,                                //根据 AWS-D1.5 标准的不连续性严重等级
        T_D_r,                                  //TOFD超声轴方向参考光标深度
        T_D_m,                                  //TOFD超声轴方向测量光标深度
        T_S_mr,                                 //TOFD扫查轴测量光标与参考光标间距
        T_D_mr                                  //TOFD超声轴测量光标与参考光标间距
    };

    /**
     * @brief calculate 计算测量值
     * @param grp       组对象
     * @param type      测量类型
     * @return          测量值
     */
    double calculate(const DplDevice::GroupPointer &grp, Type type);

    /**
     * @brief calculate_str 获取测量值字符串
     * @param grp           组对象
     * @param type          测量类型
     * @return              测量值字符串
     */
    QString calculate_str(const DplDevice::GroupPointer &grp, Type type);

protected:
    explicit Measure();
    ~Measure();

private:
    double gate_a_peak(const DplDevice::GroupPointer &group);
    double gate_adBa(const DplDevice::GroupPointer &group);
    double gate_adBr(const DplDevice::GroupPointer &group);
    double gate_b_peak(const DplDevice::GroupPointer &group);
    double gate_bdBb(const DplDevice::GroupPointer &group);
    double gate_bdBr(const DplDevice::GroupPointer &group);
    double gate_a_position(const DplDevice::GroupPointer &group);
    double gate_b_position(const DplDevice::GroupPointer &group);
    double gate_i_position(const DplDevice::GroupPointer &group);
    double gate_i_water_position(const DplDevice::GroupPointer &group);
    double thickness(const DplDevice::GroupPointer &group);
    double ml(const DplDevice::GroupPointer &group);
    double reference_cursor_amplitude(const DplDevice::GroupPointer &group);
    double measurement_cursor_amplitude(const DplDevice::GroupPointer &group);
    double measurement_reference(const DplDevice::GroupPointer &group);
    double reference_cursor_ut_position(const DplDevice::GroupPointer &group);
    double measurement_cursor_ut_position(const DplDevice::GroupPointer &group);
    double measurement_reference_ut_position(const DplDevice::GroupPointer &group);
    double reference_cursor_probe_position(const DplDevice::GroupPointer &group);
    double measurement_cursor_probe_position(const DplDevice::GroupPointer &group);
    double measurement_reference_probe_position(const DplDevice::GroupPointer &group);
    double reference_cursor_scan_position(const DplDevice::GroupPointer &group);
    double measurement_cursor_scan_position(const DplDevice::GroupPointer &group);
    double measurement_reference_scan_position(const DplDevice::GroupPointer &group);
    double reference_cursor_index_position(const DplDevice::GroupPointer &group);
    double measurement_cursor_index_position(const DplDevice::GroupPointer &group);
    double measurement_reference_index_position(const DplDevice::GroupPointer &group);
    double ra(const DplDevice::GroupPointer &group);
    double rb(const DplDevice::GroupPointer &group);
    double pa(const DplDevice::GroupPointer &group);
    double pb(const DplDevice::GroupPointer &group);
    double da(const DplDevice::GroupPointer &group);
    double db(const DplDevice::GroupPointer &group);
    double sa(const DplDevice::GroupPointer &group);
    double sb(const DplDevice::GroupPointer &group);
    double via(const DplDevice::GroupPointer &group);
    double vib(const DplDevice::GroupPointer &group);
    double vsa(const DplDevice::GroupPointer &group);
    double vsb(const DplDevice::GroupPointer &group);
    double la(const DplDevice::GroupPointer &group);
    double lb(const DplDevice::GroupPointer &group);
    double e(const DplDevice::GroupPointer &group);
    double aws_da(const DplDevice::GroupPointer &group);
    double aws_db(const DplDevice::GroupPointer &group);
    double aws_dc(const DplDevice::GroupPointer &group);
    double aws_dd(const DplDevice::GroupPointer &group);
    double aws_d45(const DplDevice::GroupPointer &group);
    double aws_d60(const DplDevice::GroupPointer &group);
    double aws_d70(const DplDevice::GroupPointer &group);
    double aws_dcl(const DplDevice::GroupPointer &group);
    double t_d_r(const DplDevice::GroupPointer &group);
    double t_d_m(const DplDevice::GroupPointer &group);
    double t_s_mr(const DplDevice::GroupPointer &group);
    double t_d_mr(const DplDevice::GroupPointer &group);

    /* attributions */
    typedef double (Measure::*Function)(const DplDevice::GroupPointer &);
    QMap<Type, Measure::Function> m_map;
};

#endif // __MEASURE_H__
