#include "uu_weld_information.h"

namespace DplWeld {

UUWeldInformation::UUWeldInformation(const QMap<QString, double> &valueList) : UWeldInformation(valueList)
{

}

double UUWeldInformation::get_W3()
{
    return m_dataMap.value(TAG_W3);
}


double UUWeldInformation::get_R2()
{
    return m_dataMap.value(TAG_R2);
}


double UUWeldInformation::get_H2()
{
    return m_dataMap.value(TAG_H2);
}

}
