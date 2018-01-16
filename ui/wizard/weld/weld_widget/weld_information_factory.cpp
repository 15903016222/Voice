#include "weld_information_factory.h"

#include <QDebug>

#include "base_weld_information.h"
#include "i_weld_information.h"
#include "v_weld_information.h"
#include "vv_weld_information.h"
#include "vy_weld_information.h"
#include "u_weld_information.h"
#include "uu_weld_information.h"
#include "uv_weld_information.h"
#include "tky_weld_information.h"

namespace DplWeld {

WeldInformationFactory::WeldInformationFactory()
{

}

QSharedPointer<DplWeld::BaseWeldInformation> WeldInformationFactory::create_weld_information(int type, const QMap<QString, double> &valueList)
{
    switch (type)
    {
        case DplWeld::I:
        {
            return QSharedPointer<BaseWeldInformation>(new IWeldInformation(valueList));
            break;
        }
        case DplWeld::V:
        {
            return QSharedPointer<BaseWeldInformation>(new VWeldInformation(valueList));
            break;
        }
        case DplWeld::U:
        {
            return QSharedPointer<BaseWeldInformation>(new UWeldInformation(valueList));
            break;
        }
        case DplWeld::VY:
        {
            return QSharedPointer<BaseWeldInformation>(new VYWeldInformation(valueList));
            break;
        }
        case DplWeld::VV:
        {
            return QSharedPointer<BaseWeldInformation>(new VVWeldInformation(valueList));
            break;
        }
        case DplWeld::UU:
        {
            return QSharedPointer<BaseWeldInformation>(new UUWeldInformation(valueList));
            break;
        }
        case DplWeld::UV:
        {
            return QSharedPointer<BaseWeldInformation>(new UVWeldInformation(valueList));
            break;
        }
        case DplWeld::TKY:
        {
            return QSharedPointer<BaseWeldInformation>(new TKYWeldInformation(valueList));
            break;
        }

    default:
        break;
    }

    return QSharedPointer<BaseWeldInformation>();
}

}
