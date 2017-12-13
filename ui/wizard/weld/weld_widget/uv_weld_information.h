#ifndef __DPL_WELD_UV_WELD_INFORMATION_H__
#define __DPL_WELD_UV_WELD_INFORMATION_H__

#include "u_weld_information.h"

namespace DplWeld {

class UVWeldInformation : public UWeldInformation
{
public:
    UVWeldInformation(const QMap<QString, double> &valueList);
    double get_H2();
    double get_W3();
};

}

#endif // __DPL_WELD_UV_WELD_INFORMATION_H__
