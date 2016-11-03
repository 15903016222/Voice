#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#define show_warning() { QMessageBox::warning(this, "Global Setting", __func__); }
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_fpga = Fpga::get_fpga();
    m_alarmOutput = m_fpga->alarm_output(ui->comboBoxAlarmOuput->currentIndex());
    m_alarmAnalog = m_fpga->alarm_analog(ui->comboBoxAlarmAnalog->currentIndex());

    m_fpga->create_group();
    m_group = m_fpga->get_group(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxPaLawQty_valueChanged(int arg1)
{
    if ( ! m_fpga->set_pa_law_qty(arg1, true) ) {
        show_warning();
    }
}

void MainWindow::on_spinBoxUtLawQty_valueChanged(int arg1)
{
    if ( ! m_fpga->set_ut_law_qty(arg1, true) ) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderXPolarity_currentIndexChanged(int index)
{
    bool ret = false;
    if (index == 1) {
        ret = m_fpga->set_encoder_x(m_fpga->encoder_x_mode(), Fpga::INVERSE, true);
    } else {
        ret = m_fpga->set_encoder_x(m_fpga->encoder_x_mode(), Fpga::NORMAL, true);
    }
    if (! ret) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderXMode_currentIndexChanged(int index)
{
    if (! m_fpga->set_encoder_x((Fpga::EncoderMode)index, m_fpga->encoder_x_polarity(), true) ) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderYPolarity_currentIndexChanged(int index)
{
    bool ret = false;
    if (index == 1) {
        ret = m_fpga->set_encoder_y(m_fpga->encoder_y_mode(), Fpga::INVERSE, true);
    } else {
        ret = m_fpga->set_encoder_y(m_fpga->encoder_y_mode(), Fpga::NORMAL, true);
    }
    if (! ret) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderYMode_currentIndexChanged(int index)
{
    if (! m_fpga->set_encoder_y((Fpga::EncoderMode)index, m_fpga->encoder_y_polarity(), true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt1Twin_currentIndexChanged(int index)
{
    if (! m_fpga->set_ut1_twin((!index), true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt2Twin_currentIndexChanged(int index)
{
    if (! m_fpga->set_ut2_twin((!index), true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt1TxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut1_tx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt1RxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut1_rx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt2TxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut2_tx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt2RxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut2_rx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUtVoltage_currentIndexChanged(int index)
{
    if (! m_fpga->set_ut_voltage((Fpga::VoltageType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxPaVoltage_currentIndexChanged(int index)
{
    if (! m_fpga->set_pa_voltage((Fpga::VoltageType)index, true)) {
        show_warning();
    }
}


void MainWindow::on_comboBoxFreeze_currentIndexChanged(int index)
{
    if ( ! m_fpga->set_freeze(!index, true) ) {
        show_warning();
    }
}

void MainWindow::on_comboBoxSound_currentIndexChanged(int index)
{
    if (! m_fpga->set_sound((Fpga::SoundMode)index, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxEcho_valueChanged(int arg1)
{
    if (! m_fpga->set_factor_echo(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxAlarmOuput_currentIndexChanged(int index)
{
    ui->groupBoxAlarmOutput->setTitle(QString("Alarm Output %1").arg(index));
    m_alarmOutput = m_fpga->alarm_output(ui->comboBoxAlarmOuput->currentIndex());
}

void MainWindow::on_comboBoxAlarmOutputValid_currentIndexChanged(int index)
{
    if (! m_alarmOutput->set_valid(!index, true) ) {
        show_warning();
    }
}

void MainWindow::do_checkBox_changed()
{
    quint32 channels = ui->checkBox_0->isChecked() | (ui->checkBox_1->isChecked() << 1)
            | (ui->checkBox_2->isChecked() << 2) | (ui->checkBox_3->isChecked() << 3)
            | (ui->checkBox_4->isChecked() << 4) | (ui->checkBox_5->isChecked() << 5)
            | (ui->checkBox_6->isChecked() << 6) | (ui->checkBox_7->isChecked() << 6)
            | (ui->checkBox_8->isChecked() << 8) | (ui->checkBox_9->isChecked() << 9)
            | (ui->checkBox_10->isChecked() << 10) | (ui->checkBox_11->isChecked() << 11)
            | (ui->checkBox_12->isChecked() << 12) | (ui->checkBox_13->isChecked() << 13)
            | (ui->checkBox_14->isChecked() << 14) | (ui->checkBox_15->isChecked() << 15)
            | (ui->checkBox_16->isChecked() << 16) | (ui->checkBox_17->isChecked() << 17)
            | (ui->checkBox_18->isChecked() << 18) | (ui->checkBox_19->isChecked() << 19)
            | (ui->checkBox_20->isChecked() << 20) | (ui->checkBox_21->isChecked() << 21)
            | (ui->checkBox_22->isChecked() << 22) | (ui->checkBox_23->isChecked() << 23)
            | (ui->checkBox_24->isChecked() << 24) | (ui->checkBox_25->isChecked() << 25)
            | (ui->checkBox_26->isChecked() << 26) | (ui->checkBox_27->isChecked() << 27)
            | (ui->checkBox_28->isChecked() << 28) | (ui->checkBox_29->isChecked() << 29)
            | (ui->checkBox_30->isChecked() << 30) | (ui->checkBox_31->isChecked() << 31);
    if (! m_fpga->set_rx_channels(channels, true) ) {
        show_warning();
    }
}

void MainWindow::on_comboBoxAlarmOutputLogicGroup_currentIndexChanged(int index)
{
    if (! m_alarmOutput->set_logic_group(index+1, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxAlarmOutputOperator_currentIndexChanged(int index)
{
    if (! m_alarmOutput->set_op((AlarmOutput::Operator)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxAlarmOutputCondition_currentIndexChanged(int index)
{
    if (! m_alarmOutput->set_condition(ui->comboBoxAlarmOutputLogicGroup->currentIndex(), (AlarmOutput::Condition)index, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxAlarmOutputCount_valueChanged(int arg1)
{
    if (! m_alarmOutput->set_count(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxAlarmOutputDelay_valueChanged(int arg1)
{
    if (! m_alarmOutput->set_delay(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxAlarmOutputHoldTime_valueChanged(int arg1)
{
    if (! m_alarmOutput->set_hold_time(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxAlarmAnalog_currentIndexChanged(int index)
{
    ui->groupBoxAlarmAnalog->setTitle(QString("Alarm Analog %1").arg(index));
    m_alarmAnalog = m_fpga->alarm_analog(ui->comboBoxAlarmAnalog->currentIndex());
}

void MainWindow::on_comboBoxAlarmAnalogValid_currentIndexChanged(int index)
{
    if (! m_alarmAnalog->set_valid(!index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxSoundAlarmAnalogLogicGroup_currentIndexChanged(int index)
{
    if (! m_alarmAnalog->set_logic_group(index+1, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxAlarmAnalogType_currentIndexChanged(int index)
{
    if (! m_alarmAnalog->set_type((AlarmAnalog::Type)index)) {
        show_warning();
    }
}

void MainWindow::on_pushButtonReset_clicked()
{
    if (! m_fpga->reset()) {
        show_warning();
    }
}

/******* Group ********/

void MainWindow::on_pushButtonGroupCreate_clicked()
{
    if (! m_fpga->create_group() ) {
        show_warning();
        return;
    }
    ui->comboBoxCurrentGroup->addItem(QString::number(m_fpga->groups()));
    ui->pushButtonGroupDelete->setEnabled(true);
    if (m_fpga->groups() == 8) {
        ui->pushButtonGroupCreate->setEnabled(false);
    }
}

void MainWindow::on_pushButtonGroupDelete_clicked()
{
    if (! m_fpga->remove_group()) {
        show_warning();
    }
    ui->comboBoxCurrentGroup->removeItem(m_fpga->groups());
    if (m_fpga->groups() == 1) {
        ui->pushButtonGroupDelete->setEnabled(false);
    }
    ui->pushButtonGroupCreate->setEnabled(true);
}

void MainWindow::on_comboBoxCurrentGroup_currentIndexChanged(int index)
{
    m_group = m_fpga->get_group(index);
    qDebug()<<__LINE__<<index;
}


void MainWindow::on_comboBoxGroupFreqBand_currentIndexChanged(int index)
{
    if (! m_group->set_freq_band((Group::FreqBand)index, true) ) {
        show_warning();
    }
}

void MainWindow::on_comboBoxGroupVideoFilter_currentIndexChanged(int index)
{
    if (! m_group->enable_video_filter(index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxGroupRectifier_currentIndexChanged(int index)
{
    if (! m_group->set_rectifier(Group::RectifierType(index), true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupCompressRato_valueChanged(int arg1)
{
    if (! m_group->set_compress_rato(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupGain_valueChanged(int arg1)
{
    if (! m_group->set_gain(arg1), true) {
        show_warning();
    }
}


void MainWindow::on_spinBoxGroupThicknessFactor_valueChanged(int arg1)
{
    if (! m_group->set_thickness_factor(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxGroupUt1_currentIndexChanged(int index)
{
    if (! m_group->enable_ut1(index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxGroupUt2_currentIndexChanged(int index)
{
    if (! m_group->enable_ut2(index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxGroupPa_currentIndexChanged(int index)
{
    if (! m_group->enable_pa(index, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupSumGain_valueChanged(int arg1)
{
    if (! m_group->set_sum_gain(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupSampleRange_valueChanged(int arg1)
{
    if (! m_group->set_sample_range(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupPointQty_valueChanged(int arg1)
{
    if (! m_group->set_point_qty(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupTcgPointQty_valueChanged(int arg1)
{
    if (! m_group->set_tcg_point_qty(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxGroupTcg_currentIndexChanged(int index)
{
    if (! m_group->enable_tcg(index, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupRxTime_valueChanged(int arg1)
{
    if (! m_group->set_rx_time(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupIdelTime_valueChanged(int arg1)
{
    if (! m_group->set_idel_time(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupGateAHeight_valueChanged(int arg1)
{
    if (! m_group->set_gate_a_height(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupGateALogic_valueChanged(int arg1)
{
    if (! m_group->set_gate_a_logic(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupGateBHeight_valueChanged(int arg1)
{
    if (! m_group->set_gate_b_height(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupGateBLogic_valueChanged(int arg1)
{
    if (! m_group->set_gate_b_logic(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupGateIHeight_valueChanged(int arg1)
{
    if (! m_group->set_gate_i_height(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupGateILogic_valueChanged(int arg1)
{
    if (! m_group->set_gate_i_logic(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupThinknessMin_valueChanged(int arg1)
{
    if (! m_group->set_thickness_min(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupReject_valueChanged(int arg1)
{
    if (! m_group->set_reject(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupSampleStart_valueChanged(int arg1)
{
    if (! m_group->set_sample_start(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupAverage_valueChanged(int arg1)
{
    if (! m_group->set_average(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupThicknessMax_valueChanged(int arg1)
{
    if (! m_group->set_thickness_max(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupThicknessSource_valueChanged(int arg1)
{
    if (! m_group->set_thickness_source(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupTxEnd_valueChanged(int arg1)
{
    if (! m_group->set_tx_end(arg1, true)) {
        show_warning();
    }
}

void MainWindow::on_spinBoxGroupTxStart_valueChanged(int arg1)
{
    if (! m_group->set_tx_start(arg1)) {
        show_warning();
    }
}

void MainWindow::on_pushButtonGroupReflesh_clicked()
{
    if (! m_group->reflesh()) {
        show_warning();
    }
}
