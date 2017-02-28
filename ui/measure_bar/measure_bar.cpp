#include "measure_bar.h"
#include "ui_measure_bar.h"

#include <source/beam_group.h>

#include <QDebug>

MeasureBar :: MeasureBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureBar)
{
    ui->setupUi(this);

    init_map();

    DplDevice::Device *device = DplDevice::Device::get_instance();
    connect(device, SIGNAL(current_group_changed()), this, SLOT(do_current_group_changed()));
    m_group = device->current_group();
//    m_beamNo = 0;
    m_beamIndex = 0;

    m_beamGroup = m_group->get_beam_group();
    connect(static_cast<DplSource::BeamGroup *>(m_beamGroup.data()), SIGNAL(data_event()), this, SLOT(do_beamgroup_data_event()));

    connect(ui->measureWidget1, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget2, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget3, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget4, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget5, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget6, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget7, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget8, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));

    ui->measureWidget1->set_type(MeasureDialog::Gate_A_Peak);
    ui->measureWidget2->set_type(MeasureDialog::Gate_AdBA);
    ui->measureWidget3->set_type(MeasureDialog::Gate_B_Peak);
    ui->measureWidget4->set_type(MeasureDialog::Gate_BdBB);
//    ui->measureWidget2->set_type(MeasureDialog::DA);
//    ui->measureWidget3->set_type(MeasureDialog::PA);
//    ui->measureWidget4->set_type(MeasureDialog::SA);
    ui->measureWidget5->set_type(MeasureDialog::Measurement_Cursor_UT_Position);
    ui->measureWidget6->set_type(MeasureDialog::Measurement_Cursor_Index_Position);
    ui->measureWidget7->set_type(MeasureDialog::Measurement_Cursor_Scan_Position);
    ui->measureWidget8->set_type(MeasureDialog::Gate_A_Position);
}

MeasureBar::~MeasureBar()
{
    delete(ui);
}

void MeasureBar::do_type_changed(MeasureDialog::MeasureType type)
{
    MeasureWidget *widget = qobject_cast<MeasureWidget*>(sender());
    if(m_beamGroup->get(0).isNull()) {
        return;
    } else {
        widget->set_value(calculate_value(type));
    }
}

QString MeasureBar::calculate_value(MeasureDialog::MeasureType type)
{
    MeasureCalculation::Function pFun = m_map.value(type);
    if(pFun) {
        double value = (MeasureCalculation::get_calculation()->*pFun)(m_group, m_beamIndex);
        return QString::number(value, 'f', 1);
    }
}

void MeasureBar::do_current_group_changed()
{
    m_group = DplDevice::Device::get_instance()->current_group();
    m_beamGroup = m_group->get_beam_group();
}

//void MeasureBar::do_beam_qty_changed(int qty)
//{
////    m_beamNo = qty;
//    m_beamIndex = qty;
//    set();
//}

void MeasureBar::do_beamgroup_data_event()
{
    set();
}

void MeasureBar::set()
{
    ui->measureWidget1->set_value(calculate_value(ui->measureWidget1->type()));
    ui->measureWidget2->set_value(calculate_value(ui->measureWidget2->type()));
    ui->measureWidget3->set_value(calculate_value(ui->measureWidget3->type()));
    ui->measureWidget4->set_value(calculate_value(ui->measureWidget4->type()));
    ui->measureWidget5->set_value(calculate_value(ui->measureWidget5->type()));
    ui->measureWidget6->set_value(calculate_value(ui->measureWidget6->type()));
    ui->measureWidget7->set_value(calculate_value(ui->measureWidget7->type()));
    ui->measureWidget8->set_value(calculate_value(ui->measureWidget8->type()));
}

