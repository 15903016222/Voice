#include <QString>
#include <QtTest>
#include "../spi.h"

class SpiTest : public QObject
{
    Q_OBJECT

public:
    SpiTest();

private Q_SLOTS:
    void test_open();
    void test_mode();
    void test_send();
private:
    Spi *m_spi;
};

SpiTest::SpiTest()
{
    m_spi = new Spi();
    m_spi->setFileName("/dev/spidev4.0");
    qDebug()<<m_spi->fileName();
}

void SpiTest::test_open()
{
    QVERIFY( m_spi->open(QIODevice::WriteOnly));
}

void SpiTest::test_mode()
{
    QVERIFY( m_spi->set_mode(Spi::MODE0) );
}

void SpiTest::test_send()
{
    char msg[] = {0x11, 0x22, 0x33, 0x44};
    int ret = 0;
    while (1) {
        ret = m_spi->write(msg, 4);
        qDebug()<<"ret="<<ret;
    }
}



QTEST_APPLESS_MAIN(SpiTest)

#include "spi_test.moc"
