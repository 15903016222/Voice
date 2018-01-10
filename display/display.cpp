#include "display.h"
#include <QApplication>
#include <QTranslator>
#include <global.h>

namespace DplDisplay {

Display::Display(QObject *parent) :
    QObject(parent),
    m_layout(A),
    m_grps(1, 0),
    m_ascan(new Ascan()),
    m_palette(new PaletteColor())
{
    m_palette->load("/opt/mercury/palette/ONDT_Amplitude.pal");
}

void Display::set_language(Display::Language lang)
{
    if (m_language == lang) {
        return;
    }
    m_language = lang;

    static QTranslator translator;
    QApplication::removeTranslator(&translator);

    if (!translator.load(language_string(), LANGUAGE_PATH)) {
        return;
    }
    QApplication::installTranslator(&translator);
}

QString Display::language_string() const
{
    if (ENGLISH == m_language) {
        return "English";
    } else if (CHINESE == m_language) {
        return "Chinese";
    } else if (RUSSIAN == m_language) {
        return "Russian";
    } else if (GERMAN == m_language) {
        return "German";
    } else if (JAPANESE == m_language) {
        return "Japanese";
    } else {
        return "";
    }
}

}
