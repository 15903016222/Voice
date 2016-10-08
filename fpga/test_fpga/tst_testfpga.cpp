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
    /** AlarmOutput **/
//    void test_valid();
//    void test_logic_group();
//    void test_op();
    /* 测试Group */
    void test_group_index();
    /* 测试Beam */
    void test_beam_index();
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
    QVERIFY(m_fpga->freezing() == false);
    QVERIFY(m_fpga->set_freezing(true));
    QVERIFY(m_fpga->freezing());
    QVERIFY(m_fpga->set_freezing(false));
    QVERIFY(m_fpga->freezing() == false);
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
    QVERIFY( m_fpga->ut1_damping() == Fpga::R50 );
    QVERIFY( m_fpga->set_ut1_damping(Fpga::R100, true) );
    QVERIFY( m_fpga->ut1_damping() == Fpga::R100 );
    QVERIFY( m_fpga->set_ut1_damping(Fpga::R200, true) );
    QVERIFY( m_fpga->ut1_damping() == Fpga::R200 );
    QVERIFY( m_fpga->set_ut1_damping(Fpga::R500, true) );
    QVERIFY( m_fpga->ut1_damping() == Fpga::R500 );
}

void TestFpga::test_ut2_damping()
{
    QVERIFY( m_fpga->ut2_damping() == Fpga::R50 );
    QVERIFY( m_fpga->set_ut2_damping(Fpga::R100, true) );
    QVERIFY( m_fpga->ut2_damping() == Fpga::R100 );
    QVERIFY( m_fpga->set_ut2_damping(Fpga::R200, true) );
    QVERIFY( m_fpga->ut2_damping() == Fpga::R200 );
    QVERIFY( m_fpga->set_ut2_damping(Fpga::R500, true) );
    QVERIFY( m_fpga->ut2_damping() == Fpga::R500 );
}

void TestFpga::test_beam_index()
{
//    QCOMPARE(m_beam->index(), 2);
}

void TestFpga::test_group_index()
{
//    QCOMPARE(m_group->index(), 2);
}


QTEST_APPLESS_MAIN(TestFpga)

#include "tst_testfpga.moc"
