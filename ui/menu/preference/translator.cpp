#include "translator.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

namespace DplTranslator {

Translator *Translator::s_instance = NULL;

static const QString g_englishFilePath = "/opt/mercury/translator/phascanII_UI_English.qm";
static const QString g_chineseFilePath = "/opt/mercury/translator/phascanII_UI_Chinese.qm";

Translator::Translator(QObject *parent)
    : QObject(parent),
    m_translator(NULL)
{

}

Translator *Translator::instance()
{
    if(NULL == s_instance) {
        s_instance = new Translator;
    }
    return s_instance;
}


void Translator::do_value_changed(int val)
{
    if(NULL == m_translator) {
        m_translator = new QTranslator;
    }

    switch(val) {
        case English:
        {
            QApplication::removeTranslator(m_translator);
            bool ret = m_translator->load(g_englishFilePath);
            if(ret) {
                QApplication::installTranslator(m_translator);
                emit retranslateUi();
            }
            break;
        }
        case Chinese:
        {
            QApplication::removeTranslator(m_translator);
            bool ret = m_translator->load(g_chineseFilePath);
            if(ret) {
                QApplication::installTranslator(m_translator);
                emit retranslateUi();
            }
            break;
        }
    }
}

}
