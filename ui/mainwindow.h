#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "firstsecondmenuwidget.h"
#include "commonmenuwidget.h"
#include "commonmenubutton.h"
#include "myinputpanel.h"
#include "mcu.h"

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindowPrivate;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    MainWindowPrivate * const d_ptr;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *moveEvent);
    void keyPressEvent(QKeyEvent *event);

private:
    Q_DECLARE_PRIVATE(MainWindow)

public:
    CommonMenuWidget * commonMenuWidget;
    FirstSecondMenuWidget *firstSecondMenu;
    CommonMenuButton *commonMenuButton;
    MyInputPanel *myInputPanelDlg;

    void show_hidden_Menu();
    void resizeEvent(QResizeEvent *event);
    void show_hidden_arrow();

    bool hiddenFirstSecondMenuFlag;
    bool hiddenThirdMenuFlag;
    bool hiddenCommonMenuFlag;
    bool hiddenArrowFlag;

    int firstMenuNum;
    int secondMenuNum;
    int mainMenuStartPos;
    int mainMenuEndPos;
    int keyValue;

private:
    void init_ui();
    QTranslator *translator;
    Mcu *m_mcu;


protected slots:
    void keyBottom_menu(int key);
    void keyLeft_menu(int key);
    void keyLeft_back(int key);

private slots:
    void slot_firstMenuToolBoxCurrentChanged(int index);
    void slot_secondMenuItemClicked(QModelIndex index);
    void on_pushButton_top_clicked();
    void on_pushButton_bottom_clicked();
    void slot_pushButton_commonMenuClicked();
    void scroll_menu(int index);
    void update_translator(QString string);
    void slot_pushButton_keyboard_clicked();
    void slot_keyboard_close_clicked();

signals:
    void clickedMenuIndex(int);
    void show_keyboard(int);
    void close_persistent_editor(int);

};

#endif // MAINWINDOW_H
