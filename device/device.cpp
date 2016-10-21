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
#include <fcntl.h>
#include <time.h>

#define MTD_DEVICE  "/dev/mtdblock2"

class DevicePrivate
{
public:
    DevicePrivate();

    QString get_serial_number();
    void save_run_count();

    bool read_old_info();
    bool read_info();

    bool mount() { return ! ::system("mount /dev/mtdblock2 /home/tt/.phascan"); }
    bool umount() { return ! ::system("umount /home/tt/.phascan"); }

    bool check_cert();

    static const QString s_typeMap[Device::DEV_TYPE_MAX];
    static const QString s_infoFile;
    static const char *s_runCountFile;
    static const char *s_timeFile;
    static const char *s_certFile;
    static const char *s_pubPemFile;

    QString m_serialNo;
    Device::Type m_type;
    int m_fpgaVersion;
    int m_runCount;
    time_t m_fstTime;

    time_t m_time;

    Cert m_cert;

    QReadWriteLock m_rwlock;
};

const char *DevicePrivate::s_pubPemFile = "/home/tt/.secure/pub.pem";
const char *DevicePrivate::s_certFile = "/home/tt/.phascan/auth.cert";
const char *DevicePrivate::s_timeFile = "/home/tt/.time";
const char *DevicePrivate::s_runCountFile = "/home/tt/.phascan/runcount.info";
const QString DevicePrivate::s_infoFile = "/home/tt/.phascan/dev.info";
const QString DevicePrivate::s_typeMap[Device::DEV_TYPE_MAX] = {
    QString("16-64-TOFD"),
    QString("32-64-TOFD"),
    QString("32-128-TOFD"),
    QString("32-128-PRO-TOFD")};

DevicePrivate::DevicePrivate()
{
    m_serialNo = get_serial_number();
    m_type = Device::DEV_16_64_TOFD;
    m_fpgaVersion = 1;
    m_runCount = 1;

    if (mount()) {
        read_info();
    } else {
        read_old_info();
    }
    m_cert.load(s_certFile, s_pubPemFile);
    umount();

    save_run_count();

    /* read time */
    FILE *fp = ::fopen(s_timeFile, "r");
    if ( NULL == fp ) {
        qWarning()<<"Cann't open"<<s_timeFile;
    } else {
        ::fscanf(fp, "%ld", &m_time);
        ::fclose(fp);
    }
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

void DevicePrivate::save_run_count()
{
    mount();

    FILE *fp = ::fopen(DevicePrivate::s_runCountFile, "r");
    if (fp) {
        ::fscanf(fp, "%d", &m_runCount);
        ::fclose(fp);
    }

    m_runCount += 1;
    QString cmd;
    cmd.sprintf("echo %d > %s", m_runCount, DevicePrivate::s_runCountFile);
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
        for (int i = 0; i < Device::DEV_TYPE_MAX; ++i) {
            if( ! (DevicePrivate::s_typeMap[i] == tmp) ) {
                m_type = (Device::Type)i;
            }
        }
    }
    ::close(mtd);

    m_fstTime = ::time(NULL);

    QString msg;
    msg.sprintf("<DevInfo><Type>%s</Type><FPGA>%d</FPGA><Time>%ld</Time></DevInfo>",
                                 DevicePrivate::s_typeMap[m_type].toUtf8().data(),
                                 m_fpgaVersion,
                                 m_fstTime
                                 );
    ::system("mkfs.ext2 "MTD_DEVICE);
    mount();
    QFile file(DevicePrivate::s_infoFile);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        qWarning()<<"Cann't Open"<<DevicePrivate::s_infoFile;
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
    QFile file(DevicePrivate::s_infoFile);
    if ( !file.open(QIODevice::ReadOnly|QIODevice::Text) ) {
        qWarning()<<__LINE__<<":Cann't open"<<DevicePrivate::s_infoFile;
        return false;
    }
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNextStartElement();
        if ( xml.name() == "Type" ) {
            QString type = xml.readElementText();
            for (int i = 0; i < Device::DEV_TYPE_MAX; ++i) {
                if ( DevicePrivate::s_typeMap[i] == type ) {
                    m_type = (Device::Type)i;
                }
            }
        } else if (xml.name() == "FPGA") {
            m_fpgaVersion = xml.readElementText().toInt();
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
        case Cert::RUN_COUNT:
            flag = (m_cert.get_expire() >= m_runCount);
            break;
        case Cert::RUN_TIME:
            flag = (m_cert.get_expire() >= (::time(NULL) - m_fstTime));
            break;
        case Cert::RUN_DATE:
            flag = (m_cert.get_expire() > ::time(NULL));
            break;
        default:
            break;
        }
    }
    return flag;
}

/* Device */
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

Device::Type Device::type() const
{
    return d->m_type;
}

const QString &Device::type_string() const
{
    return DevicePrivate::s_typeMap[d->m_type];
}

const QString &Device::serial_number() const
{
    return d->m_serialNo;
}

int Device::fpga_version() const
{
    return d->m_fpgaVersion;
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
    cmd.sprintf("echo %ld > %s && sync", d->m_time, DevicePrivate::s_timeFile);
    if ( ::system(cmd.toUtf8().data()) ) {
        return false;
    }
    return true;
}

bool Device::import_cert(const QString &certFile)
{
    QString cmd;
    cmd.sprintf("cp %s %s && sync", certFile.toUtf8().data(), DevicePrivate::s_certFile);

    d->mount();
    if (::system(cmd.toUtf8().data()) != 0) {
        d->umount();
        return false;
    }

    QWriteLocker l(&d->m_rwlock);
    bool ret = d->m_cert.load(DevicePrivate::s_certFile, DevicePrivate::s_pubPemFile);
    d->umount();
    return ret;
}

const QString &Device::cert_mode_string() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_cert.get_auth_mode_string();
}

const QString Device::cert_expire() const
{
    QReadLocker l(&d->m_rwlock);
    switch (d->m_cert.get_auth_mode()) {
    case Cert::RUN_COUNT:
    case Cert::RUN_TIME:
        return QString::number(d->m_cert.get_expire());
        break;
    case Cert::RUN_DATE:
        return QDateTime::fromTime_t(d->m_cert.get_expire()).toString("yyyy-M-d H:m");
    case Cert::ALWAYS_VALID:
        return "Always Valid";
    default:
        break;
    }
    return "Invalid";
}

bool Device::is_valid() const
{
    return d->check_cert();
}
