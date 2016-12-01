#include "menu_config.h"

#include <Parser>

#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>

MenuConfig::MenuConfig()
{
    m_languageOption = 1;
    m_language = "English";


    m_relatedMenuString = "";

    QFile *file = new QFile(":/file/json/menuconf.json");
    menuMap = read_json_file(file);
    qDebug() << menuMap;

}

MenuConfig::~MenuConfig()
{

}

QVariantMap MenuConfig::read_json_file(QFile *file)
{
    QJson::Parser parser;
    bool ok;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString str = file->readAll();
    QVariantMap variantMap = parser.parse(str.toUtf8(), &ok).toMap();
    if(!ok) {
//        QMessageBox::warning(this, tr("Parsing file Error"), tr("Read file failure!"));
    }
    file->close();

#if (PHASCAN | PHASCAN_II)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    setFont(QFont("utf8",14,QFont::Normal));
#endif

    return variantMap;
}

QStringList MenuConfig::get_fisrt_menu_list(QVariantMap variantMap)
{
    QStringList firstList;
    QVariantList variantList = variantMap.values("Queue_First_Menu");
    firstList = variantList.at(0).toStringList();
    qDebug() << "firstList" << firstList;
    return firstList;
}

QStringList MenuConfig::get_second_menu_list(QVariantMap variantMap, QString string)
{
    QVariantMap firstMap = get_first_menu_map(variantMap, string);
    QVariantList variantList = firstMap.values("Queue_Second_Menu");
    QStringList secondList  = variantList.at(0).toStringList();
    qDebug() << "secondList" << secondList;
    return secondList;
}

QStringList MenuConfig::get_third_menu_list(QVariantMap variantMap,QString firstString, QString secondString)
{
    QVariantList variantList;
    QStringList thirdList;
    QVariantMap secondMap = get_second_menu_map(variantMap, firstString, secondString);
    QVariantMap map = secondMap["Queue_Third_Menu"].toMap();

    if(map.isEmpty()) {
        variantList = secondMap.values("Queue_Third_Menu");
    } else {
        QString string = map.value("first third_menu").toString();
        QVariantMap firstThirdMenuMap = secondMap[string].toMap();
        QStringList otherThirdMenuList = get_comboBox_option_list(firstThirdMenuMap);
        if(m_relatedMenuString == NULL || !otherThirdMenuList.contains(m_relatedMenuString)) {
            variantList = map.values(otherThirdMenuList.at(0));
        } else {
            variantList = map.values(m_relatedMenuString);
        }
    }

    thirdList = variantList.at(0).toStringList();
    qDebug() << "thirdList" << thirdList;
    return thirdList;
}

QVariantMap MenuConfig::get_first_menu_map(QVariantMap variantMap, QString string)
{
    QVariantMap firstMap = variantMap[string].toMap();
    return firstMap;
}

QVariantMap MenuConfig::get_second_menu_map(QVariantMap variantMap, QString firstString, QString secondString)
{
    QVariantMap firstMap = get_first_menu_map(variantMap, firstString);
    QVariantMap secondMap = firstMap[secondString].toMap();
    return secondMap;
}

QVariantMap MenuConfig::get_third_menu_map(QVariantMap variantMap, QString firstString, QString secondString, QString thirdString)
{
    QVariantMap secondMap = get_second_menu_map(variantMap, firstString, secondString);
    QVariantMap thirdMap = secondMap[thirdString].toMap();
    return thirdMap;
}

QList<double> MenuConfig::get_spinBox_range_list(QVariantMap variantMap)
{
    double minimum = variantMap["minimum"].toInt();
    double maximum = variantMap["maximum"].toInt();
    QList<double> rangeList;
    rangeList.append(minimum);
    rangeList.append(maximum);
    qDebug() << "rangeList" << rangeList;
    return rangeList;
}

QList<double> MenuConfig::get_spinBox_step_list(QVariantMap variantMap)
{   
    QStringList stringList;
    QList<double> stepList;
    QVariantList tmpList = variantMap.values("steps");

    if(tmpList.size() != 0) {
        stringList = tmpList.at(0).toStringList();
    } else {
        stringList.append("");
    }

    for(int i = 0; i < stringList.count(); i ++) {
        QString string = stringList.at(i);
        stepList.append(string.toDouble());
    }
    qDebug() << "stepList" << stepList;
    return stepList;
}

int MenuConfig::get_style(QVariantMap variantMap)
{
    return variantMap["style"].toInt();
}

int MenuConfig::get_spinBox_decimal(QVariantMap variantMap)
{
    return variantMap["decimal"].toInt();
}

QString MenuConfig::get_spinBox_unit(QVariantMap variantMap)
{
    return variantMap["unit"].toString();
}

QStringList MenuConfig::get_comboBox_option_list(QVariantMap variantMap)
{
    QStringList optionList;
    QVariantList tmpList = variantMap["options"].toList();

    for(int index = 0; index < tmpList.count(); index ++) {
        optionList.append(tmpList.at(index).toStringList());
    }
    return optionList;
}

QStringList MenuConfig::get_related_third_menu(QVariantMap variantMap, QString string)
{
    QString str;
    QVariantMap queueMap = variantMap["Queue_Third_Menu"].toMap();

    if(!queueMap.isEmpty()  & queueMap.contains("first third_menu")) {
        if(m_languageOption == 1) {
            if(queueMap.contains(string)) {
                str = string;
            }
        } else if(m_languageOption == 2) {
//             QqueueMap tranMap = get_translate_option_map(queueMap.value("first third_menu").toString());
//             QqueueMap optionMap = tranMap["options"].toMap();
//             str = optionMap.key(string);
        }
//        m_relatedMenuString = string;
        QVariantList variantList = queueMap.values(str);
        QStringList thirdStringList = variantList.at(0).toStringList();

//        set_model_item(1, thirdStringList);
        return thirdStringList;
    }

}


void MenuConfig::set_related_menu_string(QString string)
{
    m_relatedMenuString = string;
}
