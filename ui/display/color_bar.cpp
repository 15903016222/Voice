#include "color_bar.h"
#include <QFile>
#include <QXmlStreamReader>

ColorBar::ColorBar(QWidget *parent) : QWidget(parent)
{

}

void ColorBar::load_file(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
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
}

void ColorBar::read_special_colors(QXmlStreamReader &xml)
{
    while ( ! (xml.isEndElement()
               && xml.name() == "SpecialColors") ) {
        xml.readNext();
        if ( xml.isStartElement() && xml.name() == "Color" ) {
            qDebug("%s[%d]: RGBA(%d, %d, %d, %d)",__func__, __LINE__,
                   xml.attributes().value("R").toString().toInt(),
                   xml.attributes().value("G").toString().toInt(),
                   xml.attributes().value("B").toString().toInt(),
                   xml.attributes().value("F").toString().toInt());
        } else {
            qDebug("%s[%d]: RGBA(12, 34, 56, 0)",__func__, __LINE__);
        }
    }
}

void ColorBar::read_main_colors(QXmlStreamReader &xml)
{

}

void ColorBar::paintEvent(QPaintEvent *e)
{

}
