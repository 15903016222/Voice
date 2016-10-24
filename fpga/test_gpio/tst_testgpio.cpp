#include <QString>
#include <QtTest>

#include "../gpio.h"

class TestGpio : public QObject
{
    Q_OBJECT

public:
    TestGpio();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testSet();
private:
    Gpio *m_gpio;
};

TestGpio::TestGpio()
    :m_gpio(Gpio::get_gpio())
{
//    delete &m_gpio;
}

void TestGpio::initTestCase()
{
}

void TestGpio::cleanupTestCase()
{
}

void TestGpio::testSet()
{
    QVERIFY2(m_gpio->set(Gpio::PIN_43, Gpio::HIGHT), "Failure");
    QVERIFY2(m_gpio->set(Gpio::PIN_43, Gpio::LOW), "Failure");
    QVERIFY2(m_gpio->set(Gpio::PIN_61, Gpio::HIGHT), "Failure");
    QVERIFY2(m_gpio->set(Gpio::PIN_61, Gpio::LOW), "Failure");
}

QTEST_APPLESS_MAIN(TestGpio)

#include "tst_testgpio.moc"
