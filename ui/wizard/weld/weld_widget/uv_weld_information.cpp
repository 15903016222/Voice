#include "uv_weld_information.h"

namespace DplWeld {

UVWeldInformation::UVWeldInformation(const QMap<QString, double> &valueList) : UWeldInformation(valueList)
{

}
double UVWeldInformation::get_H2()
{
    return m_dataMap.value(TAG_H2);
}

double UVWeldInformation::get_W3()
{
    return m_dataMap.value(TAG_W3);
}

}
