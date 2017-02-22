#include "measure_bar.h"
#include "ui_measure_bar.h"

#include <source/beam_group.h>

#include <QDebug>

MeasureBar :: MeasureBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureBar)
{
    ui->setupUi(this);

//    measureCalculation = MeasureCalculation::get_calculation();
//    qDebug() << "1";

    init_map();

    DplDevice::Device *device = DplDevice::Device::get_instance();
    connect(device, SIGNAL(current_group_changed()), this, SLOT(do_current_group_changed()));
//    m_group = device->current_group();

//    DplSource::Source *source = DplSource::Source::get_instance();
//    connect(source, SIGNAL(type_changed(DplSource::Source::Type)), this, SLOT(do_source_type_changed(DplSource::Source::Type)));

//    DplSource::BeamGroupPointer beamGroup = device->current_group()->get_beam_group();
//    connect(beamGroup, SIGNAL())

    connect(ui->measureWidget1, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget2, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget3, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget4, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget5, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget6, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget7, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));
    connect(ui->measureWidget8, SIGNAL(type_changed(MeasureDialog::MeasureType)), this, SLOT(do_type_changed(MeasureDialog::MeasureType)));

    ui->measureWidget1->set_type(MeasureDialog::Gate_A_Peak);
    ui->measureWidget2->set_type(MeasureDialog::DA);
    ui->measureWidget3->set_type(MeasureDialog::PA);
    ui->measureWidget4->set_type(MeasureDialog::SA);
    ui->measureWidget5->set_type(MeasureDialog::Measurement_Cursor_UT_Position);
    ui->measureWidget6->set_type(MeasureDialog::Measurement_Cursor_Index_Position);
    ui->measureWidget7->set_type(MeasureDialog::Measurement_Cursor_Scan_Position);
    ui->measureWidget8->set_type(MeasureDialog::Gate_B_Peak);
}

MeasureBar::~MeasureBar()
{
    delete(ui);
}

void MeasureBar::do_type_changed(MeasureDialog::MeasureType type)
{
    MeasureWidget *widget = qobject_cast<MeasureWidget*>(sender());
    widget->set_value(QString::number(calculate_value(type), 'f', 1));
}

double MeasureBar::calculate_value(MeasureDialog::MeasureType type)
{
    MeasureCalculation::Function pFun = m_map.value(type);
    if(pFun) {
        return (MeasureCalculation::get_calculation()->*pFun)();
    }
}

void MeasureBar::do_current_group_changed()
{
    ui->measureWidget1->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
    ui->measureWidget2->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
    ui->measureWidget3->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
    ui->measureWidget4->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
    ui->measureWidget5->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
    ui->measureWidget6->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
    ui->measureWidget7->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
    ui->measureWidget8->set_value(QString::number(calculate_value(ui->measureWidget1->type()), 'f', 1));
}

