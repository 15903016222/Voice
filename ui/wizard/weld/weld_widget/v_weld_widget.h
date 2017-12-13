#ifndef __DPL_WELD_V_WELD_WIDGET_H__
#define __DPL_WELD_V_WELD_WIDGET_H__

#include "base_weld_widget.h"

namespace DplWeld {


class VWeldWidget : public BaseWeldWidget
{
public:
    VWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo);

protected:
    void paint();
    void paint_symbol();
};

}

#endif // __DPL_WELD_V_WELD_WIDGET_H__
