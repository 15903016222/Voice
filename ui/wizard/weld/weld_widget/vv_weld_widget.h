#ifndef __DPL_WELD_VV_WELD_WIDGET_H__
#define __DPL_WELD_VV_WELD_WIDGET_H__

#include "base_weld_widget.h"

namespace DplWeld {

class VVWeldWidget : public BaseWeldWidget
{
public:
    VVWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo);

protected:
    void paint();
    void paint_symbol();
};

}

#endif // __DPL_WELD_VV_WELD_WIDGET_H__