void MeasureBar::init_map()
{
    m_map.insert(MeasureDialog::Gate_A_Peak, &MeasureCalculation::set_gate_a_peak_value);
    m_map.insert(MeasureDialog::Gate_AdBA, &MeasureCalculation::set_gate_adBa_value);
    m_map.insert(MeasureDialog::Gate_AdBr, &MeasureCalculation::set_gate_adBr_value);
    m_map.insert(MeasureDialog::Gate_B_Peak, &MeasureCalculation::set_gate_b_peak_value);
    m_map.insert(MeasureDialog::Gate_BdBB, &MeasureCalculation::set_gate_bdBb_value);
    m_map.insert(MeasureDialog::Gate_BdBr, &MeasureCalculation::set_gate_bdBr_value);
    m_map.insert(MeasureDialog::Gate_A_Position, &MeasureCalculation::set_gate_a_position_value);
    m_map.insert(MeasureDialog::Gate_B_Position, &MeasureCalculation::set_gate_b_position_value);
    m_map.insert(MeasureDialog::Gate_I_Position, &MeasureCalculation::set_gate_i_position_value);
    m_map.insert(MeasureDialog::Gate_I_Water_Position, &MeasureCalculation::set_gate_i_water_position_value);
    m_map.insert(MeasureDialog::Thickness, &MeasureCalculation::set_thickness_value);
    m_map.insert(MeasureDialog::ML, &MeasureCalculation::set_ml_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Amplitude, &MeasureCalculation::set_reference_cursor_amplitude_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Amplitude, &MeasureCalculation::set_measurement_cursor_amplitude_value);
    m_map.insert(MeasureDialog::Measurement_Reference, &MeasureCalculation::set_measurement_reference_value);
    m_map.insert(MeasureDialog::Reference_Cursor_UT_Position, &MeasureCalculation::set_reference_cursor_ut_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_UT_Position, &MeasureCalculation::set_measurement_cursor_ut_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_UT_Position, &MeasureCalculation::set_measurement_reference_ut_position_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Probe_Position, &MeasureCalculation::set_reference_cursor_probe_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Probe_Position, &MeasureCalculation::set_measurement_cursor_probe_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_Probe_position, &MeasureCalculation::set_measurement_reference_probe_position_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Scan_Position, &MeasureCalculation::set_reference_cursor_scan_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Scan_Position, &MeasureCalculation::set_measurement_cursor_scan_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_Scan_Position, &MeasureCalculation::set_measurement_reference_scan_position_value);
    m_map.insert(MeasureDialog::Reference_Cursor_Index_Position, &MeasureCalculation::set_reference_cursor_index_position_value);
    m_map.insert(MeasureDialog::Measurement_Cursor_Index_Position, &MeasureCalculation::set_measurement_cursor_index_position_value);
    m_map.insert(MeasureDialog::Measurement_Reference_Index_Position, &MeasureCalculation::set_measurement_reference_index_position_value);
    m_map.insert(MeasureDialog::RA, &MeasureCalculation::set_ra_value);
    m_map.insert(MeasureDialog::RB, &MeasureCalculation::set_rb_value);
    m_map.insert(MeasureDialog::PA, &MeasureCalculation::set_pa_value);
    m_map.insert(MeasureDialog::PB, &MeasureCalculation::set_pb_value);
    m_map.insert(MeasureDialog::DA, &MeasureCalculation::set_da_value);
    m_map.insert(MeasureDialog::DB, &MeasureCalculation::set_db_value);
    m_map.insert(MeasureDialog::SA, &MeasureCalculation::set_sa_value);
    m_map.insert(MeasureDialog::SB, &MeasureCalculation::set_sb_value);
    m_map.insert(MeasureDialog::ViA, &MeasureCalculation::set_via_value);
    m_map.insert(MeasureDialog::ViB, &MeasureCalculation::set_vib_value);
    m_map.insert(MeasureDialog::VsA, &MeasureCalculation::set_vsa_value);
    m_map.insert(MeasureDialog::VsB, &MeasureCalculation::set_vsb_value);
    m_map.insert(MeasureDialog::LA, &MeasureCalculation::set_la_value);
    m_map.insert(MeasureDialog::LB, &MeasureCalculation::set_lb_value);
    m_map.insert(MeasureDialog::E, &MeasureCalculation::set_e_value);
    m_map.insert(MeasureDialog::AWS_DA, &MeasureCalculation::set_aws_da_value);
    m_map.insert(MeasureDialog::AWS_DB, &MeasureCalculation::set_aws_db_value);
    m_map.insert(MeasureDialog::AWS_DC, &MeasureCalculation::set_aws_dc_value);
    m_map.insert(MeasureDialog::AWS_DD, &MeasureCalculation::set_aws_dd_value);
    m_map.insert(MeasureDialog::AWS_D45, &MeasureCalculation::set_aws_d45_value);
    m_map.insert(MeasureDialog::AWS_D60, &MeasureCalculation::set_aws_d60_value);
    m_map.insert(MeasureDialog::AWS_D70, &MeasureCalculation::set_aws_d70_value);
    m_map.insert(MeasureDialog::AWS_DCL, &MeasureCalculation::set_aws_dcl_value);
    m_map.insert(MeasureDialog::T_D_r, &MeasureCalculation::set_t_d_r_value);
    m_map.insert(MeasureDialog::T_D_m, &MeasureCalculation::set_t_d_m_value);
    m_map.insert(MeasureDialog::T_S_mr, &MeasureCalculation::set_t_s_mr_value);
    m_map.insert(MeasureDialog::T_D_mr, &MeasureCalculation::set_t_d_mr_value);
}
