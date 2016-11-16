#ifndef FIRSTSECONDMENUWIDGET_H
#define FIRSTSECONDMENUWIDGET_H

#include <Parser>

#include <QWidget>
#include <QToolBox>
#include <QListView>
#include <QStandardItemModel>
#include <QFile>

#define FIRST_MENU_NUMBER 9
#define SECOND_MENU_NUMBER 5

namespace Ui{
class FirstSecondMenuWidget;
}

class FirstSecondMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FirstSecondMenuWidget(QWidget *parent = 0);
    ~FirstSecondMenuWidget();

    QList<QToolBox*> toolBox;
    QList<QListView*> menuList;
    QList<QStandardItemModel*> modelList;
    QStringList firstMenuData;
    QVariantMap firstMenuMap;
    QVariantMap translateChineseMap;
    QVariantMap read_json_file(QFile *file);
    QStringList get_second_menu_list(int i);

    void resize_height(int i);
    void set_second_menu_item_style(int i, QModelIndex index);
    void retranslate_main_menu_ui(QString string);

private:
    Ui::FirstSecondMenuWidget *ui;

    void init_ui();
    void set_second_menu_name(int i);

    int m_languageOption;

};

#endif // FIRSTSECONDMENUWIDGET_H
