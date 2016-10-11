#include <QString>
#include <QtTest>

#include "../fpga.h"

class TestFpga : public QObject
{
    Q_OBJECT

public:
    TestFpga();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    /* 测试Fpga */
    void test_reset();
    void test_freezing();
    void test_pa_law_qty();
    void test_ut_law_qty();
    void test_encoder_x();
    void test_encoder_y();
    void test_ut1_twin();
    void test_ut2_twin();
    void test_ut1_damping();
    void test_ut2_damping();
    void test_ut_voltage();
    void test_pa_voltage();
    void test_power();
    void test_rx_channels();
    void test_sound();

    /** AlarmOutput **/
    void test_alarm_output_valid();
    void test_alarm_output_logic_group();
    void test_alarm_output_op();
    void test_alarm_output_condition();
    void test_alarm_output_count();
    void test_alarm_output_delay();
    void test_alarm_output_hold_time();
    /** AlarmAnalog **/
    void test_alarm_analog_valid();
    void test_alarm_analog_logic_group();
    void test_alarm_analog_type();

    void test_factor_echo();

    /* 测试Group */
    void test_group();
    void test_group_index();
    void test_group_freq_band();
    void test_group_video_filter();
    void test_group_rectifier();
    void test_group_compress_rato();
    void test_group_gain();
    void test_group_thickness_factor();
    void test_group_ut1();
    void test_group_ut2();
    void test_group_pa();
    void test_group_sum_gain();
    void test_group_sample_range();
    void test_group_point_qty();
    void test_group_tcg_point_qty();
    void test_group_tcg();
    void test_group_rx_time();
    void test_group_idel_time();
    void test_group_gate_a_height();
    void test_group_gate_a_logic();
    void test_group_gate_b_height();
    void test_group_gate_b_logic();
    void test_group_gate_i_height();
    void test_group_gate_i_logic();
    void test_group_thickness_min();
    void test_group_reject();
    void test_group_sample_start();
    void test_group_average();
    void test_group_thickness_max();
    void test_group_thickness_source();
    void test_group_tx_end();
    void test_group_tx_start();
    void test_reflesh();

    /* 测试Beam */
    void test_beam();
    void test_beam_index();
    void test_beam_gain_offset(void);
    void test_beam_group_id(void);
    void test_beam_info(void);
    void test_beam_delay(void);
    void test_beam_gate_a_start(void);
    void test_beam_gate_a_end(void);
    void test_beam_gate_b_start(void);
    void test_beam_gate_b_end(void);
    void test_beam_gate_i_start(void);
    void test_beam_gate_i_end(void);
    void test_beam_tx(void);
    void test_beam_rx(void);
    void test_beam_rx_channel_select(void);
    void test_beam_tx_channel_select(void);
    void test_beam_tx_delay(void);
    void test_beam_rx_delay(void);
    void test_beam_tcg_position(void);
    void test_beam_tcg_slope(void);
    void test_beam_tcg_flag(void);
    void test_beam_refresh(void);
private:
    Fpga *m_fpga;
};

TestFpga::TestFpga()
    : m_fpga(Fpga::get_fpga())
{
}

void TestFpga::initTestCase()
{
}

void TestFpga::cleanupTestCase()
{
}

void TestFpga::test_reset()
{
    QVERIFY2(m_fpga->reset(), "Failure");
}

void TestFpga::test_freezing()
{
    QVERIFY(m_fpga->is_freeze() == false);
    QVERIFY(m_fpga->set_freeze(true));
    QVERIFY(m_fpga->is_freeze());
    QVERIFY(m_fpga->set_freeze(false));
    QVERIFY(m_fpga->is_freeze() == false);
}

void TestFpga::test_pa_law_qty()
{
    QVERIFY(m_fpga->set_pa_law_qty(6, true));
    QVERIFY(m_fpga->pa_law_qty() == 6);
}

void TestFpga::test_ut_law_qty()
{
    QVERIFY(m_fpga->set_ut_law_qty(8, true));
    QVERIFY(m_fpga->ut_law_qty() == 8);
}

