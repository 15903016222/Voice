#include "vv_weld_information.h"

namespace DplWeld {


VVWeldInformation::VVWeldInformation(const QMap<QString, double> &valueList) : VWeldInformation(valueList)
{

}


double VVWeldInformation::get_W3()
{
    return m_dataMap.value(TAG_W3);
}


double VVWeldInformation::get_H2()
{
    return m_dataMap.value(TAG_H2);
}

}
