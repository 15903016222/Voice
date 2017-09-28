/**
 * @file device.cpp
 * @brief Device
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-10-21
 */

#include "device_p.h"

#include <global.h>

namespace DplDevice {

static const int MAX_GROUPS_NUM = 8;

Device *Device::instance()
{
    static Device *s_device = new Device();
    return s_device;
}

const QString &Device::version() const
{
    Q_D(const Device);
    return d->version();
}

uint Device::date_time() const
{
    Q_D(const Device);
    return ::time(NULL) + d->relative_time();
}

bool Device::set_date_time(uint t)
{
    Q_D(Device);
    return d->set_relative_time(t - ::time(NULL));
}

bool Device::import_cert(const QString &certFile)
{
    Q_D(Device);
    return d->import_cert(certFile);
}

const Cert &Device::get_cert() const
{
    Q_D(const Device);
    return d->cert();
}

Device::Type Device::type() const
{
    Q_D(const Device);
    return d->type();
}

const QString &Device::type_string() const
{
    Q_D(const Device);
    return d->cert().get_device_type();
}

const QString &Device::serial_number() const
{
    Q_D(const Device);
    return d->serial_number();
}

bool Device::is_valid() const
{
    Q_D(const Device);
    return d->is_valid();
}

int Device::groups()
{
    Q_D(Device);
    return d->m_groups.size();
}

bool Device::add_group()
{
    Q_D(Device);

    if (d->m_groups.size() >= MAX_GROUPS_NUM) {
        return false;
    }

    d->m_groups.append(GroupPointer(new Group(d_ptr->m_groups.size())));
    d->m_curGroup = d_ptr->m_groups.last();

    connect(static_cast<DplFocallaw::Focallawer *>(d->m_curGroup->focallawer().data()),
            SIGNAL(focallawed()),
            this, SLOT(deploy_beams()));
    connect(static_cast<DplFocallaw::Probe *>(d->m_curGroup->focallawer()->probe().data()),
            SIGNAL(pulser_index_changed(uint)),
            this, SLOT(deploy_beams()));
    connect(static_cast<DplFocallaw::Probe *>(d->m_curGroup->focallawer()->probe().data()),
            SIGNAL(receiver_index_changed(uint)),
            this, SLOT(deploy_beams()));

    deploy_beams();

    emit current_group_changed(d->m_curGroup);
    return true;
}

bool Device::remove_group(int id)
{
    Q_D(Device);

    if (d->m_groups.isEmpty()
            || id >= d->m_groups.size()) {
        return false;
    }

    d->m_groups.remove(id);

    if (d->m_curGroup->index() != id) {
        return true;
    }

    d->m_curGroup = d->m_groups.last();
    emit current_group_changed(d->m_curGroup);

    return true;
}

int Device::group_qty() const
{
    Q_D(const Device);
    return d->m_groups.size();
}

const GroupPointer &Device::get_group(int index) const
{
    Q_D(const Device);
    return d->m_groups[index];
}

bool Device::set_current_group(int index)
{
    Q_D(Device);

    if (index >= d->m_groups.size()
            || index == d->m_curGroup->index()) {
        return false;
    }
    d->m_curGroup = d->m_groups[index];

    emit current_group_changed(d->m_curGroup);
    return true;
}

const GroupPointer &Device::current_group() const
{
    Q_D(const Device);
    return d->m_curGroup;
}

int Device::first_beam_index(const Group *grp) const
{
    Q_D(const Device);

    int index = 0;
    for (int i = 0; i < grp->index(); ++i) {
        index += d->m_groups[i]->focallawer()->beam_qty();
    }

    return index;
}

int Device::total_beam_qty() const
{
    Q_D(const Device);

    return d->total_beam_qty();
}

int Device::acquisition_rate() const
{
    Q_D(const Device);
    int rate = d->max_acquisition_rate();
    switch(DplUt::Pulser::prf_mode()) {
    case DplUt::Pulser::MAX_HALF:
        if (rate > 1) {
            rate /= 2;
        }
        break;
    case DplUt::Pulser::OPTIMUM:
        if (rate > 60) {
            rate = 60;
        }
        break;
    case DplUt::Pulser::USER_DEF:
        rate = d->acquisition_rate();
        break;
    default:
        rate = 1;
        break;
    }
    return rate;
}

bool Device::set_acquisition_rate(uint val)
{
    Q_D(Device);
    if (DplUt::Pulser::prf_mode() != DplUt::Pulser::USER_DEF) {
        return false;
    }
    d->set_acquisition_rate(val);
    return true;
}

float Device::beam_cycle() const
{
    Q_D(const Device);
    return Dpl::s_to_ns(1.0)/(d->total_beam_qty() * d->max_acquisition_rate()) - DplFpga::Fpga::LOADING_TIME * DplFpga::Fpga::SAMPLE_PRECISION;
}

void Device::start()
{
    DplSource::Source::instance()->start();
    DplFpga::Fpga::instance()->set_freeze(false);
}

void Device::stop()
{
//    DplSource::Source::instance()->stop();
    DplFpga::Fpga::instance()->set_freeze(true);
}

bool Device::is_running() const
{
    return !DplFpga::Fpga::instance()->is_freeze();
}

void Device::deploy_beams()
{
    Q_D(Device);

    DplFpga::Fpga::instance()->set_pa_law_qty(total_beam_qty());
    DplFpga::Fpga::instance()->set_ut_law_qty(total_beam_qty());

    foreach (GroupPointer grp, d->m_groups) {
        grp->deploy_beams();
    }
}

Device::Device(QObject *parent) :
    QObject(parent),
    d_ptr(new DevicePrivate(this)),
    m_display(new DplDisplay::Display())
{
}

Device::~Device()
{
    delete d_ptr;
}

}
