/**
 * @file device_phascan.cpp
 * @brief Device for Phascan
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-07
 */
#include "device.h"
#include "cert.h"

#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QReadWriteLock>
#include <QDebug>

/* unix */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

namespace DplDevice {

#define MTD_DEVICE  "/dev/mtdblock2"

static const char *CERT_FILE = "/home/tt/.phascan/auth.cert";
static const char *PUB_PEM_FILE = "/home/tt/.secure/pub.pem";
static const char *TIME_FILE = "/home/tt/.time";
static const char *RUN_COUNT_FILE = "/home/tt/.phascan/runcount.info";
static const char *INFO_FILE = "/home/tt/.phascan/dev.info";

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
    explicit DevicePrivate();
    ~DevicePrivate();

    bool mount() { return ! ::system("mount /dev/mtdblock2 /home/tt/.phascan"); }
    bool umount() { return ! ::system("umount /home/tt/.phascan"); }

    bool check_cert();

    QString m_serialNo;
    QString m_version;
    Device::Type m_type;
    int m_runCount;
    time_t m_fstTime;

    time_t m_time;

    Cert m_cert;

    QReadWriteLock m_rwlock;

private:
    QString get_serial_number();
    QByteArray get_version();

    bool read_old_info();
    bool read_info();

    void save_run_count();
};


DevicePrivate::DevicePrivate()
{
    m_serialNo = get_serial_number();
    m_version = get_version();
    m_type = Device::DEV_16_64_TOFD;
    m_runCount = 1;

    if (mount()) {
        read_info();
    } else {
        read_old_info();
    }
    m_cert.load(CERT_FILE, PUB_PEM_FILE);
    umount();

    save_run_count();

    /* read time */
    FILE *fp = ::fopen(TIME_FILE, "r");
    if ( NULL == fp ) {
        qWarning()<<"Cann't open"<<TIME_FILE;
    } else {
        ::fscanf(fp, "%ld", &m_time);
        ::fclose(fp);
    }
}

DevicePrivate::~DevicePrivate()
{
}

QString DevicePrivate::get_serial_number()
{
    QString serialNo;
    int fd = ::open("/dev/mem", O_RDWR | O_NDELAY);
    unsigned char *base = NULL;

    if ( fd < 0) {
        perror ("/dev/mem");
        return serialNo;
    }

    base = (unsigned char *)
        ::mmap (NULL,  4*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x4830a000);

    if (base == MAP_FAILED) {
        ::close(fd);
        return serialNo;
    }

    serialNo.sprintf("%08lx-%08lx-%08lx-%08lx",
                           *(volatile long *)(base+0x224),
                           *(volatile long *)(base+0x220),
                           *(volatile long *)(base+0x21c),
                           *(volatile long *)(base+0x218));
    ::munmap(base, 4*1024);
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

void DevicePrivate::save_run_count()
{
    mount();

    FILE *fp = ::fopen(RUN_COUNT_FILE, "r");
    if (fp) {
        ::fscanf(fp, "%d", &m_runCount);
        ::fclose(fp);
    }

    m_runCount += 1;
    QString cmd;
    cmd.sprintf("echo %d > %s", m_runCount, RUN_COUNT_FILE);
    ::system(cmd.toUtf8().data());

    umount();
}

bool DevicePrivate::read_old_info()
{
    char buf[100] = {0};
    int mtd = ::open(MTD_DEVICE, O_RDWR | O_SYNC);

    if (mtd < 0) {
        return false;
    }

    if ( ::read(mtd , buf , 30) != -1 ) {
        QString tmp(buf);
        for (int i = 0; i < TYPE_MAX; ++i) {
            if( ! (s_typeMap[i] == tmp) ) {
                m_type = (Device::Type)i;
            }
        }
    }
    ::close(mtd);

    m_fstTime = ::time(NULL);

    QString msg;
    msg.sprintf("<DevInfo><Type>%s</Type><Time>%ld</Time></DevInfo>",
                                 s_typeMap[m_type].toUtf8().data(),
                                 m_fstTime
                                 );
    ::system("mkfs.ext2 " MTD_DEVICE);
    mount();
    QFile file(INFO_FILE);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        qWarning()<<"Cann't Open"<<INFO_FILE;
        return false;
    }
    QTextStream out(&file);
    out<<msg;
    out.flush();
    file.close();

    return true;
}

bool DevicePrivate::read_info()
{
    QFile file(INFO_FILE);
    if ( !file.open(QIODevice::ReadOnly|QIODevice::Text) ) {
        qWarning()<<__LINE__<<":Cann't open"<<INFO_FILE;
        return false;
    }
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNextStartElement();
        if ( xml.name() == "Type" ) {
            QString type = xml.readElementText();
            for (int i = 0; i < TYPE_MAX; ++i) {
                if ( s_typeMap[i] == type ) {
                    m_type = (Device::Type)i;
                }
            }
        } else if (xml.name() == "Time") {
            m_fstTime = xml.readElementText().toInt();
        }
    }
    return !xml.hasError();
}

bool DevicePrivate::check_cert()
{
    bool flag = false;
    if (m_cert.get_serial_number() == m_serialNo) {
        switch (m_cert.get_auth_mode()) {
        case Cert::ALWAYS_VALID:
            flag = true;
            break;
        case Cert::VALID_COUNT:
            flag = (m_cert.get_expire() >= m_runCount);
            break;
        case Cert::VALID_TIME:
            flag = (m_cert.get_expire() >= (::time(NULL) - m_fstTime));
            break;
        case Cert::VALID_DATE:
            flag = (m_cert.get_expire() > ::time(NULL));
            break;
        default:
            break;
        }
    }
    return flag;
}

/********************* Device ********************/
Device::Device()
    : d(new DevicePrivate())
{

}

Device::~Device()
{
    delete d;
}

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
    return d->m_type;
}

const QString &Device::type_string() const
{
    return s_typeMap[d->m_type];
}

const QString &Device::serial_number() const
{
    return d->m_serialNo;
}

int Device::run_count() const
{
    return d->m_runCount;
}

uint Device::run_time() const
{
    return (::time(NULL) - d->m_fstTime);
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

    d->mount();
    if (::system(cmd.toUtf8().data()) != 0) {
        d->umount();
        return false;
    }

    QWriteLocker l(&d->m_rwlock);
    bool ret = d->m_cert.load(CERT_FILE, PUB_PEM_FILE);
    d->umount();
    return ret;
}

const QString Device::cert_info() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_cert.info();
}

bool Device::is_valid() const
{
    return d->check_cert();
}

}
