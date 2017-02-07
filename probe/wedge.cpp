#include "wedge.h"

#include <global.h>
#include <QSettings>

namespace DplProbe {

Wedge::Wedge(QObject *parent) :
    QObject(parent),
    m_angle(30),
    m_delay(0),
    m_waveType(Longitudinal),
    m_orientation(Normal),
    m_velocity(3240),
    m_primaryOffset(0.0),
    m_secondaryOffset(0.0),
    m_height(0.0),
    m_length(0.0),
    m_refPoint(0.0)
{
}

bool Wedge::load(const QString &fileName)
{
    QSettings s(fileName, QSettings::IniFormat);
    if (s.status() != QSettings::NoError) {
        return false;
    }

    m_serial            = s.value("Serial").toString();
    m_model             = s.value("Model").toString();
    m_angle             = s.value("Angle").toInt()/10.0;
    m_delay             = s.value("Delay").toInt();

    m_orientation       = static_cast<Orientation>(s.value("Orientation").toInt());
    m_velocity          = s.value("Velocity").toInt()/1000;
    m_primaryOffset     = Dpl::um_to_mm(s.value("Primary_Offset").toFloat());
    m_secondaryOffset   = Dpl::um_to_mm(s.value("Secondary_Offset").toFloat());
    m_height            = Dpl::um_to_mm(s.value("Height").toFloat());
    m_length            = Dpl::um_to_mm(s.value("Length").toFloat());

    m_waveType          = static_cast<WaveType>(s.value("Wave_Type").toInt());
    m_refPoint          = Dpl::um_to_mm(s.value("Ref_Point").toFloat());

    return true;
}

bool Wedge::save(const QString &fileName) const
{
    if (fileName.isEmpty()) {
        return false;
    }

    QSettings s(fileName, QSettings::IniFormat);

    s.setValue("Serial", m_serial);
    s.setValue("Model", m_model);

    s.setValue("Angle", static_cast<int>(m_angle*10));
    s.setValue("Delay", m_delay);

    s.setValue("Orientation", m_orientation);
    s.setValue("Velocity", m_velocity);
    s.setValue("Primary_Offset", static_cast<int>(Dpl::mm_to_um(m_primaryOffset)));
    s.setValue("Secondary_Offset", static_cast<int>(Dpl::mm_to_um(m_secondaryOffset)));
    s.setValue("Height", static_cast<int>(Dpl::mm_to_um(m_height)));
    s.setValue("Length", static_cast<int>(Dpl::mm_to_um(m_length)));

    s.setValue("Wave_Type", static_cast<int>(m_waveType*1000));
    s.setValue("Ref_Point", static_cast<int>(Dpl::mm_to_um(m_refPoint)));

    s.sync();

    return true;
}


}
