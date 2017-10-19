#include "measure.h"

#include <device/device.h>
#include <source/beams.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <QDebug>
#include <QThread>

Measure *Measure::instance()
{
    static Measure *s_calculation = new Measure();
    return s_calculation;
}

float Measure::calculate(DplDevice::GroupPointer &grp, Measure::Type type)
{
    Measure::Function pFun = m_map.value(type);
    if (pFun == NULL) {
        return 0.0;
    }
    return (this->*pFun)(grp);
}

Measure::Measure()
{
    m_map.insert(Gate_A_Peak, &Measure::gate_a_peak);
    m_map.insert(Gate_AdBA, &Measure::gate_adBa);
    m_map.insert(Gate_AdBr, &Measure::gate_adBr);
    m_map.insert(Gate_B_Peak, &Measure::gate_b_peak);
    m_map.insert(Gate_BdBB, &Measure::gate_bdBb);
    m_map.insert(Gate_BdBr, &Measure::gate_bdBr);
    m_map.insert(Gate_A_Position, &Measure::gate_a_position);
    m_map.insert(Gate_B_Position, &Measure::gate_b_position);
    m_map.insert(Gate_I_Position, &Measure::gate_i_position);
    m_map.insert(Gate_I_Water_Position, &Measure::gate_i_water_position);
    m_map.insert(Thickness, &Measure::thickness);
    m_map.insert(ML, &Measure::ml);
    m_map.insert(Reference_Cursor_Amplitude, &Measure::reference_cursor_amplitude);
    m_map.insert(Measurement_Cursor_Amplitude, &Measure::measurement_cursor_amplitude);
    m_map.insert(Measurement_Reference, &Measure::measurement_reference);
    m_map.insert(Reference_Cursor_UT_Position, &Measure::reference_cursor_ut_position);
    m_map.insert(Measurement_Cursor_UT_Position, &Measure::measurement_cursor_ut_position);
    m_map.insert(Measurement_Reference_UT_Position, &Measure::measurement_reference_ut_position);
    m_map.insert(Reference_Cursor_Probe_Position, &Measure::reference_cursor_probe_position);
    m_map.insert(Measurement_Cursor_Probe_Position, &Measure::measurement_cursor_probe_position);
    m_map.insert(Measurement_Reference_Probe_position, &Measure::measurement_reference_probe_position);
    m_map.insert(Reference_Cursor_Scan_Position, &Measure::reference_cursor_scan_position);
    m_map.insert(Measurement_Cursor_Scan_Position, &Measure::measurement_cursor_scan_position);
    m_map.insert(Measurement_Reference_Scan_Position, &Measure::measurement_reference_scan_position);
    m_map.insert(Reference_Cursor_Index_Position, &Measure::reference_cursor_index_position);
    m_map.insert(Measurement_Cursor_Index_Position, &Measure::measurement_cursor_index_position);
    m_map.insert(Measurement_Reference_Index_Position, &Measure::measurement_reference_index_position);
    m_map.insert(RA, &Measure::ra);
    m_map.insert(RB, &Measure::rb);
    m_map.insert(PA, &Measure::pa);
    m_map.insert(PB, &Measure::pb);
    m_map.insert(DA, &Measure::da);
    m_map.insert(DB, &Measure::db);
    m_map.insert(SA, &Measure::sa);
    m_map.insert(SB, &Measure::sb);
    m_map.insert(ViA, &Measure::via);
    m_map.insert(ViB, &Measure::vib);
    m_map.insert(VsA, &Measure::vsa);
    m_map.insert(VsB, &Measure::vsb);
    m_map.insert(LA, &Measure::la);
    m_map.insert(LB, &Measure::lb);
    m_map.insert(E, &Measure::e);
    m_map.insert(AWS_DA, &Measure::aws_da);
    m_map.insert(AWS_DB, &Measure::aws_db);
    m_map.insert(AWS_DC, &Measure::aws_dc);
    m_map.insert(AWS_DD, &Measure::aws_dd);
    m_map.insert(AWS_D45, &Measure::aws_d45);
    m_map.insert(AWS_D60, &Measure::aws_d60);
    m_map.insert(AWS_D70, &Measure::aws_d70);
    m_map.insert(AWS_DCL, &Measure::aws_dcl);
    m_map.insert(T_D_r, &Measure::t_d_r);
    m_map.insert(T_D_m, &Measure::t_d_m);
    m_map.insert(T_S_mr, &Measure::t_s_mr);
    m_map.insert(T_D_mr, &Measure::t_d_mr);
}

