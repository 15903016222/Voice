

#include "device.h"
#include "cert.h"

#include <QFile>
#include <QReadWriteLock>
#include <QDebug>

/* unix */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

static const char *CERT_FILE = "/etc/mercury/cert";
static const char *PUB_PEM_FILE = "/etc/mercury/pem";
static const char *TIME_FILE = "/etc/mercury/time";

static const int TYPE_MAX = Device::DEV_32_128_PRO_TOFD+1;
static const QString s_typeMap[TYPE_MAX] = {
    QString("16-64-TOFD"),
    QString("32-64-TOFD"),
    QString("32-128-TOFD"),
    QString("32-128-PRO-TOFD")
};

class DevicePrivate
{
public:
    DevicePrivate();

    QString m_serialNo;
    QString m_version;
    Cert m_cert;
    Device::Type m_type;
    time_t m_time;

    QReadWriteLock m_rwlock;
private:
    QString get_serial_number();
    QByteArray get_version();
    time_t get_time();
};

DevicePrivate::DevicePrivate()
{
    m_serialNo = get_serial_number();
    m_version = get_version();

    m_cert.load(CERT_FILE, PUB_PEM_FILE);
    for (int i = 0; i < TYPE_MAX; ++i) {
        if (s_typeMap[i] == m_cert.get_device_type()) {
            m_type = (Device::Type)i;
        }
    }

    m_time = get_time();
}

QString DevicePrivate::get_serial_number()
{
    QString serialNo;
    int fd = ::open("/dev/mem", O_RDWR | O_NDELAY);
    unsigned char *base = NULL;

    if ( fd < 0) {
        qWarning("Can't Open /dev/mem");
        return serialNo;
    }

    base = (unsigned char *)
            ::mmap (NULL,  1*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd,0x021bc000);

    if (base == MAP_FAILED) {
        ::close(fd);
        return serialNo;
    }

    serialNo.sprintf("%08lx-%08lx-%08lx-%08lx",
                     *(volatile long *)(base+0x410),
                     *(volatile long *)(base+0x420),
                     *(volatile long *)(base+0x430),
                     *(volatile long *)(base+0x440)
                     );

//    serialNo.sprintf("%08lx-%08lx-%08lx-%08lx-%08lx-%08lx--%08lx",
//                     *(volatile long *)(base+0x410),
//                     *(volatile long *)(base+0x420),
//                     *(volatile long *)(base+0x430),
//                     *(volatile long *)(base+0x440),
//                     *(volatile long *)(base+0x450),
//                     *(volatile long *)(base+0x460),
//                     *(volatile long *)(base+0x470)
//                     );
    ::munmap(base, 1*1024);
    ::close(fd);
    return serialNo;
}

QByteArray DevicePrivate::get_version()
{
    QFile file("/etc/version");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    return file.readAll();
}

time_t DevicePrivate::get_time()
{
    time_t t = 0;
    FILE *fp = ::fopen(TIME_FILE, "r");
    if ( NULL == fp ) {
        qWarning()<<"Cann't open"<<TIME_FILE;
    } else {
        ::fscanf(fp, "%ld", &t);
        ::fclose(fp);
    }
    return t;
}


/********************* Device ***************************/
Device *Device::s_device = NULL;
QMutex Device::s_mutex;

Device *Device::get_device()
{
    QMutexLocker l(&s_mutex);
    if (s_device == NULL) {
        s_device = new Device();
    }
    return s_device;
}

const QString &Device::version() const
{
    return d->m_version;
}

Device::Type Device::type() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_type;
}

const QString &Device::type_string() const
{
    QReadLocker l(&d->m_rwlock);
    return s_typeMap[d->m_type];
}

const QString &Device::serial_number() const
{
    return d->m_serialNo;
}

uint Device::date_time() const
{
    QReadLocker l(&d->m_rwlock);
    return ::time(NULL) + d->m_time;
}

bool Device::set_date_time(uint t)
{
    QString cmd;
    QWriteLocker l(&d->m_rwlock);
    d->m_time = t - ::time(NULL);
    cmd.sprintf("echo %ld > %s && sync", d->m_time, TIME_FILE);
    if ( ::system(cmd.toUtf8().data()) ) {
        return false;
    }
    return true;
}

bool Device::import_cert(const QString &certFile)
{
    QString cmd;
    cmd.sprintf("cp %s %s && sync", certFile.toUtf8().data(), CERT_FILE);

    if (::system(cmd.toUtf8().data()) != 0) {
        return false;
    }

    QWriteLocker l(&d->m_rwlock);
    bool ret = d->m_cert.load(CERT_FILE, PUB_PEM_FILE);
    for (int i = 0; i < TYPE_MAX; ++i) {
        if (s_typeMap[i] == d->m_cert.get_device_type()) {
            d->m_type = (Device::Type)i;
        }
    }
    return ret;
}

const QString Device::cert_info() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_cert.info();
}

bool Device::is_valid() const
{
    if (d->m_cert.get_serial_number() != d->m_serialNo) {
        return false;
    }
    if (d->m_cert.get_auth_mode() == Cert::ALWAYS_VALID) {
        return true;
    } else if (d->m_cert.get_auth_mode() == Cert::VALID_DATE) {
        return (d->m_cert.get_expire() > ::time(NULL));
    }
    return false;
}

Device::Device()
    : d(new DevicePrivate())
{

}

Device::~Device()
{
    delete d;
}
