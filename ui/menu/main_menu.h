#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QWidget>
#include <QTreeWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

    QTreeWidget treeWidget;

private:
    Ui::MainMenu *ui;

    bool eventFilter(QObject *object, QEvent *event);
    void show_or_hide_arrow();

    int m_languageOption;
    int m_firstCount;

signals:
    void click_main_menu(QString str1, QString str2);

private slots:
    void change_item_selection();
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();
};

#endif // MAIN_MENU_H