void TestFpga::test_encoder_x()
{
    QVERIFY(m_fpga->encoder_x_mode() == Fpga::QUAD);
    QVERIFY(m_fpga->encoder_x_polarity() == Fpga::NORMAL);

    QVERIFY(m_fpga->set_encoder_x(Fpga::UP, Fpga::INVERSE, true));
    QVERIFY(m_fpga->encoder_x_mode() == Fpga::UP);
    QVERIFY(m_fpga->encoder_x_polarity() == Fpga::INVERSE);

    QVERIFY(m_fpga->set_encoder_x(Fpga::DOWN));
    QVERIFY(m_fpga->encoder_x_mode() == Fpga::DOWN);
    QVERIFY(m_fpga->encoder_x_polarity() == Fpga::NORMAL);
}

void TestFpga::test_encoder_y()
{
    QVERIFY(m_fpga->encoder_y_mode() == Fpga::QUAD);
    QVERIFY(m_fpga->encoder_y_polarity() == Fpga::NORMAL);

    QVERIFY(m_fpga->set_encoder_y(Fpga::UP, Fpga::INVERSE, true));
    QVERIFY(m_fpga->encoder_y_mode() == Fpga::UP);
    QVERIFY(m_fpga->encoder_y_polarity() == Fpga::INVERSE);

    QVERIFY(m_fpga->set_encoder_y(Fpga::DOWN));
    QVERIFY(m_fpga->encoder_y_mode() == Fpga::DOWN);
    QVERIFY(m_fpga->encoder_y_polarity() == Fpga::NORMAL);
}

void TestFpga::test_ut1_twin()
{
    QVERIFY( ! m_fpga->ut1_twin() );
    QVERIFY( m_fpga->set_ut1_twin(true, true) );
    QVERIFY( m_fpga->ut1_twin() );
    QVERIFY( m_fpga->set_ut1_twin(false, true) );
    QVERIFY( ! m_fpga->ut1_twin() );
}

void TestFpga::test_ut2_twin()
{
    QVERIFY( ! m_fpga->ut2_twin() );
    QVERIFY( m_fpga->set_ut2_twin(true, true) );
    QVERIFY( m_fpga->ut2_twin() );
    QVERIFY( m_fpga->set_ut2_twin(false, true) );
    QVERIFY( ! m_fpga->ut2_twin() );
}

void TestFpga::test_ut1_damping()
{
    QVERIFY( m_fpga->ut1_tx_damping() == Fpga::R50 );
    QVERIFY( m_fpga->set_ut1_tx_damping(Fpga::R100, true) );
    QVERIFY( m_fpga->ut1_tx_damping() == Fpga::R100 );
    QVERIFY( m_fpga->set_ut1_tx_damping(Fpga::R200, true) );
    QVERIFY( m_fpga->ut1_tx_damping() == Fpga::R200 );
    QVERIFY( m_fpga->set_ut1_tx_damping(Fpga::R500, true) );
    QVERIFY( m_fpga->ut1_tx_damping() == Fpga::R500 );
}

void TestFpga::test_ut2_damping()
{
    QVERIFY( m_fpga->ut2_tx_damping() == Fpga::R50 );
    QVERIFY( m_fpga->set_ut2_tx_damping(Fpga::R100, true) );
    QVERIFY( m_fpga->ut2_tx_damping() == Fpga::R100 );
    QVERIFY( m_fpga->set_ut2_tx_damping(Fpga::R200, true) );
    QVERIFY( m_fpga->ut2_tx_damping() == Fpga::R200 );
    QVERIFY( m_fpga->set_ut2_tx_damping(Fpga::R500, true) );
    QVERIFY( m_fpga->ut2_tx_damping() == Fpga::R500 );
}

void TestFpga::test_ut_voltage()
{
    QVERIFY( m_fpga->ut_voltage() == Fpga::VOLTAGE_LOW );
    QVERIFY( m_fpga->set_ut_voltage(Fpga::VOLTAGE_MIDDLE, true) );
    QVERIFY( m_fpga->ut_voltage() == Fpga::VOLTAGE_MIDDLE );
    QVERIFY( m_fpga->set_ut_voltage(Fpga::VOLTAGE_HIGHT, true) );
    QVERIFY( m_fpga->ut_voltage() == Fpga::VOLTAGE_HIGHT );
}

