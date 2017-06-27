#include "measure_calculation.h"

#include <device/device.h>
#include <source/beams.h>
#include <source/beam.h>
#include <source/source.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <QDebug>

class MeasureCalculationPrivate
{
public:
    MeasureCalculationPrivate();

//    DplDevice::Device *m_device;
//    DplSource::Source *m_source;

};

MeasureCalculationPrivate::MeasureCalculationPrivate()
{
//    m_device = DplDevice::Device::get_instance();
//    m_source = DplSource::Source::get_instance();
}

QMutex MeasureCalculation::m_mutex;
MeasureCalculation *MeasureCalculation::s_calculation = NULL;

MeasureCalculation *MeasureCalculation::get_calculation()
{
    QMutexLocker l(&m_mutex);

    if(s_calculation == NULL) {
        s_calculation = new MeasureCalculation();
    }
    return s_calculation;
}

MeasureCalculation::MeasureCalculation()
    : d(new MeasureCalculationPrivate)
{
}

MeasureCalculation::~MeasureCalculation()
{
    delete d;
}

/*  A%: 闸门 A 中测得的信号的峰值波幅  */
double MeasureCalculation::get_gate_a_peak_value(DplDevice::GroupPointer group, int beamIndex)
{
    DplSource::BeamsPointer beams = group->beams();
    DplSource::BeamPointer beam = beams->get(beamIndex);
    return beam->gate_peak(DplSource::Beam::GATE_A, !group->rectifier());
}


/*  AdBA: 闸门 A 内峰值幅度与闸门阈值幅度之差(dB)  */
double MeasureCalculation::get_gate_adBa_value(DplDevice::GroupPointer group, int beamIndex)
{
    double _nMeasureData;

    DplSource::BeamsPointer beams = group->beams();
    DplSource::BeamPointer beam = beams->get(beamIndex);
    int _nData = beam->gate_a_height();
    int _nGateAHeight = group->gate_a_height() / 20.47;

    if(group->rectifier()){
        _nMeasureData = _nData / 20.47;//满屏时200% 4095 A%
    } else {
        _nMeasureData = fabs(_nData / (10.24 * 16));// A%
    }

    if(_nGateAHeight < 1) _nGateAHeight = 1;
    _nMeasureData = 20 * log10(_nMeasureData / _nGateAHeight);

    qDebug() << _nMeasureData;
    return _nMeasureData;

}

/*  AdBr: 闸门 A 内峰值幅度与参考信号幅度之差(dB)  */
double MeasureCalculation::get_gate_adBr_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"umimplemented";
    return 10.0;
}

/*  B%: 闸门 B 中测得的信号的峰值波幅  */
double MeasureCalculation::get_gate_b_peak_value(DplDevice::GroupPointer group, int beamIndex)
{
    double _nMeasureData;

    DplSource::BeamsPointer beams = group->beams();
    DplSource::BeamPointer beam = beams->get(beamIndex);
    int _nData = beam->gate_b_height();

    if(group->rectifier()){
        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 B%
    } else {
        _nMeasureData = _nData / (10.24 * 16);// B%
    }

    qDebug() << "b%" << _nMeasureData;
    return _nMeasureData;
}

/*  BdBB: 闸门 B 内峰值幅度与闸门阈值幅度之差(dB)  */
double MeasureCalculation::get_gate_bdBb_value(DplDevice::GroupPointer group, int beamIndex)
{
    double _nMeasureData;

    DplSource::BeamsPointer beams = group->beams();
    DplSource::BeamPointer beam = beams->get(beamIndex);
    int _nData = beam->gate_b_height();
    int _nGateBHeight = group->gate_b_height() / 20.47;

    if(group->rectifier()){
        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 B%
    } else {
        _nMeasureData = fabs(_nData / (10.24 * 16)) ;// B%
    }

    if(_nGateBHeight < 1) _nGateBHeight = 1  ;
    _nMeasureData = 20 * log10(_nMeasureData / _nGateBHeight);

    qDebug() << "BdBB" << _nMeasureData;
    return _nMeasureData;
}

