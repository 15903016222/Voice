#ifndef __DPL_WELD_BASE_WELD_INFORMATION_H__
#define __DPL_WELD_BASE_WELD_INFORMATION_H__

#include "weldwidget_global.h"

#include <QMap>

#include "global_property_tag.h"


namespace DplWeld {

enum WeldType
{
    I,
    V,
    U,
    VY,
    VV,
    UU,
    UV,
    TKY
};

enum E_ShowScale
{
    TopScale    = 20,
    WeldScale   = 60,
    BottomScale = 20
};

enum E_TKYShowScale
{
    TKYTopScale     = 10,
    TKYBottomScale  = 10,
    TKYLeftScale    = 10,
    TKYRightScale   = 10
};


class WELDWIDGETSHARED_EXPORT BaseWeldInformation
{

public:

    BaseWeldInformation(const QMap<QString, double> &valueList);
    ~BaseWeldInformation();

    bool insert_value(const QString &tag, double value);
    bool insert_value_list(const QMap<QString, double> &valueList);
    void get_value_list(QMap<QString, double> &valueList);

    int    get_type();
    double get_height_scale();
    double get_width_scale();
    void   get_pic_path(QString &path);
    double get_thickness();

protected:

    QMap<QString, double>   m_dataMap;
    QMap<WeldType, QString> m_pixMap;

};

}

#endif // __DPL_WELD_BASE_WELD_INFORMATION_H__
