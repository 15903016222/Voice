#include "probe.h"

#include <global.h>
#include <QSettings>
#include <QDebug>

namespace DplProbe {

Probe::Probe(QObject *parent) :
    QObject(parent),
    m_type(ANGLE_BEAM),
    m_freq(0.0)
{
}

Probe::~Probe()
{
}

bool Probe::load(const QString &fileName)
{
    QSettings s(fileName, QSettings::IniFormat);
    if (s.status() != QSettings::NoError) {
        return false;
    }

    QVariant value;

    m_serial    = s.value("Serial").toString();
    m_model     = s.value("Model").toString();

    value = s.value("Type");
    if (!value.isNull()) {
        m_type  = static_cast<Type>(value.toInt());
    }

    m_freq      = s.value("Freq").toInt()/1000.0;
    m_elemElevation = Dpl::um_to_mm(s.value("Element_Elevation").toDouble());

    return true;
}

bool Probe::save(const QString &fileName)
{
    QSettings s(fileName, QSettings::IniFormat);
    if (s.status() != QSettings::NoError) {
        return false;
    }

    s.setValue("Serial", m_serial);
    s.setValue("Model", m_model);
    s.setValue("Type", m_type);
    s.setValue("Freq", static_cast<int>(m_freq*1000));
    s.setValue("Element_Elevation", static_cast<int>(m_elemElevation*1000));

    s.sync();
    return true;
}

}