Measure::~Measure()
{
}

/*  A%: 闸门 A 中测得的信号的峰值波幅  */
float Measure::gate_a_peak(DplDevice::GroupPointer &group)
{
    return group->current_beam()->gate_peak(DplSource::Beam::GATE_A);
}

/*  AdBA: 闸门 A 内峰值幅度与闸门阈值幅度之差(dB)  */
float Measure::gate_adBa(DplDevice::GroupPointer &group)
{
    return group->current_beam()->gate_minus(DplSource::Beam::GATE_A,
                                                      group->gate_a()->height());
}

/*  AdBr: 闸门 A 内峰值幅度与参考信号幅度之差(dB)  */
float Measure::gate_adBr(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"umimplemented";
    return 10.0;
}

/*  B%: 闸门 B 中测得的信号的峰值波幅  */
float Measure::gate_b_peak(DplDevice::GroupPointer &group)
{
    return group->current_beam()->gate_peak(DplSource::Beam::GATE_B);
}

/*  BdBB: 闸门 B 内峰值幅度与闸门阈值幅度之差(dB)  */
float Measure::gate_bdBb(DplDevice::GroupPointer &group)
{
    return group->current_beam()->gate_minus(DplSource::Beam::GATE_B,
                                                      group->gate_b()->height());
}

/*  BdBr: 闸门 B 内峰值幅度与参考信号幅度之差(dB)  */
float Measure::gate_bdBr(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"umimplemented";
    return 0;
}

/*  A^: 闸门 A 内的信号峰值位置  */
float Measure::gate_a_position(DplDevice::GroupPointer &group)
{
    if (group->gate_a()->height() > fabs(group->current_beam()->gate_peak(DplSource::Beam::GATE_A))) {
        return MEASURE_DATA_ND;
    }

    if (group->ut_unit() == DplDevice::Group::Time) {
        return group->current_beam()->gate_peak_position(DplSource::Beam::GATE_A) / 1000;
    } else {
        return group->current_beam()->gate_peak_position(DplSource::Beam::GATE_A) * group->focallawer()->specimen()->velocity() / 200000;
    }
}

/*  B^: 闸门 B 内的信号峰值位置  */
float Measure::gate_b_position(DplDevice::GroupPointer &group)
{
    if (group->gate_b()->height() > fabs(group->current_beam()->gate_peak(DplSource::Beam::GATE_B))) {
        return MEASURE_DATA_ND;
    }

    if (group->ut_unit() == DplDevice::Group::Time) {
        return group->current_beam()->gate_peak_position(DplSource::Beam::GATE_B) / 1000;
    } else {
        return group->current_beam()->gate_peak_position(DplSource::Beam::GATE_B) * group->focallawer()->specimen()->velocity() / 200000;
    }
}

/*  I/: 闸门 I 内信号的前沿位置  */
float Measure::gate_i_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少闸门I内波形前沿的位置
    return 0;
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_i_height();
//    int _nDataPos = beam->gate_i_position();// 单位: ns
//    int _nGateIHeight = group->gate_i_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 I%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);// I%
//    }

//    if(_nGateIHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
//        float _nVelocity = group->velocity();// 单位: m/s
//        if(group->ut_unit() == DplDevice::Group::Time) {
//            _nMeasureData = _nDataPos / 1000;// 单位: 微秒
//        } else {
//            _nMeasureData = _nDataPos * _nVelocity / 200000;// 单位: mm
//        }
//    }
//    return _nMeasureData;
}

/*  I(w)/: 闸门 I 内信号的前沿位置(水) */
float Measure::gate_i_water_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少闸门I内波形前沿的位置
    return 0;
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_i_height();
//    int _nDataPos = beam->gate_i_position();// 单位: ns
//    int _nGateIHeight = group->gate_i_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;//满屏时200% 4095 I%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);// I%
//    }

//    if(_nGateIHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
//        if(group->ut_unit() == DplDevice::Group::Time) {
//            _nMeasureData = _nDataPos / 1000;
//        } else {
//            float _nVelocity = 1480;// 单位: m/s
//            _nMeasureData = _nDataPos * _nVelocity / 200000;
//        }
//    }
//    return _nMeasureData;
}

