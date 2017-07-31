#include "color_bar.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QPainter>

ColorBar::ColorBar(QWidget *parent) : QWidget(parent)
{

}

void ColorBar::load_file(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
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

    update();
}

void ColorBar::read_special_colors(QXmlStreamReader &xml)
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

void ColorBar::read_main_colors(QXmlStreamReader &xml)
{
    for ( ;
          ! (xml.isEndElement() && xml.name() == "MainColors" );
          xml.readNext() ) {
        if ( xml.isStartElement() && xml.name() == "Color" ) {
            m_colorVector.append(QColorPointer(new QColor(
                                                   xml.attributes().value("R").toString().toInt(),
                                                   xml.attributes().value("G").toString().toInt(),
                                                   xml.attributes().value("B").toString().toInt(),
                                                   255 - xml.attributes().value("F").toString().toInt()
                                                   )));
        }
    }
}

void ColorBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QLinearGradient l(width()/2, 0, width()/2, height());
    float step = 1.0 / m_colorVector.size();

    for (int i = 0; i < m_colorVector.size(); ++i) {
        l.setColorAt(step*i, *(m_colorVector[i]));
    }

    QPainter painter(this);
    painter.setBrush(QBrush(l));
    painter.drawRect(rect());
}
