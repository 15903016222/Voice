#include "device_p.h"

#include <global.h>

#include <QFile>

namespace DplDevice {

static const char *CERT_FILE = "/opt/mercury/info/cert";
static const char *PUBPEM_FILE = "/opt/mercury/info/pub.pem";
static const char *TIME_FILE = "/opt/mercury/info/time";

static const int TYPE_MAX = Device::DEV_32_128_PR_TOFD+1;
static const QString s_typeMap[TYPE_MAX] = {
    QString("16-64-TOFD"),
    QString("32-64-TOFD"),
    QString("32-128-TOFD"),
    QString("32-128-PR-TOFD")
};

DevicePrivate::DevicePrivate(Device *parent) :
    QObject(),
    q_ptr(parent),
    m_serialNo(get_serial_number()),
    m_version(get_version()),
    m_time(get_relative_time()),
    m_cert(CERT_FILE, PUBPEM_FILE)
{
    DplSource::Scan *scan = DplSource::Scan::instance();
    DplSource::Encoder *encX = scan->encoder_x().data();
    DplSource::Encoder *encY = scan->encoder_y().data();

    connect(encX, SIGNAL(enabled_changed(bool)),
            this, SLOT(do_encX_enabled_changed(bool)));
    connect(encX, SIGNAL(mode_changed(DplSource::Encoder::Mode)),
            this, SLOT(do_encX_mode_changed(DplSource::Encoder::Mode)));
    connect(encX, SIGNAL(polarity_changed(DplSource::Encoder::Polarity)),
            this, SLOT(do_encX_polarity_changed(DplSource::Encoder::Polarity)));
    connect(encY, SIGNAL(enabled_changed(bool)),
            this, SLOT(do_encY_enabled_changed(bool)));
    connect(encY, SIGNAL(mode_changed(DplSource::Encoder::Mode)),
            this, SLOT(do_encY_mode_changed(DplSource::Encoder::Mode)));
}

DevicePrivate::~DevicePrivate()
{
}

bool DevicePrivate::set_relative_time(time_t t)
{
    m_time = t;
    QFile f(TIME_FILE);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }
    f.write(QString::number(t).toUtf8());
    return true;
}

bool DevicePrivate::import_cert(const QString &certFile)
{
    if (!QFile::copy(certFile, CERT_FILE)) {
        return false;
    }
    if (!m_cert.load(CERT_FILE, PUBPEM_FILE)) {
        return false;
    }
    for (int i = 0; i < TYPE_MAX; ++i) {
        if (s_typeMap[i] == m_cert.get_device_type()) {
            m_type = (Device::Type)i;
        }
    }
    return true;
}

bool DevicePrivate::is_valid() const
{
    bool flag = false;
    if (m_cert.get_serial_number() == m_serialNo) {
        switch (m_cert.get_auth_mode()) {
        case Cert::ALWAYS_VALID:
            flag = true;
            break;
        case Cert::VALID_DATE:
            flag = QDateTime::fromTime_t(m_cert.get_expire()) > QDateTime::currentDateTime();
            break;
        default:
            break;
        }
    }
    return flag;
}

int DevicePrivate::total_beam_qty() const
{
    int qty = 0;
    foreach (GroupPointer grp, m_groups) {
        if (grp->mode() == Group::PA) {
            qty += grp->focallawer()->beam_qty();
        } else {
            qty += 1;
        }
    }
    return qty;
}

quint32 DevicePrivate::max_txrx_time() const
{
    quint32 max = 1;
    foreach (GroupPointer grp, m_groups) {
        if (max < grp->txrx_time()) {
            max = grp->txrx_time();
        }
    }
    return max;
}

