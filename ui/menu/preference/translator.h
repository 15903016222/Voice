#ifndef __DPL_TRANSLATOR_H__
#define __DPL_TRANSLATOR_H__

#include <QObject>

class QTranslator;

namespace DplTranslator {

enum E_LanguageType {
    English,
    Chinese
};

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QObject *parent = 0);
    static Translator *instance();

signals:
    void retranslateUi();

public slots:
    void do_value_changed(int val);

private:
    static Translator  *s_instance;
    QTranslator         *m_translator;

};

}

#endif // __TRANSLATOR_H__
