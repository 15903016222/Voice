/**
 * @file device.cpp
 * @brief Device
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */

#include "fpga/fpga.h"

#ifdef PHASCAN
#include "device_phascan.h"
#elif PHASCAN_II
#include "device_phascan_ii.h"
#else
#include ""
#endif

#include <QFile>
#include <QReadWriteLock>
#include <QDebug>
#include <source/source.h>

namespace DplDevice {

static const int MAX_GROUPS_NUM = 8;

Device *Device::s_device = NULL;
QMutex Device::s_mutex;

#if defined(PHASCAN) || defined(PHASCAN_II) || defined(PC_UNIX)
static const char *CERT_FILE = "~/.mercury/cert";
static const char *PUB_PEM_FILE = "~/.mercury/pem";
static const char *TIME_FILE = "~/.mercury/time";
#elif defined(PC_WIN)
static const char *CERT_FILE = "~/.mercury/cert";
static const char *PUB_PEM_FILE = "~/.mercury/pem";
static const char *TIME_FILE = "~/.mercury/time";
#else
#error("Not Specfied Device")
#endif

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

    DplFpga::Fpga *m_fpga;
    DplSource::Source *m_source;

    QReadWriteLock m_rwlock;

    QString m_version;
    time_t m_time;
    Cert m_cert;
    Device::Type m_type;

    /* Group */
    QList<GroupPointer> m_groups;
    GroupPointer m_curGroup;
    QReadWriteLock m_groupsRWLock;
private:
    QByteArray get_version();
    time_t get_time();
};

DevicePrivate::DevicePrivate()
{
    m_version = get_version();
    m_time = get_time();
    m_cert.load(CERT_FILE, PUB_PEM_FILE);

    m_fpga = DplFpga::Fpga::get_instance();
    m_source = DplSource::Source::get_instance();
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

QByteArray DevicePrivate::get_version()
{
    QFile file("/etc/version");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    return file.readAll();
}

/* Device */

Device *Device::get_instance()
{
    QMutexLocker l(&s_mutex);
    if (s_device == NULL) {
#ifdef PHASCAN
        s_device = new DevicePhascan();
#elif PHASCAN_II
        s_device = new DevicePhascanII();
#else
#error "Not specified device"
#endif
    }

    return s_device;
}

const QString &Device::version() const
{
    return d->m_version;
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

const Cert &Device::get_cert() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_cert;
}

Device::Type Device::type() const
{
    QReadLocker l(&d->m_rwlock);
    return d->m_type;
}

const QString &Device::type_string()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_cert.get_device_type();
}

int Device::groups()
{
    QReadLocker l(&d->m_groupsRWLock);
    return d->m_groups.size();
}

bool Device::add_group()
{
    QWriteLocker l(&d->m_groupsRWLock);
    if (d->m_groups.size() >= MAX_GROUPS_NUM) {
        return false;
    }
    d->m_groups.append(GroupPointer(new Group(d->m_groups.size())));
    d->m_curGroup = d->m_groups.last();
    d->m_source->add_group(d->m_curGroup->beam_qty(), d->m_curGroup->point_qty());

    DplSource::GroupPointer groupSource = d->m_source->get_group(d->m_curGroup->index());

    /* connect */
    connect(static_cast<DplDevice::Group *>(d->m_curGroup.data()),
            SIGNAL(point_qty_changed(int)),
            static_cast<DplSource::Group *>(groupSource.data()),
            SLOT(set_point_qty(int)));
    connect(static_cast<DplDevice::Group *>(d->m_curGroup.data()),
            SIGNAL(point_qty_changed(int)),
            d->m_source,
            SLOT(restart()));

    emit current_group_changed();
    return true;
}

bool Device::remove_group(int id)
{
    QWriteLocker l(&d->m_groupsRWLock);
    if (d->m_groups.isEmpty()
            || id >= d->m_groups.size()) {
        return false;
    }

    /* disconnect */
    disconnect(static_cast<DplDevice::Group *>(d->m_groups.at(id).data()),
               SIGNAL(point_qty_changed(int)),
               static_cast<DplSource::Group *>(d->m_source->get_group(id).data()),
               SLOT(set_point_qty(int)));
    disconnect(static_cast<DplDevice::Group *>(d->m_groups.at(id).data()),
               SIGNAL(point_qty_changed(int)),
               d->m_source,
               SLOT(restart()));

    d->m_groups.removeAt(id);
    d->m_source->remove_group(id);
    if (d->m_curGroup->index() == id) {
        d->m_curGroup = d->m_groups.last();
        emit current_group_changed();
    }
    return true;
}

GroupPointer &Device::get_group(int index)
{
    QReadLocker l(&d->m_groupsRWLock);
    return d->m_groups[index];
}

bool Device::set_current_group(int index)
{
    QWriteLocker l(&d->m_groupsRWLock);
    if (index >= d->m_groups.size()
            || index == d->m_curGroup->index()) {
        return false;
    }
    d->m_curGroup = d->m_groups[index];
    emit current_group_changed();
    return true;
}

GroupPointer &Device::current_group()
{
    QReadLocker l(&d->m_groupsRWLock);
    return d->m_curGroup;
}

int Device::beam_qty()
{
    QReadLocker l(&d->m_groupsRWLock);
    int qty = 0;
    for (int i = 0; i < d->m_groups.size(); ++i) {
        qty += d->m_groups[i]->beam_qty();
    }
    return qty;
}

Device::Device(QObject *parent) :
    QObject(parent),
    d(new DevicePrivate())
{

}

Device::~Device()
{
    delete d;
}


}
