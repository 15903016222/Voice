#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "firstsecondmenuwidget.h"
#include "commonmenuwidget.h"
#include "commonmenubutton.h"
#include "myinputpanel.h"
#include "mcu.h"

#include <QMainWindow>
#include <QTranslator>
#include <QGraphicsOpacityEffect>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void show_hidden_Menu();
    void resizeEvent(QResizeEvent *event);
    void show_hidden_arrow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *moveEvent);
    void keyPressEvent(QKeyEvent *event);

private:
    void init_ui();

    Ui::MainWindow *ui;

    QTranslator *translator;
    Mcu *m_mcu;
    QGraphicsOpacityEffect *effect;

    CommonMenuWidget * commonMenuWidget;
    FirstSecondMenuWidget *firstSecondMenu;
    CommonMenuButton *commonMenuButton;
    MyInputPanel *myInputPanelDlg;

    bool hiddenFirstSecondMenuFlag;
    bool hiddenThirdMenuFlag;
    bool hiddenCommonMenuFlag;
    bool hiddenArrowFlag;
    bool hiddenKeyboardFlag;

    int firstMenuNum;
    int secondMenuNum;
    int mainMenuStartPos;
    int mainMenuEndPos;


protected slots:
    void do_key_event(Mcu::KeyType type);

    void slot_firstMenuToolBoxCurrentChanged(int index);
    void slot_secondMenuItemClicked(QModelIndex index);
    void on_pushButton_top_clicked();
    void on_pushButton_bottom_clicked();
    void slot_pushButton_commonMenuClicked();
    void scroll_menu(int index);
    void update_translator(QString string);
    void do_keyboard_event();
    void slot_keyboard_close_clicked();
    void slot_setMenuOpacity(double value);

signals:
    void clickedMenuIndex(int);
    void show_keyboard(int);
    void close_persistent_editor(int);
};

#endif // MAINWINDOW_H