void TestFpga::test_pa_voltage()
{
    QVERIFY( m_fpga->pa_voltage() == Fpga::VOLTAGE_LOW );
    QVERIFY( m_fpga->set_pa_voltage(Fpga::VOLTAGE_MIDDLE, true) );
    QVERIFY( m_fpga->pa_voltage() == Fpga::VOLTAGE_MIDDLE );
    QVERIFY( m_fpga->set_pa_voltage(Fpga::VOLTAGE_HIGHT, true) );
    QVERIFY( m_fpga->pa_voltage() == Fpga::VOLTAGE_HIGHT );
}

void TestFpga::test_power()
{
    QVERIFY( m_fpga->power() == Fpga::NONE_POWER_MODE );
}

void TestFpga::test_rx_channels()
{
    QVERIFY( m_fpga->rx_channels() == 0 );
    QVERIFY( m_fpga->set_rx_channels(0b01, true));
    QVERIFY( m_fpga->rx_channels() == 0b01 );
}

void TestFpga::test_sound()
{
    QVERIFY( m_fpga->sound() == Fpga::SOUND_OFF );
    QVERIFY( m_fpga->set_sound(Fpga::SOUND_300HZ, true) );
    QVERIFY( m_fpga->sound() == Fpga::SOUND_300HZ );
    QVERIFY( m_fpga->set_sound(Fpga::SOUND_600HZ, true) );
    QVERIFY( m_fpga->sound() == Fpga::SOUND_600HZ );
    QVERIFY( m_fpga->set_sound(Fpga::SOUND_1000HZ, true) );
    QVERIFY( m_fpga->sound() == Fpga::SOUND_1000HZ );
    QVERIFY( m_fpga->set_sound(Fpga::SOUND_5000HZ, true) );
    QVERIFY( m_fpga->sound() == Fpga::SOUND_5000HZ );
}

void TestFpga::test_alarm_output_valid()
{
    AlarmOutput *output = m_fpga->alarm_output(0);
    QVERIFY( ! output->is_valid() );
    QVERIFY( output->set_valid(true, true) );
    QVERIFY( output->is_valid() );

    output = m_fpga->alarm_output(1);
    QVERIFY( ! output->is_valid() );
    QVERIFY( output->set_valid(true, true) );
    QVERIFY( output->is_valid() );

    output = m_fpga->alarm_output(2);
    QVERIFY( ! output->is_valid() );
    QVERIFY( output->set_valid(true, true) );
    QVERIFY( output->is_valid() );

    output = m_fpga->alarm_output(3);
    QVERIFY( output == NULL );
}

void TestFpga::test_alarm_output_logic_group()
{
    AlarmOutput *output = m_fpga->alarm_output(0);
    QVERIFY( output->logic_group() == 0 );
    QVERIFY( output->set_logic_group(0b11, true) );
    QVERIFY( output->logic_group() == 0b11 );

    output = m_fpga->alarm_output(1);
    QVERIFY( output->logic_group() == 0 );
    QVERIFY( output->set_logic_group(0b11, true) );
    QVERIFY( output->logic_group() == 0b11 );

    output = m_fpga->alarm_output(2);
    QVERIFY( output->logic_group() == 0 );
    QVERIFY( output->set_logic_group(0b11, true) );
    QVERIFY( output->logic_group() == 0b11 );
}

void TestFpga::test_alarm_output_op()
{
    AlarmOutput *output = m_fpga->alarm_output(0);
    QVERIFY( output->op() == AlarmOutput::AND );
    QVERIFY( output->set_op(AlarmOutput::OR, true) );
    QVERIFY( output->op() == AlarmOutput::OR );

    output = m_fpga->alarm_output(1);
    QVERIFY( output->op() == AlarmOutput::AND );
    QVERIFY( output->set_op(AlarmOutput::OR) );
    QVERIFY( output->op() == AlarmOutput::OR );

    output = m_fpga->alarm_output(2);
    QVERIFY( output->op() == AlarmOutput::AND );
    QVERIFY( output->set_op(AlarmOutput::OR, true) );
    QVERIFY( output->op() == AlarmOutput::OR );
}

