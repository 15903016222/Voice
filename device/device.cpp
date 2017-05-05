/**
 * @file device.cpp
 * @brief Device
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */

#include "device_p.h"

#include <QFile>
#include <QDebug>

namespace DplDevice {

static const int MAX_GROUPS_NUM = 8;

#if defined(PHASCAN) || defined(PHASCAN_II) || defined(PCUNIX)
static const char *CERT_FILE = "~/.mercury/cert";
static const char *PUB_PEM_FILE = "~/.mercury/pem";
static const char *TIME_FILE = "~/.mercury/time";
#elif defined(PCWIN)
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

DevicePrivate::DevicePrivate()
{
    m_serialNo = get_serial_number();
    m_version = get_version();
    m_time = get_time();
    m_cert.load(CERT_FILE, PUB_PEM_FILE);
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
Device *Device::instance()
{
    static Device *s_device = new Device();
    return s_device;
}

const QString &Device::version() const
{
    Q_D(const Device);
    return d->m_version;
}

uint Device::date_time() const
{
    Q_D(const Device);
    QReadLocker l(&d->m_rwlock);
    return ::time(NULL) + d->m_time;
}

bool Device::set_date_time(uint t)
{
    Q_D(Device);
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
    Q_D(Device);
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
    Q_D(const Device);
    QReadLocker l(&d->m_rwlock);
    return d->m_cert;
}

Device::Type Device::type() const
{
    Q_D(const Device);
    QReadLocker l(&d->m_rwlock);
    return d->m_type;
}

const QString &Device::type_string()
{
    Q_D(Device);
    QReadLocker l(&d->m_rwlock);
    return d->m_cert.get_device_type();
}

const QString &Device::serial_number() const
{
    Q_D(const Device);
    return d->m_serialNo;
}

bool Device::is_valid() const
{
    Q_D(const Device);
    QReadLocker l(&d->m_rwlock);
    bool flag = false;
    if (d->m_cert.get_serial_number() == d->m_serialNo) {
        switch (d->m_cert.get_auth_mode()) {
        case Cert::ALWAYS_VALID:
            flag = true;
            break;
        case Cert::VALID_DATE:
            flag = (d->m_cert.get_expire() > ::time(NULL));
            break;
        default:
            break;
        }
    }
    return flag;
}

int Device::groups()
{
    Q_D(Device);
    QReadLocker l(&d->m_groupsRWLock);
    return d->m_groups.size();
}

bool Device::add_group()
{
    Q_D(Device);
    {
        QWriteLocker l(&d->m_groupsRWLock);
        if (d->m_groups.size() >= MAX_GROUPS_NUM) {
            return false;
        }
        d->m_groups.append(GroupPointer(new Group(d_ptr->m_groups.size())));
        d->m_curGroup = d_ptr->m_groups.last();
    }
    connect(static_cast<DplFocallaw::Focallawer *>(d->m_curGroup->focallawer().data()),
            SIGNAL(focallawed()),
            this,
            SLOT(refresh_beams()));

    refresh_beams();

    emit current_group_changed();
    return true;
}

bool Device::remove_group(int id)
{
    Q_D(Device);
    {
        QWriteLocker l(&d->m_groupsRWLock);
        if (d->m_groups.isEmpty()
                || id >= d->m_groups.size()) {
            return false;
        }

        d->m_groups.removeAt(id);
        if (d->m_curGroup->index() != id) {
            return true;
        }
    }

    d->m_curGroup = d->m_groups.last();
    emit current_group_changed();

    return true;
}

const GroupPointer &Device::get_group(int index) const
{
    Q_D(const Device);
    QReadLocker l(&d->m_groupsRWLock);
    return d->m_groups[index];
}

bool Device::set_current_group(int index)
{
    Q_D(Device);
    {
        QWriteLocker l(&d->m_groupsRWLock);
        if (index >= d->m_groups.size()
                || index == d->m_curGroup->index()) {
            return false;
        }
        d->m_curGroup = d->m_groups[index];
    }
    emit current_group_changed();
    return true;
}

const GroupPointer &Device::current_group() const
{
    Q_D(const Device);
    QReadLocker l(&d->m_groupsRWLock);
    return d->m_curGroup;
}

int Device::total_beam_qty() const
{
    Q_D(const Device);
    QReadLocker l(&d_ptr->m_groupsRWLock);
    int qty = 0;
    for (int i = 0; i < d->m_groups.size(); ++i) {
        if (d->m_groups[i]->mode() == Group::PA) {
            qty += d->m_groups[i]->focallawer()->beam_qty();
        } else {
            qty += 1;
        }
    }
    return qty;
}

void Device::refresh_beams()
{
    Q_D(Device);
    uint qty = total_beam_qty();
    DplFpga::Beam fpgaBeam;

    DplFocallaw::FocallawerPointer focallawer;
    QList<DplFocallaw::BeamPointer> focallawerBeams;

    DplFpga::Fpga::instance()->set_pa_law_qty(qty);
    DplFpga::Fpga::instance()->set_ut_law_qty(qty);

    fpgaBeam.set_total_beam_qty(qty);

    int index = 0;
    int i,j,k;
    int aperture;
    int startRxChannel;
    int startTxChannel;

    for (i = 0; i < d->m_groups.size(); ++i) {
        focallawer = d->m_groups[i]->focallawer();
        focallawerBeams = focallawer->beams();
        fpgaBeam.set_group_id(i);
        fpgaBeam.set_gain_compensation(0);
        fpgaBeam.set_total_beam_qty(qty);

        d->m_groups[i]->show_info();

        for (j = 0; j < focallawer->beam_qty(); ++j) {
//            qDebug("%s[%d]: beamQty(%d) pointQty(%d)",__func__, __LINE__, focallawer->beam_qty(), d->m_groups[i]->point_qty());
            fpgaBeam.set_index(index);
//            fpgaBeam.set_delay(focallawerBeams[j]->delay()/DplFpga::Fpga::SAMPLE_PRECISION);
            fpgaBeam.set_delay(0);
            fpgaBeam.set_gate_a(0, 30);
            fpgaBeam.set_gate_b(0, 30);
            fpgaBeam.set_gate_i(0, 30);

            startRxChannel = focallawer->probe()->pulser_index() + focallawerBeams[j]->first_rx_element();
            startTxChannel = focallawer->probe()->receiver_index() + focallawerBeams[j]->first_tx_element();

            aperture = focallawerBeams[j]->aperture();

            fpgaBeam.set_tx_channel(startRxChannel, aperture);
            fpgaBeam.set_rx_channel(startTxChannel, aperture);

            for (k = 0; k < aperture; ++k) {
                fpgaBeam.set_rx_delay(startRxChannel+k, focallawerBeams[j]->rxdelay().at(k));
                fpgaBeam.set_tx_delay(startTxChannel+k, focallawerBeams[j]->txdelay().at(k));
//                fpgaBeam.set_rx_delay(startRxChannel+k, 0);
//                fpgaBeam.set_tx_delay(startTxChannel+k, 0);
                qDebug("%s[%d]: enablet(0x%x) rx(%f) tx(%f)",__func__, __LINE__, (startRxChannel+i)&0x1f, focallawerBeams[j]->rxdelay().at(k), focallawerBeams[j]->txdelay().at(k));
            }

            fpgaBeam.refresh();

            ++index;
        }
    }
}

Device::Device(QObject *parent) :
    QObject(parent),
    d_ptr(new DevicePrivate())
{
    DplFpga::Fpga::instance()->show_info();
    add_group();
}

Device::~Device()
{
    delete d_ptr;
}


}
