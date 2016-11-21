#include "vinput.h"

/* linux */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <QDebug>

class VInputPrivate
{
public:
    VInputPrivate();
    ~VInputPrivate() { ::close(fd); }

    int fd;
    struct Event {
        int type;
        int key;
    };
    Event e;
};

VInputPrivate::VInputPrivate()
{
    fd = ::open("/dev/vkeyboard", O_RDWR|O_NDELAY);
    if (fd < 0) {
        qCritical()<<"Init VInput failed";
    }
}

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
    QMutexLocker l(&m_mutex);
    if (d->fd < 0) {
        return;
    }
    d->e.type = type;
    d->e.key = key;
    ::write(d->fd, &d->e, sizeof(d->e));
}

VInput::VInput()
    : d(new VInputPrivate())
{
}

VInput::~VInput()
{
    delete d;
}
