#include "pa_probe.h"

#include <global.h>
#include <QFileInfo>
#include <QSettings>

namespace DplProbe {

PaProbe::PaProbe(QObject *parent) :
    Probe(parent),
    m_arrayType(LINEAR),
    m_priElemQty(1),
    m_secElemQty(1),
    m_priPitch(1),
    m_secPitch(0),
    m_rxWave(Longitudinal),
    m_txWave(Longitudinal)
{

}

bool PaProbe::load(const QString &fileName)
{
    if (! Probe::load(fileName)) {
        return false;
    }

    QSettings s(fileName, QSettings::IniFormat);
    if (s.status() != QSettings::NoError) {
        return false;
    }

    m_arrayType     = static_cast<ArrayType>(s.value("Array_Type").toInt());
    m_priElemQty    = s.value("Principal_Axis_Element_Qty").toInt();
    m_secElemQty    = s.value("Secondary_Axis_Element_Qty").toInt();
    m_priPitch      = Dpl::um_to_mm(s.value("Principal_Axis_Pitch").toDouble());
    m_secPitch      = Dpl::um_to_mm(s.value("Secondary_Axis_Pitch").toDouble());

    return true;
}

}
