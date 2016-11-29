#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QWidget>
#include <QVariantMap>
#include <QFile>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

    QVariantMap translateChineseMap;

private:
    Ui::MainMenu *ui;

    bool eventFilter(QObject *object, QEvent *event);

    int m_languageOption;
    int m_firstCount;

private slots:
    void change_item_selection();

};

#endif // MAIN_MENU_H
