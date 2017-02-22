#include "measure_calculation.h"

#include <device/device.h>
#include <device/group.h>
#include <source/beam_group.h>
#include <source/beam.h>
#include <source/source.h>

#include <QDebug>

class MeasureCalculationPrivate
{
public:
    MeasureCalculationPrivate();

    DplDevice::Device *m_device;
    DplSource::Source *m_source;
//    DplDevice::GroupPointer m_group;
//    DplSource::BeamGroupPointer m_beamGroup;
//    int m_beamQty;

};

MeasureCalculationPrivate::MeasureCalculationPrivate()
{
    m_device = DplDevice::Device::get_instance();
    m_source = DplSource::Source::get_instance();
//    m_group = DplDevice::Device::get_instance()->current_group();
//    m_beamGroup = m_group->get_beam_group();
//    m_beamQty = m_beamGroup->beam_qty();
}

QMutex MeasureCalculation::m_mutex;
MeasureCalculation *MeasureCalculation::s_calculation = NULL;

MeasureCalculation *MeasureCalculation::get_calculation()
{
    QMutexLocker l(&m_mutex);

    if(s_calculation == NULL) {
        s_calculation = new MeasureCalculation();
    }
    qDebug() << "run1";
    qDebug() << s_calculation;
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

double MeasureCalculation::set_gate_a_peak_value()
{
//    int _nData;
//    double _nMeasureData;

//    DplDevice::GroupPointer group = d->m_device->current_group();
//    DplSource::BeamGroupPointer beamGroup = group->get_beam_group();
//    int beamQty = beamGroup->beam_qty();
//    DplSource::BeamPointer beam = beamGroup->get(beamQty);
//    if(beamQty == 1) {
//        _nData = beam->gate_a_height();
//    } else {

//    }


//    if(){
//        _nMeasureData = ((_nData >> 20) & 0x00000fff) / 20.47;//满屏时200% 4095
//    } else {
//        _nMeasureData = (signed short)(_nData >> 16) ;
//        _nMeasureData = _nMeasureData / (10.24 * 16);
//    }
//    return _nMeasureData;

//    return _nData;
    return 10.0;
}

double MeasureCalculation::set_gate_adBa_value()
{
    return 20.0;
}

double MeasureCalculation::set_gate_adBr_value()
{
    return 10.0;
}

double MeasureCalculation::set_gate_b_peak_value()
{
//    int _nData = DplSource::Beam::gate_b_height();

}


double MeasureCalculation::set_gate_bdBb_value()
{

}

double MeasureCalculation::set_gate_bdBr_value()
{

}

double MeasureCalculation::set_gate_a_position_value()
{
//    int _nData = DplSource::Beam::gate_a_position();
}

double MeasureCalculation::set_gate_b_position_value()
{
//    int _nData = DplSource::Beam::gate_b_position();
}

double MeasureCalculation::set_gate_i_position_value()
{
//    int _nData = DplSource::Beam::gate_i_position();
}

double MeasureCalculation::set_gate_i_water_position_value()
{

}

double MeasureCalculation::set_thickness_value()
{

}

double MeasureCalculation::set_ml_value()
{

}

double MeasureCalculation::set_reference_cursor_amplitude_value()
{   
    qDebug()<<__func__<<__LINE__<<"umimplement";
}

double MeasureCalculation::set_measurement_cursor_amplitude_value()
{
    qDebug()<<__func__<<__LINE__<<"umimplement";
}

double MeasureCalculation::set_measurement_reference_value()
{

}

double MeasureCalculation::set_reference_cursor_ut_position_value()
{

}

double MeasureCalculation::set_measurement_cursor_ut_position_value()
{

}

double MeasureCalculation::set_measurement_reference_ut_position_value()
{

}

double MeasureCalculation::set_reference_cursor_probe_position_value()
{

}

double MeasureCalculation::set_measurement_cursor_probe_position_value()
{

}

double MeasureCalculation::set_measurement_reference_probe_position_value()
{

}

double MeasureCalculation::set_reference_cursor_scan_position_value()
{

}

double MeasureCalculation::set_measurement_cursor_scan_position_value()
{

}

double MeasureCalculation::set_measurement_reference_scan_position_value()
{

}

double MeasureCalculation::set_reference_cursor_index_position_value()
{

}

double MeasureCalculation::set_measurement_cursor_index_position_value()
{

}

double MeasureCalculation::set_measurement_reference_index_position_value()
{

}

double MeasureCalculation::set_ra_value()
{

}

double MeasureCalculation::set_rb_value()
{

}

double MeasureCalculation::set_pa_value()
{
    return 10.2;
}

double MeasureCalculation::set_pb_value()
{

}

double MeasureCalculation::set_da_value()
{
    return 10.1;
}

double MeasureCalculation::set_db_value()
{

}

double MeasureCalculation::set_sa_value()
{
    return 10.3;
}

double MeasureCalculation::set_sb_value()
{

}

double MeasureCalculation::set_via_value()
{

}

double MeasureCalculation::set_vib_value()
{

}

double MeasureCalculation::set_vsa_value()
{

}

double MeasureCalculation::set_vsb_value()
{

}

double MeasureCalculation::set_la_value()
{

}

double MeasureCalculation::set_lb_value()
{

}

double MeasureCalculation::set_e_value()
{

}

double MeasureCalculation::set_aws_da_value()
{

}

double MeasureCalculation::set_aws_db_value()
{

}

double MeasureCalculation::set_aws_dc_value()
{

}

double MeasureCalculation::set_aws_dd_value()
{

}

double MeasureCalculation::set_aws_d45_value()
{

}

double MeasureCalculation::set_aws_d60_value()
{

}

double MeasureCalculation::set_aws_d70_value()
{

}

double MeasureCalculation::set_aws_dcl_value()
{

}

double MeasureCalculation::set_t_d_r_value()
{

}

double MeasureCalculation::set_t_d_m_value()
{

}

double MeasureCalculation::set_t_s_mr_value()
{

}

double MeasureCalculation::set_t_d_mr_value()
{

}
