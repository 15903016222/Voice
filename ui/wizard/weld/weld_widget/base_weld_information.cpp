#include "base_weld_information.h"

#include <QString>
#include <QMap>
#include <QDebug>

namespace DplWeld {

static const QString I_IMG_PATH("./img/IWeld.png");
static const QString V_IMG_PATH("./img/VWeld.png");
static const QString U_IMG_PATH("./img/UWeld.png");
static const QString VY_IMG_PATH("./img/VYWeld.png");
static const QString VV_IMG_PATH("./img/VVWeld.png");
static const QString UU_IMG_PATH("./img/UUWeld.png");
static const QString UV_IMG_PATH("./img/UVWeld.png");
static const QString TKY_IMG_PATH("./img/TKYWeld.png");

BaseWeldInformation::BaseWeldInformation(const QMap<QString, double> &valueList):
    m_dataMap(valueList)
{
    m_pixMap.insert(I, I_IMG_PATH);
    m_pixMap.insert(V, V_IMG_PATH);
    m_pixMap.insert(U, U_IMG_PATH);
    m_pixMap.insert(VY, VY_IMG_PATH);
    m_pixMap.insert(VV, VV_IMG_PATH);
    m_pixMap.insert(UU, UU_IMG_PATH);
    m_pixMap.insert(UV, UV_IMG_PATH);
    m_pixMap.insert(TKY, TKY_IMG_PATH);
}


BaseWeldInformation::~BaseWeldInformation()
{
}


bool BaseWeldInformation::insert_value(const QString &tag, double value)
{
    if(tag.isEmpty()) {
        return false;
    }

    m_dataMap.insert(tag, value);
    return true;
}


bool BaseWeldInformation::insert_value_list(const QMap<QString, double> &valueList)
{
    QMap<QString, double>::const_iterator it = valueList.begin();

    while(it != valueList.end()) {
        m_dataMap.insert(it.key(), it.value());
        ++it;
    }

    return true;
}

void BaseWeldInformation::get_value_list(QMap<QString, double> &valueList)
{
    valueList = m_dataMap;
}

int BaseWeldInformation::get_type()
{
    return m_dataMap.value(TAG_TYPE);
}

double BaseWeldInformation::get_height_scale()
{
    return m_dataMap.value(TAG_HEIGHT_SCALE);
}

double BaseWeldInformation::get_width_scale()
{
    return m_dataMap.value(TAG_WIDTH_SCALE);
}

void BaseWeldInformation::get_pic_path(QString &path)
{
    path = m_pixMap.value((WeldType)m_dataMap.value(TAG_TYPE));
}

double BaseWeldInformation::get_thickness()
{
    return m_dataMap.value(TAG_THICKNESS);
}

}
