#include "palette_color.h"

#include <QFile>
#include <QXmlStreamReader>

namespace DplDisplay {

PaletteColor::PaletteColor(QObject *parent) :
    QObject(parent)
{
}

bool PaletteColor::load(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    m_colorVector.clear();

    QXmlStreamReader xml(&file);

    while (!xml.atEnd()) {
        xml.readNext();
        if ( ! xml.isStartElement() ) {
            continue;
        } else if (xml.name() == "MainColors") {
            read_main_colors(xml);
        } else if (xml.name() == "SpecialColors") {
            read_special_colors(xml);
        }
    }
    emit changed();
    return true;
}

void PaletteColor::read_special_colors(QXmlStreamReader &xml)
{
    for ( ;
          ! (xml.isEndElement() && xml.name() == "SpecialColors");
          xml.readNext() ) {
//        qDebug("%s[%d]: name(%s) flag(%d)",__func__, __LINE__,
//               xml.name().toUtf8().data(), xml.isStartElement());
//        if ( xml.isStartElement() && xml.name() == "Color" ) {
//            qDebug("%s[%d]: RGBA(%d, %d, %d, %d)",__func__, __LINE__,
//                   xml.attributes().value("R").toString().toInt(),
//                   xml.attributes().value("G").toString().toInt(),
//                   xml.attributes().value("B").toString().toInt(),
//                   xml.attributes().value("F").toString().toInt());
//        }
    }
}

void PaletteColor::read_main_colors(QXmlStreamReader &xml)
{
    for ( ;
          ! (xml.isEndElement() && xml.name() == "MainColors" );
          xml.readNext() ) {
        if ( xml.isStartElement() && xml.name() == "Color" ) {
            m_colorVector.append(qRgb(
                                     xml.attributes().value("R").toString().toInt(),
                                     xml.attributes().value("G").toString().toInt(),
                                     xml.attributes().value("B").toString().toInt()
                                     ));
        }
    }
}

}
