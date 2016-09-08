#ifndef THIRDMENUWIDGET_H
#define THIRDMENUWIDGET_H

#include "firstsecondmenuwidget.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QResizeEvent>
#include <QTableView>

#define THIRD_MENU_NUMBER 6
static QString WIDGET_CHOICE_CHAR[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER][THIRD_MENU_NUMBER]={
    {
        {"1", "1", "1", "1", "1", "2"},
        {"2", "1", "1", "1", "1"},
        {"1", "2", "2", "2", "2"},
        {"2", "2", "1", "1", "1"}
    }, //1
    {
        {"2", "1", "1", "1", "1", "1"},
        {"2", "2", "2", "2", "2", "2"},
        {"2", "2", "1", "1", "1", "2"},
        {"2"},
        {"2"}
    }, //2
    {
        {"2", "2", "2", "1", "1"},
        {"1", "1", "1"},
        {"2", "2", "2", "2"}
    }, //3
    {
        {"2", "2", "2", "2", "2", "2"},
        {"1", "1", "1"},
        {"1", "1", "1", "2"},
        {"2", "1", "1", "2", "2"},
        {"2", "2"}
    }, //4
    {
        {"2", "2", "2", "2"},
        {"1", "1", "1"},
        {"1", "1", "1", "1"},
        {"2"}
    }, //5
    {
        {"2", "2", "1", "1"},
        {"2", "2", "1", "2", "1", "2"},
        {"1", "1", "1", "1", "1", "1"},
        {"2", "2"}
    }, //6
    {
        {"2", "2", "2", "2", "2"},
        {"2"},
        {"2", "2", "2"},
        {"2", "2", "2", "2", "2"}
    }, //7
    {
        {"2", "2", "2"},
        {"2", "2", "2", "2"},
        {"2", "2", "1", "1", "1", "1"},
        {"2", "2", "2", "2", "2", "2"},
        {"2", "2", "1", "2", "2", "2"}
    }, //8
    {
        {"2", "1", "2"},
        {"2", "2", "3"},
        {"2", "2"},
        {"2", "2", "2", "2", "2", "1"}
    } //9
}; // widget类型 1 是Spin Box, 2 是Combo Box, 3 是Label 4是on/off Label

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
    void widgetStyleChoice(int i, int j, int k);
    void resizeEvent(QResizeEvent *event);

    bool get_json_document_type(QString string, QJsonObject jsonObject);
    bool eventFilter(QObject *object, QEvent *event);

//    QVariantHash read_json_file(QString string);
//    QJsonObject get_json_object(QString string);
//    QJsonObject get_subsidiary_object(QString string, QJsonObject jsonObject);
//    QJsonArray get_subsidiary_array(QString string, QJsonObject jsonObject);
    QStringList get_third_menu_list(int i, int j);
    QVariantMap read_json_file(QString string);
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

private:

public slots:

private slots:
    void on_tableView_clicked(const QModelIndex &index);
};

#endif // THIRDMENUWIDGET_H
