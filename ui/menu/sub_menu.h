#ifndef SUB_MENU_H
#define SUB_MENU_H

#include "menu_item.h"
#include "menu_config.h"

#include <QWidget>
#include <QTreeWidgetItem>
#include <QMap>

namespace Ui {
class SubMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();
    QMap<QString, QString> previous;
    QMap<QString, QString> current;

private:
    Ui::SubMenu *ui;

    bool eventFilter(QObject *object, QEvent *event);
    void set_third_menu_and_connect(QString str1, QString str2);
    void disconnect_previous_signals(QString str1, QString str2);
    void get_second_menu_string(QString str1, QString str2);

    MenuConfig *menuConfig;

private slots:
    void set_third_menu(QString str1, QString str2);

};

#endif // SUB_MENU_H
