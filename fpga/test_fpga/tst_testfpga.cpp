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
//    void test_encoder_y();
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
    qDebug()<<"x mode"<<m_fpga->encoder_x_mode();
    QVERIFY(m_fpga->encoder_x_mode() == Fpga::QUAD);
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