/*  T(A^): 厚度  */
float Measure::thickness(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少PulserWidth(脉宽)和BeamDelay
    return 0.0;
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_a_height();
//    int _nDataPos = beam->gate_a_position();// 单位: ns
//    int _nGateAHeight = group->gate_a_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;//满屏时200% 4095 A%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);
//    }

//    if(_nGateAHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
//        float _nAngle = group->current_angle();
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        float _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = _nDataPos - _nWedgeDelay;
//        _nMeasureData = _nMeasureData * _nVelocity * cos(_nAngle) / 200000;
//    }

//    return _nMeasureData;
}

/*  ML: 材料损失百分比  */
float Measure::ml(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽),BeamDelay,工件厚度
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_a_height();
//    int _nDataPos = beam->gate_a_position();// 单位: ns
//    int _nGateAHeight = group->gate_a_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;//满屏时200% 4095 A%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);
//    }

//    if(_nGateAHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
//        float _nAngle = group->current_angle();
////        float _nThickness = part->
////        if(_nThickness < 0.1) _nThickness = 0.1;
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        float _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = _nDataPos - _nWedgeDelay;
//        _nMeasureData = _nMeasureData * _nVelocity * cos(_nAngle) / 200000; // T(A^)
////        _nMeasureData = (_nThickness - _nMeasureData) / _nThickness * 100;
//    }

//    return _nMeasureData;
    return 0;
}

