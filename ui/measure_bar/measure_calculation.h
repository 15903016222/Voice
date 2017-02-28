#ifndef __MEASURE_CALCULATION_H
#define __MEASURE_CALCULATION_H

#include <device/group.h>
#include <device/device.h>

#include <QObject>
#include <QMutex>

#define MEASURE_DATA_ND    987654321.123

class MeasureCalculationPrivate;
class MeasureCalculation : public QObject
{
    Q_OBJECT

public:   
    static MeasureCalculation *get_calculation();
    typedef double (MeasureCalculation::*Function)(DplDevice::GroupPointer, int);

    double get_gate_a_peak_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_adBa_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_adBr_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_b_peak_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_bdBb_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_bdBr_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_a_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_b_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_i_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_gate_i_water_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_thickness_value(DplDevice::GroupPointer group, int beamIndex);
    double get_ml_value(DplDevice::GroupPointer group, int beamIndex);
    double get_reference_cursor_amplitude_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_cursor_amplitude_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_reference_value(DplDevice::GroupPointer group, int beamIndex);
    double get_reference_cursor_ut_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_cursor_ut_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_reference_ut_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_reference_cursor_probe_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_cursor_probe_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_reference_probe_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_reference_cursor_scan_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_cursor_scan_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_reference_scan_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_reference_cursor_index_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_cursor_index_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_measurement_reference_index_position_value(DplDevice::GroupPointer group, int beamIndex);
    double get_ra_value(DplDevice::GroupPointer group, int beamIndex);
    double get_rb_value(DplDevice::GroupPointer group, int beamIndex);
    double get_pa_value(DplDevice::GroupPointer group, int beamIndex);
    double get_pb_value(DplDevice::GroupPointer group, int beamIndex);
    double get_da_value(DplDevice::GroupPointer group, int beamIndex);
    double get_db_value(DplDevice::GroupPointer group, int beamIndex);
    double get_sa_value(DplDevice::GroupPointer group, int beamIndex);
    double get_sb_value(DplDevice::GroupPointer group, int beamIndex);
    double get_via_value(DplDevice::GroupPointer group, int beamIndex);
    double get_vib_value(DplDevice::GroupPointer group, int beamIndex);
    double get_vsa_value(DplDevice::GroupPointer group, int beamIndex);
    double get_vsb_value(DplDevice::GroupPointer group, int beamIndex);
    double get_la_value(DplDevice::GroupPointer group, int beamIndex);
    double get_lb_value(DplDevice::GroupPointer group, int beamIndex);
    double get_e_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_da_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_db_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_dc_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_dd_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_d45_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_d60_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_d70_value(DplDevice::GroupPointer group, int beamIndex);
    double get_aws_dcl_value(DplDevice::GroupPointer group, int beamIndex);
    double get_t_d_r_value(DplDevice::GroupPointer group, int beamIndex);
    double get_t_d_m_value(DplDevice::GroupPointer group, int beamIndex);
    double get_t_s_mr_value(DplDevice::GroupPointer group, int beamIndex);
    double get_t_d_mr_value(DplDevice::GroupPointer group, int beamIndex);

protected:
    explicit MeasureCalculation();
    ~MeasureCalculation();

private:
    static MeasureCalculation *s_calculation;
    static QMutex m_mutex;
    MeasureCalculationPrivate *d;
};

#endif // __MEASURE_CALCULATION_H
