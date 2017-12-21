#include "i_weld_information.h"
#include <QDebug>

namespace DplWeld {

IWeldInformation::IWeldInformation(const QMap<QString, double> &valueList):BaseWeldInformation(valueList)
{
}

double IWeldInformation::get_W1()
{
    return m_dataMap.value(TAG_W1);
}

IWeldInformation::~IWeldInformation()
{
}

}

