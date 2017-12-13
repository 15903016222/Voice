#ifndef __DPL_WELD_TKY_WELD_INFORMATION_H__
#define __DPL_WELD_TKY_WELD_INFORMATION_H__

#include "base_weld_information.h"

namespace DplWeld {


class TKYWeldInformation : public BaseWeldInformation
{
public:
    TKYWeldInformation(const QMap<QString, double> &valueList);

    double get_X1();
    double get_Y1();
    double get_X2();
    double get_Y2();
    double get_T1();
    double get_T2();
    double get_angle();
};

}

#endif // __DPL_WELD_TKY_WELD_INFORMATION_H__
