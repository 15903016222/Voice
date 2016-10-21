#include "device.h"

#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
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

    static const QString s_typeMap[Device::DEV_TYPE_MAX];
    static const QString s_infoFile;
    static const char *s_runCountFile;
    QString m_serialNo;
    Device::Type m_type;
    int m_fpgaVersion;
    int m_runCount;
    time_t m_fstTime;
};

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
    umount();

    save_run_count();

    //load_cert();
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