/*  %(r): 参考光标位置的幅度值  */
float Measure::reference_cursor_amplitude(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  %(m): 测量光标位置的幅度值  */
float Measure::measurement_cursor_amplitude(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  %(m-r): 测量光标减去参考光标的幅度值  */
float Measure::measurement_reference(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  U(r): 参考光标在超声轴上的位置  */
float Measure::reference_cursor_ut_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  U(m): 测量光标在超声轴上的位置  */
float Measure::measurement_cursor_ut_position(DplDevice::GroupPointer &group)
{
//    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  U(m-r): 超声轴上测量光标位置与参考光标位置之差 */
float Measure::measurement_reference_ut_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  P(r): 相对于参考光标的探头位置  */
float Measure::reference_cursor_probe_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  P(m): 相对于测量光标的探头位置  */
float Measure::measurement_cursor_probe_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  P(m-r): 探头相对于测量光标位置与参考光标位置的差值  */
float Measure::measurement_reference_probe_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  S(r): 扫查轴上参考光标的位置  */
float Measure::reference_cursor_scan_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  S(m): 扫查轴上测量光标的位置  */
float Measure::measurement_cursor_scan_position(DplDevice::GroupPointer &group)
{
//    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  S(m-r): 扫查轴上的测量光标位置与参考光标位置之差  */
float Measure::measurement_reference_scan_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  I(r): 步进轴上的参考光标位置  */
float Measure::reference_cursor_index_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  I(m): 步进轴上的测量光标位置  */
float Measure::measurement_cursor_index_position(DplDevice::GroupPointer &group)
{
//    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  I(m-r): 步进轴上的测量光标位置与参考光标位置之差  */
float Measure::measurement_reference_index_position(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  RA^: 声束出射点与闸门A内检测到的缺陷之间的距离  */
float Measure::ra(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少PulserWidth(脉宽)和BeamDelay
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_a_height();
//    int _nDataPos = beam->gate_a_position();// 单位: ns
//    int _nGateAHeight = group->gate_a_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 A%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);// A%
//    }

//    if(_nGateAHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
//        float _nAngle = group->current_angle();
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        float _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity * sin(_nAngle) / 200000; // 单位: mm
//    }

//    return _nMeasureData;
    return 0;

}

/*  RB^: 声束出射点与闸门B内检测到的缺陷之间的距离  */
float Measure::rb(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)和BeamDelay
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_b_height();
//    int _nDataPos = beam->gate_b_position();// 单位: ns
//    int _nGateBHeight = group->gate_b_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 B%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);// B%
//    }

//    if(_nGateBHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
//        float _nAngle = group->current_angle();
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        float _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity * sin(_nAngle) / 200000; // 单位: mm
//    }

//    return _nMeasureData;
    return 0;
}

/*  PA^: 探头前表面与闸门A内检测到的缺陷之间的距离  */
float Measure::pa(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 10.2;
}

/*  PB^: 探头前表面与闸门B内检测到的缺陷之间的距离  */
float Measure::pb(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  DA^: 闸门A内检测到的缺陷在工件中的深度  */
float Measure::da(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 10.1;
}

/*  DB^: 闸门B内检测到的缺陷在工件中的深度  */
float Measure::db(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  SA^: 声束出射点与闸门A内检测到的缺陷之间的声程  */
float Measure::sa(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少PulserWidth(脉宽)和BeamDelay

//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_a_height();
//    int _nDataPos = beam->gate_a_position();// 单位: ns
//    int _nGateAHeight = group->gate_a_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 A%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);// A%
//    }

//    if(_nGateAHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        float _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity / 200000; // 单位: mm
//    }

//    return _nMeasureData;

    return 10.3;
}

/*  SB^: 声束出射点与闸门B内检测到的缺陷之间的声程  */
float Measure::sb(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)和BeamDelay
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_b_height();
//    int _nDataPos = beam->gate_b_position();// 单位: ns
//    int _nGateBHeight = group->gate_b_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 B%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);// B%
//    }

//    if(_nGateBHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        float _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity / 200000; // 单位: mm
//    }

//    return _nMeasureData;

    return 0;
}

/*  ViA^: 闸门A中测得的信号指示在步进轴上的空间位置  */
float Measure::via(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  ViB^: 闸门B中测得的信号指示在步进轴上的空间位置  */
float Measure::vib(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  VsA^: 闸门A中测得的信号指示在扫查轴上的空间位置  */
float Measure::vsa(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  VsB^: 闸门B中测得的信号指示在扫查轴上的空间位置  */
float Measure::vsb(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  LA^: 从声束入射点到闸门A中测得的信号指示之间声波反射的次数  */
float Measure::la(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)，BeamDelay，工件厚度
//    float _nMeasureData;

//    DplSource::BeamGroupPointer beams = group->get_beam_group();
//    DplSource::BeamPointer beam = beams->get(beamIndex);
//    int _nData = beam->gate_a_height();
//    int _nDataPos = beam->gate_a_position();// 单位: ns
//    int _nGateAHeight = group->gate_a_height() / 20.47;

//    if(group->rectifier()){
//        _nMeasureData = _nData / 20.47;//满屏时200% 4095 A%
//    } else {
//        _nMeasureData = _nData / (10.24 * 16);
//    }

//    if(_nGateAHeight > fabs(_nMeasureData)) {
//        _nMeasureData = MEASURE_DATA_ND;
//    } else {
//        float _nAngle = group->current_angle();
////        float _nThickness = part->  / 1000;
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        float _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity * cos(_nAngle) / 200000; // T(A^)
////        _nMeasureData = (_nThickness - _nMeasureData) / _nThickness * 100;
//    }

//    return _nMeasureData;
    return 0;
}

/*  LB^: 从声束入射点到闸门B中测得的信号指示之间声波反射的次数  */
float Measure::lb(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)，BeamDelay，工件厚度
    return 0;
}

/*  E%: 闸门 A 中包络线的峰值波幅  */
float Measure::e(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DA: 根据 AWS-D1.5 A 标准规定的指示电平  */
float Measure::aws_da(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DB: 根据 AWS-D1.5 B 标准的零点参考电平  */
float Measure::aws_db(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DC: 根据 AWS-D1.5 C 标准的衰减系数  */
float Measure::aws_dc(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DD: 根据 AWS-D1.5 D 标准的衰减系数  */
float Measure::aws_dd(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-D45: 根据 AWS-D1.5 45°标准的不连续性严重等级  */
float Measure::aws_d45(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-D60: 根据 AWS-D1.5 60°标准的不连续性严重等级  */
float Measure::aws_d60(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-D70: 根据 AWS-D1.5 70°标准的不连续性严重等级  */
float Measure::aws_d70(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DCL: 根据 AWS-D1.5 标准的不连续性严重等级  */
float Measure::aws_dcl(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-D(r): TOFD超声轴方向参考光标深度  */
float Measure::t_d_r(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-D(m): TOFD超声轴方向测量光标深度  */
float Measure::t_d_m(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-S(m-r): TOFD扫查轴测量光标与参考光标间距  */
float Measure::t_s_mr(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-D(m-r): TOFD超声轴测量光标与参考光标间距  */
float Measure::t_d_mr(DplDevice::GroupPointer &group)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}
