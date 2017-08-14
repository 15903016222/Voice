#include "device_p.h"

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
    m_cert(CERT_FILE, PUBPEM_FILE),
    m_paintThread(new PaintThread)
{
    init_paintThread();
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

QByteArray DevicePrivate::get_version()
{
    QFile file("/etc/version");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }

    return file.readAll();
}

time_t DevicePrivate::get_relative_time()
{
    QFile f(TIME_FILE);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }
    return f.readAll().toInt();
}

void DevicePrivate::init_paintThread()
{
    DplSource::Source *source = DplSource::Source::instance();
    connect(source, SIGNAL(data_event(const char*)),
            this, SLOT(do_data_event()));
    connect(m_paintThread, SIGNAL(started()),
            q_ptr, SIGNAL(start_paint_event()),
            Qt::DirectConnection);
    connect(m_paintThread, SIGNAL(finished()),
            q_ptr, SIGNAL(finish_paint_event()),
            Qt::QueuedConnection);
}

void DevicePrivate::do_data_event()
{
    if (!m_paintThread->isRunning()) {
        m_paintThread->start();
    }
}

}
