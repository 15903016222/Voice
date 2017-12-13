#ifndef __DPL_WELD_U_WELD_INFORMATION_H__
#define __DPL_WELD_U_WELD_INFORMATION_H__

#include "v_weld_information.h"

namespace DplWeld {

class UWeldInformation : public VWeldInformation
{
public:
    UWeldInformation(const QMap<QString, double> &valueList);

    double get_R1();
};

}

#endif // __DPL_WELD_U_WELD_INFORMATION_H__
