#include "u_weld_information.h"

namespace DplWeld {

UWeldInformation::UWeldInformation(const QMap<QString, double> &valueList) : VWeldInformation(valueList)
{

}

double UWeldInformation::get_R1()
{
    return m_dataMap.value(TAG_R1);
}

}
