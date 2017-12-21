#include "v_weld_information.h"

namespace DplWeld {


VWeldInformation::VWeldInformation(const QMap<QString, double> &valueList) : IWeldInformation(valueList)
{

}

double VWeldInformation::get_W2()
{
    return m_dataMap.value(TAG_W2);
}


double VWeldInformation::get_H1()
{
    return m_dataMap.value(TAG_H1);
}

}
