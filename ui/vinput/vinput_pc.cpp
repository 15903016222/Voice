#include "vinput.h"

class VInputPrivate
{
public:
    VInputPrivate() {}
};

QMutex VInput::m_mutex;
VInput *VInput::s_vinput = NULL;

VInput *VInput::get_vinput()
{
    QMutexLocker l(&m_mutex);
    if (s_vinput == NULL) {
        s_vinput = new VInput();
    }
    return s_vinput;
}

void VInput::send(KeyType type, VInput::Key key)
{
    Q_UNUSED(type);
    Q_UNUSED(key);
}

VInput::VInput()
    : d(new VInputPrivate())
{
}

VInput::~VInput()
{
    delete d;
}
