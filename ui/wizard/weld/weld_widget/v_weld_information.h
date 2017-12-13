#ifndef __DPL_WELD_V_WELD_INFORMATION_H__
#define __DPL_WELD_V_WELD_INFORMATION_H__

#include "i_weld_information.h"

namespace DplWeld {


class VWeldInformation : public IWeldInformation
{
public:
    VWeldInformation(const QMap<QString, double> &valueList);

    double get_W2();
    double get_H1();
};

}

#endif // __DPL_WELD_V_WELD_INFORMATION_H__
