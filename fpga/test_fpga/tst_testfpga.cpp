#include <QString>
#include <QtTest>

#include "../fpga.h"
//#include "../beam.h"
//#include "../group.h"

class TestFpga : public QObject
{
    Q_OBJECT

public:
    TestFpga();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testReset();
    void testBeamIndex();
    void testGroupIndex();
private:
    Fpga *m_fpga;
};

TestFpga::TestFpga()
    : m_fpga(Fpga::get_fpga())//, m_beam(new Beam(2)), m_group(new Group(1))
{
}

void TestFpga::initTestCase()
{
}

void TestFpga::cleanupTestCase()
{
}

void TestFpga::testReset()
{
    QVERIFY2(m_fpga->reset(), "Failure");
}

void TestFpga::testBeamIndex()
{
//    QCOMPARE(m_beam->index(), 2);
}

void TestFpga::testGroupIndex()
{
//    QCOMPARE(m_group->index(), 2);
}


QTEST_APPLESS_MAIN(TestFpga)

#include "tst_testfpga.moc"
