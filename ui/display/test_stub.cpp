#include "test_stub.h"

#include <iostream>

TestStub *TestStub::s_instance = NULL;

TestStub::TestStub():
    m_source(SOURCE_A),
    m_thicknessSource(A_POSITION_MINUS_I_POSITION),
    m_timeCount(0.0)
{

}

TestStub *TestStub::instance()
{
    if(s_instance == NULL) {
        s_instance = new TestStub;
    }

    return s_instance;
}


