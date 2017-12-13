#ifndef __DPL_WELD_WELD_WIDGET_FACTORY_H__
#define __DPL_WELD_WELD_WIDGET_FACTORY_H__

#include <QSharedPointer>

namespace DplWeld {

class BaseWeldWidget;
class BaseWeldInformation;

class WeldWidgetFactory
{
public:
    WeldWidgetFactory();
    static DplWeld::BaseWeldWidget *create_weld_widget(QSharedPointer<BaseWeldInformation> &weldInfo);
};

}

#endif // __DPL_WELD_WELD_WIDGET_FACTORY_H__