void TestFpga::test_alarm_output_condition()
{
    AlarmOutput *output = m_fpga->alarm_output(0);
    QVERIFY( output->condition(0) == AlarmOutput::CONDITION_NONE );
    QVERIFY( output->set_condition(0, AlarmOutput::CONDITION_GATE_A, true) );
    QVERIFY( output->condition(0) == AlarmOutput::CONDITION_GATE_A );
    QVERIFY( output->condition(1) == AlarmOutput::CONDITION_NONE );
    QVERIFY( output->set_condition(1, AlarmOutput::CONDITION_GATE_B, true) );
    QVERIFY( output->condition(1) == AlarmOutput::CONDITION_GATE_B );

    output = m_fpga->alarm_output(1);
    QVERIFY( output->condition(0) == AlarmOutput::CONDITION_NONE );
    QVERIFY( output->set_condition(0, AlarmOutput::CONDITION_GATE_I, true) );
    QVERIFY( output->condition(0) == AlarmOutput::CONDITION_GATE_I );
    QVERIFY( output->condition(1) == AlarmOutput::CONDITION_NONE );
    QVERIFY( output->set_condition(1, AlarmOutput::CONDITION_NOT_GATE_A, true) );
    QVERIFY( output->condition(1) == AlarmOutput::CONDITION_NOT_GATE_A );

    output = m_fpga->alarm_output(2);
    QVERIFY( output->condition(0) == AlarmOutput::CONDITION_NONE );
    QVERIFY( output->set_condition(0, AlarmOutput::CONDITION_NOT_GATE_B, true) );
    QVERIFY( output->condition(0) == AlarmOutput::CONDITION_NOT_GATE_B );
    QVERIFY( output->condition(1) == AlarmOutput::CONDITION_NONE );
    QVERIFY( output->set_condition(1, AlarmOutput::CONDITION_MAX_THICKNESS, true) );
    QVERIFY( output->condition(1) == AlarmOutput::CONDITION_MAX_THICKNESS );
}

void TestFpga::test_alarm_output_count()
{
    AlarmOutput *output = m_fpga->alarm_output(0);
    QVERIFY( output->count() == 0 );
    QVERIFY( output->set_count(99, true) );
    QVERIFY( output->count() == 99 );
    QVERIFY( ! output->set_count(101, true) );

    output = m_fpga->alarm_output(1);
    QVERIFY( output->count() == 0 );
    QVERIFY( output->set_count(92, true) );
    QVERIFY( output->count() == 92 );
    QVERIFY( ! output->set_count(132, true) );

    output = m_fpga->alarm_output(2);
    QVERIFY( output->count() == 0 );
    QVERIFY( output->set_count(49, true) );
    QVERIFY( output->count() == 49 );
    QVERIFY( ! output->set_count(210, true) );
}

void TestFpga::test_alarm_output_delay()
{
    AlarmOutput *output = m_fpga->alarm_output(0);
    QVERIFY( output->delay() == 0 );
    QVERIFY( output->set_delay(5000, true) );
    QVERIFY( output->delay() == 5000 );
    QVERIFY( ! output->set_delay(5001*1000, true) );

    output = m_fpga->alarm_output(1);
    QVERIFY( output->delay() == 0 );
    QVERIFY( output->set_delay(45000, true) );
    QVERIFY( output->delay() == 45000 );
    QVERIFY( ! output->set_delay(5001*1000, true) );

    output = m_fpga->alarm_output(2);
    QVERIFY( output->delay() == 0 );
    QVERIFY( output->set_delay(500, true) );
    QVERIFY( output->delay() == 500 );
    QVERIFY( ! output->set_delay(5001*1000, true) );
}

