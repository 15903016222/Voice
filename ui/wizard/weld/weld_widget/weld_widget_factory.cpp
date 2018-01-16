#include "weld_widget_factory.h"

#include "base_weld_information.h"
#include "base_weld_widget.h"

#include "i_weld_widget.h"
#include "v_weld_widget.h"
#include "vv_weld_widget.h"
#include "vy_weld_widget.h"
#include "u_weld_widget.h"
#include "uu_weld_widget.h"
#include "uv_weld_widget.h"
#include "tky_weld_widget.h"

namespace DplWeld {


WeldWidgetFactory::WeldWidgetFactory()
{

}

DplWeld::BaseWeldWidget* WeldWidgetFactory::create_weld_widget(QSharedPointer<BaseWeldInformation> &weldInfo)
{
    switch (weldInfo->get_type())
    {
        case I:
        {
            return new IWeldWidget(weldInfo);
            break;
        }
        case V:
        {
            return new VWeldWidget(weldInfo);
            break;
        }
        case U:
        {
            return new UWeldWidget(weldInfo);
            break;
        }
        case VY:
        {
            return new VYWeldWidget(weldInfo);
            break;
        }
        case VV:
        {
            return new VVWeldWidget(weldInfo);
            break;
        }
        case UU:
        {
            return new UUWeldWidget(weldInfo);
            break;
        }
        case UV:
        {
            return new UVWeldWidget(weldInfo);
            break;
        }
        case TKY:
        {
            return new TKYWeldWidget(weldInfo);
            break;
        }
    default:
        break;
    }

    return NULL;
}

}

