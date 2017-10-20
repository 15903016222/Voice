#ifndef TESTSTUB_H
#define TESTSTUB_H

#include <QDebug>
#include <QReadWriteLock>
#include <QWriteLocker>

static const double  SECOND_T = 1000.0;

class TestStub
{

public:
    enum C_SCAN_SOURCE {
        SOURCE_A,
        SOURCE_B,
        SOURCE_T,
        SOURCE_I,
        SOURCE_OFF
    };

    enum THICKNESS_SOURCE {
        A_POSITION,
        A_POSITION_MINUS_I_POSITION,
        A_POSITION_MINUS_I_AMPLITUDE,
        B_POSITION,
        B_POSITION_MINUS_I_POSITION,
        B_POSITION_MINUS_I_AMPLITUDE,
        B_POSITION_MINUS_A_POSITION,
        I_POSITION,
        I_AMPLITUDE,
    };

    TestStub();

    static TestStub *instance();
    inline TestStub::C_SCAN_SOURCE get_source() { return m_source; }
    inline void set_source(TestStub::C_SCAN_SOURCE source) { qDebug() << " select = " << source; m_source = source;}

    inline TestStub::THICKNESS_SOURCE get_thickness_source() { return m_thicknessSource; }
    inline void set_thickness_source(TestStub::THICKNESS_SOURCE source) { m_thicknessSource = source; }

    inline double get_min_thickness() { return m_minThickness;}
    inline double get_max_thickness() { return m_maxThickness;}

    inline void set_min_thickness(double value) { m_minThickness = value; }
    inline void set_max_thickness(double value) { m_maxThickness = value; }

    inline void update_time(double time) { QWriteLocker l(&m_lock); m_timeCount = time; }
    inline double get_time() { QWriteLocker l(&m_lock); return m_timeCount; }


private:
    static TestStub *s_instance;
    C_SCAN_SOURCE   m_source;
    THICKNESS_SOURCE m_thicknessSource;
    double           m_minThickness;
    double           m_maxThickness;
    volatile double  m_timeCount;
    QReadWriteLock   m_lock;
};

#endif // TESTSTUB_H