void TestFpga::test_alarm_output_hold_time()
{
    AlarmOutput *output = m_fpga->alarm_output(0);
    QVERIFY( output->hold_time() == 0 );
    QVERIFY( output->set_hold_time(4924, true) );
//    qDebug()<<"alarm output0 hold time:"<<output->hold_time();
    QVERIFY( output->hold_time() == 4920 );

    output = m_fpga->alarm_output(1);
    QVERIFY( output->hold_time() == 0 );
    QVERIFY( output->set_hold_time(5002, true) );
    QVERIFY( output->hold_time() == 5000 );

    output = m_fpga->alarm_output(2);
    QVERIFY( output->hold_time() == 0 );
    QVERIFY( ! output->set_hold_time(5001*1000) );
    QVERIFY( output->hold_time() == 0 );
}

void TestFpga::test_alarm_analog_valid()
{
    AlarmAnalog *a = m_fpga->alarm_analog(0);
    QVERIFY( ! a->is_valid() );
    QVERIFY( a->set_valid(true, true) );
    QVERIFY( a->is_valid() );

    a = m_fpga->alarm_analog(1);
    QVERIFY( ! a->is_valid() );
    QVERIFY( a->set_valid(true, true) );
    QVERIFY( a->is_valid() );

    a = m_fpga->alarm_analog(2);
    QVERIFY( a == NULL );
}

void TestFpga::test_alarm_analog_logic_group()
{
    AlarmAnalog *a = m_fpga->alarm_analog(0);
    QVERIFY( a->logic_group() == 0 );
    QVERIFY( a->set_logic_group(0b11, true) );
    QVERIFY( a->logic_group() == 0b11 );

    a = m_fpga->alarm_analog(1);
    QVERIFY( a->logic_group() == 0 );
    QVERIFY( a->set_logic_group(0b10, true) );
    QVERIFY( a->logic_group() == 0b10 );
}

void TestFpga::test_alarm_analog_type()
{
    AlarmAnalog *a = m_fpga->alarm_analog(0);
    QVERIFY( a->type() == AlarmAnalog::NONE );
    QVERIFY( a->set_type(AlarmAnalog::GATE_A, true) );
    QVERIFY( a->type() == AlarmAnalog::GATE_A );

    a = m_fpga->alarm_analog(1);
    QVERIFY( a->type() == AlarmAnalog::NONE );
    QVERIFY( a->set_type(AlarmAnalog::GATE_B, true) );
    QVERIFY( a->type() == AlarmAnalog::GATE_B );
}

void TestFpga::test_factor_echo()
{
    QVERIFY( m_fpga->factor_echo() == 0 );
    QVERIFY( m_fpga->set_factor_echo(405, true) );
    QVERIFY( m_fpga->factor_echo() == 405 );
}

void TestFpga::test_group()
{
    qDebug()<<"-------- Testing Group --------";
    QVERIFY( m_fpga->groups() == 0 );
    for (int i = 0; i < Fpga::MAX_GROUPS_NUM; ++i) {
        QVERIFY ( m_fpga->create_group() );
    }
    GroupPointer grp = m_fpga->get_group(0);
    QVERIFY( ! grp.isNull() );
    while ( m_fpga->groups() ) {
        QVERIFY( m_fpga->remove_group() );
    }
}

void TestFpga::test_group_index()
{
    if (m_fpga->groups() <= 0) {
        QVERIFY( m_fpga->create_group() );
    }
    qDebug()<<__LINE__;
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<__LINE__;
    QVERIFY( ! grp.isNull() );
    QVERIFY( grp->index() == m_fpga->groups()-1 );
    QVERIFY( m_fpga->remove_group() );
    qDebug()<<"group index:"<<grp->index();
}

void TestFpga::test_group_freq_band()
{
    if (m_fpga->groups() <= 0) {
        QVERIFY( m_fpga->create_group() );
    }
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<__LINE__;
    QVERIFY( grp->freq_band() == Group::FREQ_BAND_05_20 );
    qDebug()<<__LINE__;
    QVERIFY( grp->set_freq_band(Group::FREQ_BAND_20_100, true) );
    QVERIFY( grp->freq_band() == Group::FREQ_BAND_20_100 );
}