int DevicePrivate::max_acquisition_rate() const
{
    double prfLimit[3] = {0.0};
    int beamQty = total_beam_qty();
    int totalDataSize = DplSource::Source::instance()->beams_size();

    // the rx_time used to calculate PRF is the max rx_time of each group
    // then the idel_time will be 3*max_rx_time minus current group rx_time
    //single_beam_time = 4 * max_rx_time;
    prfLimit[0] = (Dpl::s_to_ns(1.0)/4) / (max_txrx_time() * beamQty );
    double power = 0.0;
    double elementPower = 0.0;
    double totalElementPower = 0.0;

    foreach (GroupPointer grp, m_groups) {
        if (grp->focallawer()->probe()->is_pa()) {
            DplFocallaw::PaProbePointer probe = grp->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
            power = grp->pulser()->pw() * qPow(grp->pulser()->voltage(true), 2) / DplFocallaw::PaProbe::RESISTANCE;
            elementPower += grp->focallawer()->beam_qty() * power;
            totalElementPower += probe->scan_configure()->aperture() * elementPower;
        }
    }

    if(qFuzzyIsNull(elementPower)) {
        prfLimit[1]  =  6000;
    } else {
        prfLimit[1]  =  (pa_max_power() * Dpl::s_to_ns(1.0) / 4) / elementPower;
    }

    if(qFuzzyIsNull(totalElementPower)) {
        prfLimit[2]  =  6000;
     }else {
        prfLimit[2]  =  2*1000*1000*1000 / totalElementPower;
    }

    double result = prfLimit[0];
    for(int i = 1 ; i < 3 ; i ++) {
        if(result > prfLimit[i]) {
            result = prfLimit[i] ;
        }
    }

    // total prf limit
    if(result * beamQty > 20000) {
        result = 20000 / beamQty;
    }

    // total data size limit
    if(result * totalDataSize > 8 *1024 * 1024) {
        result = 8 * 1024 * 1024 / totalDataSize;
    }

    // max interrupt limit
    if(result > 6000) {
        result = 6000 ;
    }

    return  (result)<1 ? 1: result;
}

QString DevicePrivate::get_version()
{
    QFile file("/etc/version");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    return QString(file.readAll()).remove('\n');
}

time_t DevicePrivate::get_relative_time()
{
    QFile f(TIME_FILE);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }
    return f.readAll().toInt();
}

void DevicePrivate::do_encX_enabled_changed(bool enable)
{
    if (!enable) {
        DplFpga::Fpga::instance()->set_encoder_x_mode(DplFpga::Fpga::OFF);
    } else {
        do_encX_mode_changed(DplSource::Scan::instance()->encoder_x()->mode());
    }
}

void DevicePrivate::do_encX_mode_changed(DplSource::Encoder::Mode mode)
{
    if(!DplSource::Scan::instance()->encoder_x()->is_enabled()) {
        return;
    }

    switch (mode) {
    case DplSource::Encoder::UP:
        DplFpga::Fpga::instance()->set_encoder_x_mode(DplFpga::Fpga::UP);
        break;
    case DplSource::Encoder::DOWN:
        DplFpga::Fpga::instance()->set_encoder_x_mode(DplFpga::Fpga::DOWN);
        break;
    case DplSource::Encoder::QUAD:
        DplFpga::Fpga::instance()->set_encoder_x_mode(DplFpga::Fpga::QUAD);
        break;
    default:
        break;
    }
}

void DevicePrivate::do_encX_polarity_changed(DplSource::Encoder::Polarity polarity)
{
    DplFpga::Fpga::instance()->set_encoder_x_polarity(static_cast<DplFpga::Fpga::EncoderPolarity>(polarity));
}

void DevicePrivate::do_encY_enabled_changed(bool enable)
{
    if (!enable) {
        DplFpga::Fpga::instance()->set_encoder_y_mode(DplFpga::Fpga::OFF);
    } else {
        do_encY_mode_changed(DplSource::Scan::instance()->encoder_y()->mode());
    }
}

void DevicePrivate::do_encY_mode_changed(DplSource::Encoder::Mode mode)
{
    if (! DplSource::Scan::instance()->encoder_y()->is_enabled()) {
        return;
    }

    switch (mode) {
    case DplSource::Encoder::UP:
        DplFpga::Fpga::instance()->set_encoder_y_mode(DplFpga::Fpga::UP);
        break;
    case DplSource::Encoder::DOWN:
        DplFpga::Fpga::instance()->set_encoder_y_mode(DplFpga::Fpga::DOWN);
        break;
    case DplSource::Encoder::QUAD:
        DplFpga::Fpga::instance()->set_encoder_y_mode(DplFpga::Fpga::QUAD);
        break;
    default:
        break;
    }
}

void DevicePrivate::do_encY_polarity_changed(DplSource::Encoder::Polarity polarity)
{
    DplFpga::Fpga::instance()->set_encoder_y_polarity(static_cast<DplFpga::Fpga::EncoderPolarity>(polarity));
}

}
