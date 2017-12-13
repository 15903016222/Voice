#ifndef __DPL_WELD_UU_WELD_INFORMATION_H__
#define __DPL_WELD_UU_WELD_INFORMATION_H__

#include "u_weld_information.h"

namespace DplWeld {

class UUWeldInformation : public UWeldInformation
{
public:
    UUWeldInformation(const QMap<QString, double> &valueList);

    double get_W3();
    double get_R2();
    double get_H2();
};

}

#endif // __DPL_WELD_UU_WELD_INFORMATION_H__
