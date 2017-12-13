#ifndef __DPL_WELD_VY_WELD_INFORMATION_H__
#define __DPL_WELD_VY_WELD_INFORMATION_H__

#include "vv_weld_information.h"

namespace DplWeld {

class VYWeldInformation : public VVWeldInformation
{
public:
    VYWeldInformation(const QMap<QString, double> &valueList);
};

}

#endif // __DPL_WELD_VY_WELD_INFORMATION_H__
