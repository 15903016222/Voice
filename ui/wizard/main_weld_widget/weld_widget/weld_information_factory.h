#ifndef __DPL_WELD_WELD_INFORMATION_FACTORY_H__
#define __DPL_WELD_WELD_INFORMATION_FACTORY_H__

#include <QMap>
#include <QString>
#include <QSharedPointer>

namespace DplWeld {


class BaseWeldInformation;

class WeldInformationFactory
{
public:
    WeldInformationFactory();

    static QSharedPointer<DplWeld::BaseWeldInformation> create_weld_information(int type, const QMap<QString, double> &valueList);

};

}

#endif // __DPL_WELD_WELD_INFORMATION_FACTORY_H__
