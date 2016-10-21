#include <QString>
#include <QtTest>
#include "../device.h"

class DeviceTest : public QObject
{
    Q_OBJECT

public:
    DeviceTest();

private Q_SLOTS:
    void test_type();
    void test_serial_number();
    void test_fpga_version();
    void test_run_count();
    void test_run_time();
    void test_time();

private:
    Device *m_device;

};

DeviceTest::DeviceTest()
    :m_device(Device::get_device())
{
}

void DeviceTest::test_type()
{
    qDebug()<<"Type:"<<m_device->type()<<":"<<m_device->type_string();
}

void DeviceTest::test_serial_number()
{
    qDebug()<<"Serial No."<<m_device->serial_number();
}

void DeviceTest::test_fpga_version()
{
    qDebug()<<"Fpga Version:"<<m_device->fpga_version();
}

void DeviceTest::test_run_count()
{
    qDebug()<<"Run Count:"<<m_device->run_count();
}

void DeviceTest::test_run_time()
{
    qDebug()<<"Run Time:"<<m_device->run_time()<<"s";
    sleep(1);
    qDebug()<<"Run Time:"<< m_device->run_time()<<"s";
}

void DeviceTest::test_time()
{
    QDateTime t;
    t.setTime_t(m_device->date_time());
    qDebug()<<__LINE__<<"Device Date:"<<t;
    t = t.addYears(1);
    t = t.addDays(2);
    t = t.addSecs(42);
    m_device->set_date_time(t);
    t.setTime_t(m_device->date_time());
    qDebug()<<__LINE__<<"Device Date:"<<t;
}

QTEST_APPLESS_MAIN(DeviceTest)

#include "devicetest.moc"