void TestFpga::test_group_video_filter()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( ! grp->video_filter() );
    QVERIFY( grp->enable_video_filter(true, true) );
    QVERIFY( grp->video_filter() );
}

void TestFpga::test_group_rectifier()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( grp->rectifier() == Group::RF );
    QVERIFY( grp->set_rectifier(Group::POSITIVE_HW, true) );
    QVERIFY( grp->rectifier() == Group::POSITIVE_HW );
}

void TestFpga::test_group_compress_rato()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( grp->compress_rato() == 0 );
    QVERIFY( grp->set_compress_rato(20, true) );
    QVERIFY( grp->compress_rato() == 20 );
}

void TestFpga::test_group_gain()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( grp->gain() == 1);
    QVERIFY( grp->set_gain(20, true) );
    QVERIFY( grp->gain() == 20 );
}

void TestFpga::test_group_thickness_factor()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( grp->thickness_factor() == 0 );
    QVERIFY( grp->set_thickness_factor(10, true) );
    QVERIFY( grp->thickness_factor() == 10 );
}

void TestFpga::test_group_ut1()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( ! grp->ut1() );
    QVERIFY( grp->enable_ut1(true, true) );
    QVERIFY( grp->ut1() );
}

void TestFpga::test_group_ut2()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( ! grp->ut2() );
    QVERIFY( grp->enable_ut2(true, true) );
    QVERIFY( grp->ut2() );
}

void TestFpga::test_group_pa()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    QVERIFY( ! grp->pa() );
    QVERIFY( grp->enable_pa(true, true) );
    QVERIFY( grp->pa() );
}

void TestFpga::test_group_sum_gain()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"sum gain:"<<grp->sum_gain();
    QVERIFY( grp->set_sum_gain(20, true) );
    QVERIFY( grp->sum_gain() == 20 );
}

void TestFpga::test_group_sample_range()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"sample range:"<<grp->sample_range();
    QVERIFY( grp->set_sample_range(20, true) );
    QVERIFY( grp->sample_range() == 20 );
}

void TestFpga::test_group_point_qty()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"point qty:"<<grp->point_qty();
    QVERIFY( grp->set_point_qty(30, true) );
    QVERIFY( grp->point_qty() == 30 );
}

void TestFpga::test_group_tcg_point_qty()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"tcg point qty:"<<grp->tcg_point_qty();
    QVERIFY( grp->set_tcg_point_qty(25, true) );
    QVERIFY( grp->tcg_point_qty() == 25 );
}

void TestFpga::test_group_tcg()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"tcg enable:"<<grp->tcg();
    QVERIFY( grp->enable_tcg(true, true) );
    QVERIFY( grp->tcg() );
}

void TestFpga::test_group_rx_time()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"rx time:"<<grp->rx_time();
    QVERIFY( grp->set_rx_time(11, true) );
    QVERIFY( grp->rx_time() == 11 );
}

void TestFpga::test_group_idel_time()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"idel time:"<<grp->idel_time();
    QVERIFY( grp->set_idel_time(56, true) );
    QVERIFY( grp->idel_time() == 56 );
}

void TestFpga::test_group_gate_a_height()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"gate a height:"<<grp->gate_a_height();
    QVERIFY( grp->set_gate_a_height(76, true) );
    QVERIFY( grp->gate_a_height() == 76 );
}

void TestFpga::test_group_gate_a_logic()
{
    GroupPointer grp = m_fpga->get_group(m_fpga->groups()-1);
    qDebug()<<"gate a logic:"<<grp->gate_a_logic();
    QVERIFY( grp->set_gate_a_logic(34, true) );
    QVERIFY( grp->gate_a_logic() );
}

void TestFpga::test_group_gate_b_height()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"gate b height:"<<grp->gate_b_height();
    QVERIFY( grp->set_gate_b_height(23, true) );
    QVERIFY( grp->gate_b_height() == 23 );
}

void TestFpga::test_group_gate_b_logic()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"gate b logic:"<<grp->gate_b_logic();
    QVERIFY( grp->set_gate_b_logic(12, true) );
    QVERIFY( grp->gate_b_logic() == 12 );
}

