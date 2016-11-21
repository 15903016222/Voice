#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_APushButton_clicked();

    void on_ZPushButton_clicked();

    void on_onePushButton_clicked();

    void on_twoPushButton_clicked();

    void on_capsPushButton_clicked();

    void on_leftShiftPushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
