#ifndef MEASURECALCULATION_H
#define MEASURECALCULATION_H

#include "measure_dialog.h"

#include <QObject>
#include <QMutex>

class MeasureCalculationPrivate;
class MeasureCalculation : public QObject
{
    Q_OBJECT

public:   
    static MeasureCalculation *get_calculation();
    typedef double (MeasureCalculation::*Function)();

    double set_gate_a_peak_value();
    double set_gate_adBa_value();
    double set_gate_adBr_value();
    double set_gate_b_peak_value();
    double set_gate_bdBb_value();
    double set_gate_bdBr_value();
    double set_gate_a_position_value();
    double set_gate_b_position_value();
    double set_gate_i_position_value();
    double set_gate_i_water_position_value();
    double set_thickness_value();
    double set_ml_value();
    double set_reference_cursor_amplitude_value();
    double set_measurement_cursor_amplitude_value();
    double set_measurement_reference_value();
    double set_reference_cursor_ut_position_value();
    double set_measurement_cursor_ut_position_value();
    double set_measurement_reference_ut_position_value();
    double set_reference_cursor_probe_position_value();
    double set_measurement_cursor_probe_position_value();
    double set_measurement_reference_probe_position_value();
    double set_reference_cursor_scan_position_value();
    double set_measurement_cursor_scan_position_value();
    double set_measurement_reference_scan_position_value();
    double set_reference_cursor_index_position_value();
    double set_measurement_cursor_index_position_value();
    double set_measurement_reference_index_position_value();
    double set_ra_value();
    double set_rb_value();
    double set_pa_value();
    double set_pb_value();
    double set_da_value();
    double set_db_value();
    double set_sa_value();
    double set_sb_value();
    double set_via_value();
    double set_vib_value();
    double set_vsa_value();
    double set_vsb_value();
    double set_la_value();
    double set_lb_value();
    double set_e_value();
    double set_aws_da_value();
    double set_aws_db_value();
    double set_aws_dc_value();
    double set_aws_dd_value();
    double set_aws_d45_value();
    double set_aws_d60_value();
    double set_aws_d70_value();
    double set_aws_dcl_value();
    double set_t_d_r_value();
    double set_t_d_m_value();
    double set_t_s_mr_value();
    double set_t_d_mr_value();

protected:
    explicit MeasureCalculation();
    ~MeasureCalculation();

private:
    static MeasureCalculation *s_calculation;
    static QMutex m_mutex;
    MeasureCalculationPrivate *d;
};

#endif // MEASURECALCULATION_H