/*  BdBr: 闸门 B 内峰值幅度与参考信号幅度之差(dB)  */
double MeasureCalculation::get_gate_bdBr_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"umimplemented";
    return 0;
}

/*  A^: 闸门 A 内的信号峰值位置  */
double MeasureCalculation::get_gate_a_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    double _nMeasureData;

    DplSource::BeamsPointer beams = group->beams();
    DplSource::BeamPointer beam = beams->get(beamIndex);
    int _nData = beam->gate_a_height();
    int _nDataPos = beam->gate_a_position();
    int _nGateAHeight = group->gate_a_height() / 20.47;

    if(group->rectifier()){
        _nMeasureData = _nData / 20.47;// 满屏时200% 4095 A%
    } else {
        _nMeasureData = _nData / (10.24 * 16);// A%
    }

    if(_nGateAHeight > fabs(_nMeasureData)) {
        _nMeasureData = MEASURE_DATA_ND;
    } else {
        if(group->ut_unit() == DplDevice::Group::Time) {
            _nMeasureData = _nDataPos / 1000;
        } else {
            double _nVelocity = group->velocity();
            _nMeasureData = _nDataPos * _nVelocity / 200000;
            qDebug() << _nVelocity;
        }
    }

    qDebug() << _nDataPos << _nMeasureData;
    return _nMeasureData;
}

/*  B^: 闸门 B 内的信号峰值位置  */
double MeasureCalculation::get_gate_b_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    double _nMeasureData;

    DplSource::BeamsPointer beams = group->beams();
    DplSource::BeamPointer beam = beams->get(beamIndex);
    int _nData = beam->gate_b_height();
    int _nDataPos = beam->gate_b_position();// 单位: ns
    int _nGateBHeight = group->gate_b_height() / 20.47;

    if(group->rectifier()){
        _nMeasureData = _nData / 20.47;//满屏时200% 4095 B%
    } else {
        _nMeasureData = _nData / (10.24 * 16);// B%
    }

    if(_nGateBHeight > fabs(_nMeasureData)) {
        _nMeasureData = MEASURE_DATA_ND;
    } else {
        if(group->ut_unit() == DplDevice::Group::Time) {
            _nMeasureData = _nDataPos / 1000;
        } else {
            double _nVelocity = group->velocity();
            _nMeasureData = _nDataPos * _nVelocity / 200000;
        }
    }

    return _nMeasureData;
}

/*  I/: 闸门 I 内信号的前沿位置  */
double MeasureCalculation::get_gate_i_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少闸门I内波形前沿的位置
    return 0;
//    double _nMeasureData;

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
//        double _nVelocity = group->velocity();// 单位: m/s
//        if(group->ut_unit() == DplDevice::Group::Time) {
//            _nMeasureData = _nDataPos / 1000;// 单位: 微秒
//        } else {
//            _nMeasureData = _nDataPos * _nVelocity / 200000;// 单位: mm
//        }
//    }
//    return _nMeasureData;
}

/*  I(w)/: 闸门 I 内信号的前沿位置(水) */
double MeasureCalculation::get_gate_i_water_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少闸门I内波形前沿的位置
    return 0;
//    double _nMeasureData;

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
//            double _nVelocity = 1480;// 单位: m/s
//            _nMeasureData = _nDataPos * _nVelocity / 200000;
//        }
//    }
//    return _nMeasureData;
}

/*  T(A^): 厚度  */
double MeasureCalculation::get_thickness_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少PulserWidth(脉宽)和BeamDelay
//    double _nMeasureData;

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
//        double _nAngle = group->current_angle();
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        double _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = _nDataPos - _nWedgeDelay;
//        _nMeasureData = _nMeasureData * _nVelocity * cos(_nAngle) / 200000;
//    }

