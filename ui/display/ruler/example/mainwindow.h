#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ruler.h"

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
    void on_startDoubleSpinBox_valueChanged(double arg1);

    void on_endDoubleSpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    Ruler *m_topRuler;
    Ruler *m_leftRuler;
    Ruler *m_rightRuler;
    Ruler *m_bottomRuler;
};

#endif // MAINWINDOW_H