void TestFpga::test_group_gate_i_height()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"gate i height:"<<grp->gate_i_height();
    QVERIFY( grp->set_gate_i_height(23, true) );
    QVERIFY( grp->gate_i_height() == 23 );
}

void TestFpga::test_group_gate_i_logic()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"gate i logic:"<<grp->gate_i_logic();
    QVERIFY( grp->set_gate_i_logic(21, true) );
    QVERIFY( grp->gate_i_logic() == 21 );
}

void TestFpga::test_group_thickness_min()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"thickness min:"<<grp->thickness_min();
    QVERIFY( grp->set_thickness_min(12, true) );
    QVERIFY( grp->thickness_min() == 12 );
}

void TestFpga::test_group_reject()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"reject:"<<grp->reject();
    QVERIFY( grp->set_reject(11, true) );
    QVERIFY( grp->reject() == 11 );
}

void TestFpga::test_group_sample_start()
{
    GroupPointer &grp = m_fpga->get_group(0);
    qDebug()<<"grp addr:"<<&grp;
    grp = m_fpga->get_group(0);
    qDebug()<<"grp addr:"<<&grp;
    qDebug()<<"sample_start:"<<grp->sample_start();
    QVERIFY( grp->set_sample_start(12, true) );
    QVERIFY( grp->sample_start() == 12 );
}

void TestFpga::test_group_average()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"average:"<<grp->average();
    QVERIFY( grp->set_average(5, true) );
    QVERIFY( grp->average() == 5 );
}

void TestFpga::test_group_thickness_max()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"thickness max:"<<grp->thickness_max();
    QVERIFY( grp->set_thickness_max(34, true) );
    QVERIFY( grp->thickness_max() == 34 );
}

void TestFpga::test_group_thickness_source()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"thickness source:"<<grp->thickness_source();
    QVERIFY( grp->set_thickness_source(11, true) );
    QVERIFY( grp->thickness_source() == 11 );
}

void TestFpga::test_group_tx_end()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"tx end:"<<grp->tx_end();
    QVERIFY( grp->set_tx_end(42, true) );
    QVERIFY( grp->tx_end() == 42 );
}

void TestFpga::test_group_tx_start()
{
    GroupPointer grp = m_fpga->get_group(0);
    qDebug()<<"tx start:"<<grp->tx_start();
    QVERIFY( grp->set_tx_start(12, true) );
    QVERIFY( grp->tx_start() == 12 );
}

void TestFpga::test_reflesh()
{
    GroupPointer grp = m_fpga->get_group(0);
    QVERIFY( grp->reflesh() );
}

void TestFpga::test_beam()
{
    qDebug()<<"******** Testing Beam ********";
    QVERIFY( m_fpga->beams() == 0 );
    for (int i = 0; i < 1024; ++i) {
        QVERIFY( m_fpga->create_beam() );
    }
    QVERIFY( m_fpga->beams() == 1024 );
    BeamPointer beam = m_fpga->get_beam(0);
    QVERIFY( ! beam.isNull() );
    while( m_fpga->beams() ) {
        QVERIFY( m_fpga->remove_beam() );
    }
}

void TestFpga::test_beam_index()
{
    if ( m_fpga->beams() == 0 ) {
        m_fpga->create_beam();
    }
    QVERIFY( m_fpga->beams() );
    qDebug()<<"beam index:"<<m_fpga->get_beam(0)->index();
    m_fpga->get_beam(0)->set_index(2);
    QVERIFY( m_fpga->get_beam(0)->index() == 2 );
}

void TestFpga::test_beam_gain_offset()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"gain offset:"<<b->gain_offset();
    b->set_gain_offset(23);
    QVERIFY( b->gain_offset() == 23 );
}

void TestFpga::test_beam_group_id()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"group id"<<b->group_id();
    b->set_group_id(3);
    QVERIFY( b->group_id() == 3 );
}

void TestFpga::test_beam_info()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"info:"<<b->info();
    b->set_info(34);
    QVERIFY( b->info() == 34 );
}

