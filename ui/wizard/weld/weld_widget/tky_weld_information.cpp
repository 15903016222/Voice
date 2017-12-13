#include "tky_weld_information.h"

namespace DplWeld {


TKYWeldInformation::TKYWeldInformation(const QMap<QString, double> &valueList) : BaseWeldInformation(valueList)
{

}

double TKYWeldInformation::get_X1()
{
    return m_dataMap.value(TAG_X1);
}


double TKYWeldInformation::get_Y1()
{
    return m_dataMap.value(TAG_Y1);
}


double TKYWeldInformation::get_X2()
{
    return m_dataMap.value(TAG_X2);
}


double TKYWeldInformation::get_Y2()
{
    return m_dataMap.value(TAG_Y2);
}


double TKYWeldInformation::get_T1()
{
    return m_dataMap.value(TAG_T1);
}


double TKYWeldInformation::get_T2()
{
    return m_dataMap.value(TAG_T2);
}


double TKYWeldInformation::get_angle()
{
    return m_dataMap.value(TAG_ANGLE);
}

}
