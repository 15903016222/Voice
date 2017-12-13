#ifndef __DPL_WELD_VV_WELD_INFORMATION_H__
#define __DPL_WELD_VV_WELD_INFORMATION_H__

#include "v_weld_information.h"

namespace DplWeld {


class VVWeldInformation : public VWeldInformation
{
public:
    VVWeldInformation(const QMap<QString, double> &valueList);

    double get_W3();
    double get_H2();
};

}

#endif // __DPL_WELD_VV_WELD_INFORMATION_H__