//    return _nMeasureData;
}

/*  ML: 材料损失百分比  */
double MeasureCalculation::get_ml_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽),BeamDelay,工件厚度
//    double _nMeasureData;

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
//        double _nAngle = group->current_angle();
////        double _nThickness = part->
////        if(_nThickness < 0.1) _nThickness = 0.1;
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        double _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = _nDataPos - _nWedgeDelay;
//        _nMeasureData = _nMeasureData * _nVelocity * cos(_nAngle) / 200000; // T(A^)
////        _nMeasureData = (_nThickness - _nMeasureData) / _nThickness * 100;
//    }

//    return _nMeasureData;
    return 0;
}

/*  %(r): 参考光标位置的幅度值  */
double MeasureCalculation::get_reference_cursor_amplitude_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  %(m): 测量光标位置的幅度值  */
double MeasureCalculation::get_measurement_cursor_amplitude_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  %(m-r): 测量光标减去参考光标的幅度值  */
double MeasureCalculation::get_measurement_reference_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  U(r): 参考光标在超声轴上的位置  */
double MeasureCalculation::get_reference_cursor_ut_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  U(m): 测量光标在超声轴上的位置  */
double MeasureCalculation::get_measurement_cursor_ut_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  U(m-r): 超声轴上测量光标位置与参考光标位置之差 */
double MeasureCalculation::get_measurement_reference_ut_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  P(r): 相对于参考光标的探头位置  */
double MeasureCalculation::get_reference_cursor_probe_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  P(m): 相对于测量光标的探头位置  */
double MeasureCalculation::get_measurement_cursor_probe_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  P(m-r): 探头相对于测量光标位置与参考光标位置的差值  */
double MeasureCalculation::get_measurement_reference_probe_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  S(r): 扫查轴上参考光标的位置  */
double MeasureCalculation::get_reference_cursor_scan_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  S(m): 扫查轴上测量光标的位置  */
double MeasureCalculation::get_measurement_cursor_scan_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  S(m-r): 扫查轴上的测量光标位置与参考光标位置之差  */
double MeasureCalculation::get_measurement_reference_scan_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  I(r): 步进轴上的参考光标位置  */
double MeasureCalculation::get_reference_cursor_index_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  I(m): 步进轴上的测量光标位置  */
double MeasureCalculation::get_measurement_cursor_index_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  I(m-r): 步进轴上的测量光标位置与参考光标位置之差  */
double MeasureCalculation::get_measurement_reference_index_position_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  RA^: 声束出射点与闸门A内检测到的缺陷之间的距离  */
double MeasureCalculation::get_ra_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少PulserWidth(脉宽)和BeamDelay
//    double _nMeasureData;

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
//        double _nAngle = group->current_angle();
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        double _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity * sin(_nAngle) / 200000; // 单位: mm
//    }

//    return _nMeasureData;
    return 0;

}

/*  RB^: 声束出射点与闸门B内检测到的缺陷之间的距离  */
double MeasureCalculation::get_rb_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)和BeamDelay
//    double _nMeasureData;

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
//        double _nAngle = group->current_angle();
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        double _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity * sin(_nAngle) / 200000; // 单位: mm
//    }

//    return _nMeasureData;
    return 0;
}

/*  PA^: 探头前表面与闸门A内检测到的缺陷之间的距离  */
double MeasureCalculation::get_pa_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 10.2;
}

/*  PB^: 探头前表面与闸门B内检测到的缺陷之间的距离  */
double MeasureCalculation::get_pb_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  DA^: 闸门A内检测到的缺陷在工件中的深度  */
double MeasureCalculation::get_da_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 10.1;
}

/*  DB^: 闸门B内检测到的缺陷在工件中的深度  */
double MeasureCalculation::get_db_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  SA^: 声束出射点与闸门A内检测到的缺陷之间的声程  */
double MeasureCalculation::get_sa_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented"; // 缺少PulserWidth(脉宽)和BeamDelay

