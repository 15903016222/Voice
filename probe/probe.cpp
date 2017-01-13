#include "probe.h"

#include <QFileInfo>
#include <QDebug>

namespace DplProbe {

struct ProbeData
{
    /*PA 时候先读走4个字节*/
    qint16  res0;
    quint8  paType;         /* 探头类型: 1,是Custom; 3,是angle beam; 5,是 Contact; 6,是Immersion */
    qint8   res1;
    quint8  utProbeType;	/* 探头类型 1 n/a 0 converntional */
    qint8	res2;
    char	model[20];		/* 探头型号 */
    char	serial[20];		/* 探头系列 */
    quint8  elemQty;		/* 阵元数 */
    quint8	freq2;			/* UT 时候 频率是 (freq2 << 8) + elem_qty */
    quint32	pitch;			/* 阵元中心间距 0.001mm 为单位 范围是0.01~65.00mm UT 是Elemet_size */
    quint32	res3;
    quint16 res4;
    quint16	freq;           /* 频率 */
    qint32	res5[75];
    qint32  res6;
    qint16  res7;
    quint16	refPoint;       /* 参考点 */
    quint32	res8[36];
};

void Probe::update_pa(const QByteArray &bytes)
{
    const ProbeData *data = (ProbeData *)(bytes.constData());
    m_type = static_cast<Probe::Type>(data->paType);
    m_model = data->model;
    m_serial = data->serial;
    m_elemQty = data->elemQty;
    m_pitch = data->pitch;
    m_freq = data->freq;
    m_refPoint = data->refPoint;
}

void Probe::update_ut(const QByteArray &bytes)
{
    const ProbeData *data = (ProbeData *)(bytes.constData());

    if (data->utProbeType == 1) {
        m_type = Probe::CONVENTION;
    } else {
        m_type = Probe::UNKNOWN;
    }
    m_model = data->model;
    m_serial = data->serial;
    m_freq = data->elemQty | (data->freq2<<8);
    m_elemSize = data->pitch;

    m_elemQty = 1;
    m_refPoint = 0;
}

Probe::Probe(QObject *parent) :
    QObject(parent)
{
    m_type = UNKNOWN;
}

Probe::~Probe()
{
}

bool Probe::load(const QString &fileName)
{
    QFileInfo info(fileName);
    QFile file(fileName);

    if (! file.open(QIODevice::ReadOnly)) {
        return false;
    }

    if (info.suffix() == "opp") {
        file.seek(4);
        update_pa(file.readAll());
    } else if (info.suffix() == "oup") {
        update_ut(file.readAll());
    } else {
        return false;
    }

    return TRUE ;
}

bool Probe::save(const QString &fileName)
{
    QFile file(fileName);
    QFileInfo info(fileName);
    ProbeData data;
    int seek = 0;

    ::memset(&data, 0, sizeof(data));

    ::strncpy(data.serial, m_serial.toUtf8().data(), 20);
    ::strncpy(data.model, m_model.toUtf8().data(), 20);

    if (info.suffix() == "oup") {
        data.utProbeType = 1;
        data.elemQty = m_freq & 0xff;
        data.freq2 = m_freq >> 8;
        data.pitch = m_elemSize;
    } else if (info.suffix() == "opp") {
        data.paType = m_type;
        data.elemQty = m_elemQty;
        data.pitch = m_pitch;
        data.freq = m_freq;
        data.refPoint = m_refPoint;

        seek = 4;
    } else {
        return false;
    }

    if (! file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.seek(seek);
    file.write((char *)&data, sizeof(ProbeData));

    return true;
}

const QString Probe::show() const
{
    QString msg;
    if (m_type == CONVENTION) {
        msg = "Type\t: Convention";
        msg += "\nModel\t: ";
        msg += m_model;
        msg += "\nSerial\t: ";
        msg += m_serial;
        msg += "\nFreq\t: ";
        msg += QString::number(m_freq/1000.0)+" MHz";
        msg += "\nSize\t: ";
        msg += QString::number(m_elemSize/1000.0, 'f', 2) + " mm";
        msg += "\n";
    } else {
        msg = "Type\t: ";
        switch (m_type) {
        case CUSTOM:
            msg += "Custom";
            break;
        case ANGLE_BEAM:
            msg += "Angle Beam";
            break;
        case CONTACT:
            msg += "Contact";
            break;
        case IMMERSION:
            msg += "Immersion";
            break;
        default:
            msg += "Unkown";
            break;
        }
        msg += "\nModel\t: ";
        msg += m_model;
        msg += "\nSerial\t: ";
        msg += m_serial;
        msg += "\nElemQty\t: ";
        msg += QString::number(m_elemQty);
        msg += "\nFreq\t: ";
        msg += QString::number(m_freq/1000.0, 'f', 2) + " MHz";
        msg += "\nPitch\t: ";
        msg += QString::number(m_pitch/1000.0, 'f', 2) + " mm";
        msg += "\nRefPoint\t: ";
        msg += QString::number(m_refPoint/1000.0, 'f', 2) + " mm";
        msg += "\n";
    }
    return msg;
}

}
