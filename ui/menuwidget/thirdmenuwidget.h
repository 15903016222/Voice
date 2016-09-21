#ifndef THIRDMENUWIDGET_H
#define THIRDMENUWIDGET_H

#include "firstsecondmenuwidget.h"

#include <QWidget>
#include <QStandardItemModel>

#define THIRD_MENU_NUMBER 6

namespace Ui {
    class ThirdMenuWidget;
}

class ThirdMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThirdMenuWidget(QWidget *parent = 0);
    ~ThirdMenuWidget();

private:
    Ui::ThirdMenuWidget *ui;


public:
    void reTranslatorThirdMenuUi();
    void initStandardModel();
    void setThirdMenuName(int i, int j);
    void widgetStyleChoice(int k);
    void resizeEvent(QResizeEvent *event);
    void set_model_item(int startIndex, int count);
//    bool get_json_document_type(QString string, QJsonObject jsonObject);
//    QVariantHash read_json_file(QString string);
//    QJsonObject get_json_object(QString string);
//    QJsonObject get_subsidiary_object(QString string, QJsonObject jsonObject);
//    QJsonArray get_subsidiary_array(QString string, QJsonObject jsonObject);
    QStringList get_third_menu_list();
    QVariantMap read_json_file(QString string);
    QVariantMap get_sub_menu_map(QVariantMap variantMap, QString thirdMenuString, QString subString);
    QList<int> get_spinBox_range_list(QVariantMap variantMap);
    QStringList get_spinBox_step_list(QVariantMap variantMap, QString thirdMenuString);
    QList<QStringList> get_comboBox_option_list(QVariantMap variantMap, QString thirdMenuString);
    QString set_long_contents_header(int index, QString string);
    void cache_menu_data();

    int width;
    int height;
    int currFirstNum;
    int currSecondNum;

    QStandardItemModel *model;
//    QVariantHash thirdMenuHash;
//    QVariantHash fourthMenuHash;
    FirstSecondMenuWidget *widget;
//    QJsonObject jsonObjectOne;
//    QJsonObject jsonObjectTwo;
    QVariantMap thirdMenuMap;
    QVariantMap fourthMenuMap;
    QVariantMap menuCacheMap;
    QString firstMenuString;
    QString secondMenuString;
    QString relatedMenuString;
    int measurementIndex;

private:

public slots:

private slots:
    void onHeaderClicked(int index);
    void change_related_third_menu_data(QString string);
    void set_header_text_create(QStringList stringList) const ;
    void set_header_text_close(QWidget *editor) ;
    void on_tableView_clicked(const QModelIndex &index);
    void change_measurement_label(QString string);
};

#endif // THIRDMENUWIDGET_H