//    double _nMeasureData;

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

//        double _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity / 200000; // 单位: mm
//    }

//    return _nMeasureData;

    return 10.3;
}

/*  SB^: 声束出射点与闸门B内检测到的缺陷之间的声程  */
double MeasureCalculation::get_sb_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)和BeamDelay
//    double _nMeasureData;

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

//        double _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity / 200000; // 单位: mm
//    }

//    return _nMeasureData;

    return 0;
}

/*  ViA^: 闸门A中测得的信号指示在步进轴上的空间位置  */
double MeasureCalculation::get_via_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  ViB^: 闸门B中测得的信号指示在步进轴上的空间位置  */
double MeasureCalculation::get_vib_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  VsA^: 闸门A中测得的信号指示在扫查轴上的空间位置  */
double MeasureCalculation::get_vsa_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  VsB^: 闸门B中测得的信号指示在扫查轴上的空间位置  */
double MeasureCalculation::get_vsb_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  LA^: 从声束入射点到闸门A中测得的信号指示之间声波反射的次数  */
double MeasureCalculation::get_la_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)，BeamDelay，工件厚度
//    double _nMeasureData;

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
//        double _nAngle = group->current_angle();
////        double _nThickness = part->  / 1000;
////        _nPulserWidth = group->
//        int _nWedgeDelay = group->get_wedge()->delay() / 10;
////        int _nBeamDelay = beam->
//        _nWedgeDelay += _nBeamDelay + _nPulserWidth;

//        double _nVelocity = group->velocity();// 单位: m/s
//        _nMeasureData = (_nDataPos - _nWedgeDelay) * _nVelocity * cos(_nAngle) / 200000; // T(A^)
////        _nMeasureData = (_nThickness - _nMeasureData) / _nThickness * 100;
//    }

//    return _nMeasureData;
    return 0;
}

/*  LB^: 从声束入射点到闸门B中测得的信号指示之间声波反射的次数  */
double MeasureCalculation::get_lb_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";// 缺少PulserWidth(脉宽)，BeamDelay，工件厚度
    return 0;
}

/*  E%: 闸门 A 中包络线的峰值波幅  */
double MeasureCalculation::get_e_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DA: 根据 AWS-D1.5 A 标准规定的指示电平  */
double MeasureCalculation::get_aws_da_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DB: 根据 AWS-D1.5 B 标准的零点参考电平  */
double MeasureCalculation::get_aws_db_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DC: 根据 AWS-D1.5 C 标准的衰减系数  */
double MeasureCalculation::get_aws_dc_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DD: 根据 AWS-D1.5 D 标准的衰减系数  */
double MeasureCalculation::get_aws_dd_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-D45: 根据 AWS-D1.5 45°标准的不连续性严重等级  */
double MeasureCalculation::get_aws_d45_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-D60: 根据 AWS-D1.5 60°标准的不连续性严重等级  */
double MeasureCalculation::get_aws_d60_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-D70: 根据 AWS-D1.5 70°标准的不连续性严重等级  */
double MeasureCalculation::get_aws_d70_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  AWS-DCL: 根据 AWS-D1.5 标准的不连续性严重等级  */
double MeasureCalculation::get_aws_dcl_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-D(r): TOFD超声轴方向参考光标深度  */
double MeasureCalculation::get_t_d_r_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-D(m): TOFD超声轴方向测量光标深度  */
double MeasureCalculation::get_t_d_m_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-S(m-r): TOFD扫查轴测量光标与参考光标间距  */
double MeasureCalculation::get_t_s_mr_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}

/*  T-D(m-r): TOFD超声轴测量光标与参考光标间距  */
double MeasureCalculation::get_t_d_mr_value(DplDevice::GroupPointer group, int beamIndex)
{
    qDebug()<<__FILE__<<__func__<<"Unimplemented";
    return 0;
}
