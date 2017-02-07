#include "pa_probe.h"

#include <global.h>
#include <QFileInfo>
#include <QSettings>

#include <QDebug>

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

    QVariant value = s.value("Array_Type");
    if (!value.isNull()) {
        m_arrayType = static_cast<ArrayType>(value.toInt());
    }

    m_priElemQty    = s.value("Principal_Axis_Element_Qty").toInt();

    value = s.value("Secondary_Axis_Element_Qty");
    if (! value.isNull()) {
        m_secElemQty = value.toInt();
    }

    m_priPitch      = Dpl::um_to_mm(s.value("Principal_Axis_Pitch").toDouble());

    value = s.value("Secondary_Axis_Pitch");
    if (! value.isNull()) {
         m_secPitch      = Dpl::um_to_mm(value.toDouble());
    }

    return true;
}

}
