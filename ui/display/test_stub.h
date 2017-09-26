#ifndef TESTSTUB_H
#define TESTSTUB_H

#include <QDebug>

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

    TestStub();

    static TestStub *instance();
    inline TestStub::C_SCAN_SOURCE get_source() { return m_source; }
    inline void set_source(TestStub::C_SCAN_SOURCE source) { qDebug() << " select = " << source; m_source = source;}


private:
    static TestStub *s_instance;
    C_SCAN_SOURCE   m_source;

};

#endif // TESTSTUB_H
