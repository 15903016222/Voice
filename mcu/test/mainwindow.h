#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../mcu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void on_mcu_event(Mcu::Cmd type, QByteArray &data);

private:
    Ui::MainWindow *ui;
    Mcu *m_mcu;
};

#endif // MAINWINDOW_H
