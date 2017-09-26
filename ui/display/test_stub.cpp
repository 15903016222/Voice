#include "test_stub.h"

#include <iostream>

TestStub *TestStub::s_instance = NULL;

TestStub::TestStub():
    m_source(SOURCE_A)
{

}

TestStub *TestStub::instance()
{
    if(s_instance == NULL) {
        s_instance = new TestStub;
    }

    return s_instance;
}
