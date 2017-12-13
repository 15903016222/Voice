#ifndef __DPL_WELD_I_WELD_INFORMATION_H__
#define __DPL_WELD_I_WELD_INFORMATION_H__

#include "base_weld_information.h"

namespace DplWeld {

class IWeldInfoPrivate;

class IWeldInformation : public BaseWeldInformation
{
public:
    IWeldInformation(const QMap<QString, double> &valueList);
    ~IWeldInformation();

    double get_W1();

};

}

#endif // __DPL_WELD_I_WELD_INFORMATION_H__
