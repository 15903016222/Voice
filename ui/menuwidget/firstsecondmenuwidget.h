#ifndef FIRSTSECONDMENUWIDGET_H
#define FIRSTSECONDMENUWIDGET_H

#include <QWidget>
#include <QToolBox>
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>

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

private:
    Ui::FirstSecondMenuWidget *ui;

public:
    QList<QToolBox*> toolBox;
    QList<QListView*> menuList;
    QList<QStandardItemModel*> modelList;
    QStandardItemModel *standardItemModel;

    void initUI();
    void reTranslatorFirstSecondMenuUi();
    void setSecondMenuName(int i);
    void initSecondMenuItem(int i);
    void secondMenuItemClicked(int i, QModelIndex index);

private:

private slots:

public slots:

};

#endif // FIRSTSECONDMENUWIDGET_H