void TestFpga::test_beam_delay()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"delay:"<<b->delay();
    b->set_delay(20);
    QVERIFY( b->delay() == 20 );
}

void TestFpga::test_beam_gate_a_start()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"gate a start:"<<b->gate_a_start();
    b->set_gate_a_start(25);
    QVERIFY( b->gate_a_start() == 25 );
}

void TestFpga::test_beam_gate_a_end()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"gate a end:"<<b->gate_a_end();
    b->set_gate_a_end(56);
    QVERIFY( b->gate_a_end() == 56 );
}

void TestFpga::test_beam_gate_b_start()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"gate b start:"<<b->gate_b_start();
    b->set_gate_b_start(31);
    QVERIFY( b->gate_b_start() == 31 );
}

void TestFpga::test_beam_gate_b_end()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"gate a end:"<<b->gate_b_end();
    b->set_gate_b_end(76);
    QVERIFY( b->gate_b_end() == 76 );
}

void TestFpga::test_beam_gate_i_start()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"gate a start:"<<b->gate_i_start();
    b->set_gate_i_start(2);
    QVERIFY( b->gate_i_start() == 2 );
}

void TestFpga::test_beam_gate_i_end()
{
    BeamPointer b= m_fpga->get_beam(0);
    qDebug()<<"gate a end:"<<b->gate_i_end();
    b->set_gate_i_end(50);
    QVERIFY( b->gate_i_end() == 50 );
}

void TestFpga::test_beam_tx()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"tx channel:"<<b->tx_channel();
    b->set_tx_channel(35);
    QVERIFY( b->tx_channel() == 35 );
}

void TestFpga::test_beam_rx()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"rx channel:"<<b->rx_channel();
    b->set_rx_channel(25);
    QVERIFY( b->rx_channel() == 25 );
}

void TestFpga::test_beam_rx_channel_select()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"rx channel start:"<<b->rx_channel_select();
    QVERIFY( b->set_rx_channel_select(42) );
    qDebug()<<"rx channel start:"<<b->rx_channel_select();
    QVERIFY( b->rx_channel_select() == 42 );
}

void TestFpga::test_beam_tx_channel_select()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"tx channel start:"<<b->tx_channel_select();
    QVERIFY( b->set_tx_channel_select(43) );
    qDebug()<<"tx channel start:"<<b->tx_channel_select();
    QVERIFY( b->tx_channel_select() == 43 );
}

void TestFpga::test_beam_tx_delay()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"tx channel4 delay:"<<b->tx_delay(4);
    QVERIFY( b->set_tx_delay(4, 34) );
    qDebug()<<"tx channel4 delay:"<<b->tx_delay(4);
    QVERIFY( b->tx_delay(4) == 34 );
}

void TestFpga::test_beam_rx_delay()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"rx channel5 delay:"<<b->rx_delay(5);
    QVERIFY( b->set_rx_delay(5, 32) );
    qDebug()<<"rx channel5 delay:"<<b->rx_delay(5);
    QVERIFY( b->rx_delay(5) == 32 );
}

void TestFpga::test_beam_tcg_position()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"tcg point2 position:"<<b->tcg_position(2)*10<<"ns";
    QVERIFY( b->set_tcg_position(2, 23) );
    qDebug()<<"tcg point2 position:"<<b->tcg_position(2)*10<<"ns";
    QVERIFY( b->tcg_position(2) == 23 );
}

void TestFpga::test_beam_tcg_slope()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"tcg point3 slope:"<<b->tcg_slope(3);
    QVERIFY( b->set_tcg_slope(3, 12) );
}

void TestFpga::test_beam_tcg_flag()
{
    BeamPointer b = m_fpga->get_beam(0);
    qDebug()<<"tcg point7 flag:"<<b->tcg_flag(7);
    QVERIFY( b->set_tcg_flag(7, true) );
    QVERIFY( b->tcg_flag(7) == true );
}

void TestFpga::test_beam_refresh()
{
    BeamPointer b = m_fpga->get_beam(0);
    QVERIFY( b->refresh() );
}

QTEST_APPLESS_MAIN(TestFpga)

#include "tst_testfpga.moc"
