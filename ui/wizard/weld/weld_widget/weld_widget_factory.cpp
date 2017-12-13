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
        case I_Weld:
        {
            return new IWeldWidget(weldInfo);
            break;
        }
        case V_Weld:
        {
            return new VWeldWidget(weldInfo);
            break;
        }
        case U_Weld:
        {
            return new UWeldWidget(weldInfo);
            break;
        }
        case VY_Weld:
        {
            return new VYWeldWidget(weldInfo);
            break;
        }
        case VV_Weld:
        {
            return new VVWeldWidget(weldInfo);
            break;
        }
        case UU_Weld:
        {
            return new UUWeldWidget(weldInfo);
            break;
        }
        case UV_Weld:
        {
            return new UVWeldWidget(weldInfo);
            break;
        }
        case TKY_Weld:
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