void MeasureBar::init_map()
{
    m_map.insert(MeasureDialog::Gate_A_Peak, &MeasureCalculation::get_gate_a_peak_value);
    m_map.insert(MeasureDialog::Gate_AdBA, &MeasureCalculation::get_gate_adBa_value);
    m_map.insert(MeasureDialog::Gate_AdBr, &MeasureCalculation::get_gate_adBr_value);
    m_map.insert(MeasureDialog::Gate_B_Peak, &MeasureCalculation::get_gate_b_peak_value);
    m_map.insert(MeasureDialog::Gate_BdBB, &MeasureCalculation::get_gate_bdBb_value);
    m_map.insert(MeasureDialog::Gate_BdBr, &MeasureCalculation::get_gate_bdBr_value);
    m_map.insert(MeasureDialog::Gate_A_Position, &MeasureCalculation::get_gate_a_position_value);
    m_map.insert(MeasureDialog::Gate_B_Position, &MeasureCalculation::get_gate_b_position_value);
    m_map.insert(MeasureDialog::Gate_I_Position, &MeasureCalculation::get_gate_i_position_value);
    m_map.insert(MeasureDialog::Gate_I_Water_Position, &MeasureCalculation::get_gate_i_water_position_value);
    m_map.insert(MeasureDialog::Thickness, &MeasureCalculation::get_thickness_value);
    m_map.insert(MeasureDialog::ML, &MeasureCalculation::get_ml_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Amplitude, &MeasureCalculation::get_reference_cursor_amplitude_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Amplitude, &MeasureCalculation::get_measurement_cursor_amplitude_value);
    m_map.insert(MeasureDialog::Measurement_Reference, &MeasureCalculation::get_measurement_reference_value);
    m_map.insert(MeasureDialog::Reference_Cursor_UT_Position, &MeasureCalculation::get_reference_cursor_ut_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_UT_Position, &MeasureCalculation::get_measurement_cursor_ut_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_UT_Position, &MeasureCalculation::get_measurement_reference_ut_position_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Probe_Position, &MeasureCalculation::get_reference_cursor_probe_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Probe_Position, &MeasureCalculation::get_measurement_cursor_probe_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_Probe_position, &MeasureCalculation::get_measurement_reference_probe_position_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Scan_Position, &MeasureCalculation::get_reference_cursor_scan_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Scan_Position, &MeasureCalculation::get_measurement_cursor_scan_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_Scan_Position, &MeasureCalculation::get_measurement_reference_scan_position_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Index_Position, &MeasureCalculation::get_reference_cursor_index_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Index_Position, &MeasureCalculation::get_measurement_cursor_index_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_Index_Position, &MeasureCalculation::get_measurement_reference_index_position_value);
    m_map.insert(MeasureDialog::RA, &MeasureCalculation::get_ra_value);
    m_map.insert(MeasureDialog::RB, &MeasureCalculation::get_rb_value);
    m_map.insert(MeasureDialog::PA, &MeasureCalculation::get_pa_value);
    m_map.insert(MeasureDialog::PB, &MeasureCalculation::get_pb_value);
    m_map.insert(MeasureDialog::DA, &MeasureCalculation::get_da_value);
    m_map.insert(MeasureDialog::DB, &MeasureCalculation::get_db_value);
    m_map.insert(MeasureDialog::SA, &MeasureCalculation::get_sa_value);
    m_map.insert(MeasureDialog::SB, &MeasureCalculation::get_sb_value);
    m_map.insert(MeasureDialog::ViA, &MeasureCalculation::get_via_value);
    m_map.insert(MeasureDialog::ViB, &MeasureCalculation::get_vib_value);
    m_map.insert(MeasureDialog::VsA, &MeasureCalculation::get_vsa_value);
    m_map.insert(MeasureDialog::VsB, &MeasureCalculation::get_vsb_value);
    m_map.insert(MeasureDialog::LA, &MeasureCalculation::get_la_value);
    m_map.insert(MeasureDialog::LB, &MeasureCalculation::get_lb_value);
    m_map.insert(MeasureDialog::E, &MeasureCalculation::get_e_value);
    m_map.insert(MeasureDialog::AWS_DA, &MeasureCalculation::get_aws_da_value);
    m_map.insert(MeasureDialog::AWS_DB, &MeasureCalculation::get_aws_db_value);
    m_map.insert(MeasureDialog::AWS_DC, &MeasureCalculation::get_aws_dc_value);
    m_map.insert(MeasureDialog::AWS_DD, &MeasureCalculation::get_aws_dd_value);
    m_map.insert(MeasureDialog::AWS_D45, &MeasureCalculation::get_aws_d45_value);
    m_map.insert(MeasureDialog::AWS_D60, &MeasureCalculation::get_aws_d60_value);
    m_map.insert(MeasureDialog::AWS_D70, &MeasureCalculation::get_aws_d70_value);
    m_map.insert(MeasureDialog::AWS_DCL, &MeasureCalculation::get_aws_dcl_value);
    m_map.insert(MeasureDialog::T_D_r, &MeasureCalculation::get_t_d_r_value);
    m_map.insert(MeasureDialog::T_D_m, &MeasureCalculation::get_t_d_m_value);
    m_map.insert(MeasureDialog::T_S_mr, &MeasureCalculation::get_t_s_mr_value);
    m_map.insert(MeasureDialog::T_D_mr, &MeasureCalculation::get_t_d_mr_value);
}
