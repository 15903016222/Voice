#ifndef MENU_CONFIG_H__
#define MENU_CONFIG_H__

#include <QObject>
#include <QFile>
#include <QVariantMap>

class MenuConfig : public QObject
{
    Q_OBJECT

public:
    explicit MenuConfig();
    ~MenuConfig();

    QList<double> get_spinBox_range_list(QVariantMap variantMap);
    QList<double> get_spinBox_step_list(QVariantMap variantMap);
    int get_spinBox_decimal(QVariantMap variantMap);
    int get_style(QVariantMap variantMap);
    QString get_spinBox_unit(QVariantMap variantMap);
    QStringList get_comboBox_option_list(QVariantMap variantMap);
    QStringList get_related_third_menu(QVariantMap variantMap, QString string);

    QStringList get_fisrt_menu_list(QVariantMap variantMap);
    QStringList get_second_menu_list(QVariantMap variantMap, QString string);
    QStringList get_third_menu_list(QVariantMap variantMap, QString firstString, QString secondString);

    QVariantMap get_first_menu_map(QVariantMap variantMap, QString string);
    QVariantMap get_second_menu_map(QVariantMap variantMap, QString firstString, QString secondString);
    QVariantMap get_third_menu_map(QVariantMap variantMap, QString firstString, QString secondString, QString thirdString);
    QVariantMap read_json_file(QFile *file);

    void set_related_menu_string(QString string);

    QVariantMap menuMap;
    QString m_relatedMenuString;


private:

//    QStringList get_translate_third_menu_list();

//    QList<QStringList> get_translate_comboBox_option_list(QVariantMap variantMapEng, QVariantMap variantMapTran);
//    QStringList get_abbreviate_comboBox_option_list(QStringList stringList);
//    QVariantMap get_translate_option_map(QString thirdMenuString);
//    QStringList get_third_menu_list();

    int m_currFirstNum;
    int m_currSecondNum;
    int m_languageOption;
    QString m_language;
    QVariantMap m_secondMenuMap;
    QString m_firstMenuString;
    QString m_secondMenuString;

signals:
//    void retranslate_ui(QString);
//    void translater_ZH();
//    void translater_EN();

};

#endif // MENU_CONFIG_H
