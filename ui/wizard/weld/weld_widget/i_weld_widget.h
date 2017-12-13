#ifndef __DPL_WELD_I_WELD_WIDGET_H__
#define __DPL_WELD_I_WELD_WIDGET_H__

#include "base_weld_widget.h"

namespace DplWeld {

class WELDWIDGETSHARED_EXPORT IWeldWidget : public BaseWeldWidget
{
public:
    IWeldWidget(QSharedPointer<BaseWeldInformation> &weldInfo);
    ~IWeldWidget();

protected:
    void paint();
    void paint_symbol();

};

}


#endif // __DPL_WELD_I_WELD_WIDGET_H__
