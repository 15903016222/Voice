/**
 * @file vinput.cpp
 * @brief Virtual Key Input
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-20
 */
#include "vinput.h"

/* linux */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <unistd.h>

#include <QDebug>

class VInputPrivate
{
public:
    VInputPrivate();
    ~VInputPrivate();

    void inject_event(quint16 type, quint16 code, qint32 value);

    int fd;
private:
    struct input_event e;
};

VInputPrivate::VInputPrivate()
{
    fd = ::open("/dev/input/uinput", O_WRONLY | O_NDELAY);
    if (fd < 0) {
        fd = ::open("/dev/uinput", O_WRONLY | O_NDELAY);
        if (fd < 0) {
            qCritical()<<"Init VInput failed";
            return;
        }
    }

    ::ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ::ioctl(fd, UI_SET_EVBIT, EV_SYN);

    /* add Key 0-9 */
    for (int i = KEY_1; i <= KEY_0; ++i) {
        ::ioctl(fd, UI_SET_KEYBIT, i);
    }

    ::ioctl(fd, UI_SET_KEYBIT, KEY_ESC);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_MINUS);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_BACKSPACE);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_ENTER);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_DOT);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_UP);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_LEFT);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_RIGHT);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_DOWN);
    ::ioctl(fd, UI_SET_KEYBIT, KEY_DELETE);

    /* configure input device information */
    struct uinput_user_dev uidev;
    ::memset(&uidev, 0, sizeof(uidev));
    ::strncpy(uidev.name, "Doppler-VInput", UINPUT_MAX_NAME_SIZE);
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor  = 0xdea8;
    uidev.id.product = 0x2;
    uidev.id.version = 0x1;
    ::write(fd, &uidev, sizeof(uidev));

    /* create input device */
    ::ioctl(fd, UI_DEV_CREATE);

    ::memset(&e, 0, sizeof(e));
}

VInputPrivate::~VInputPrivate()
{
    ::ioctl(fd, UI_DEV_DESTROY);
    ::close(fd);
}

void VInputPrivate::inject_event(quint16 type, quint16 code, qint32 value)
{
    e.type  = type;
    e.code  = code;
    e.value = value;
    ::write(fd, &e, sizeof(e));
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

void VInput::send(VInput::Key key, bool press, bool sync)
{
    QMutexLocker l(&m_mutex);
    if (d->fd < 0) {
        return;
    }
    d->inject_event(EV_KEY, key, press);
    if (sync) {
        d->inject_event(EV_SYN, SYN_REPORT, 0);
    }
}

VInput::VInput()
    : d(new VInputPrivate())
{
}

VInput::~VInput()
{
    delete d;
}
