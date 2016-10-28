#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../fpga.h"

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
    void on_spinBoxPaLawQty_editingFinished();

    void on_spinBoxUtLawQty_editingFinished();

    void on_comboBoxEncoderXPolarity_currentIndexChanged(int index);

    void on_comboBoxEncoderXMode_currentIndexChanged(int index);

    void on_comboBoxEncoderYPolarity_currentIndexChanged(int index);

    void on_comboBoxEncoderYMode_currentIndexChanged(int index);

    void on_comboBoxUt1Twin_currentIndexChanged(int index);

    void on_comboBoxUt2Twin_currentIndexChanged(int index);

    void on_comboBoxUt1TxDamping_currentIndexChanged(int index);

    void on_comboBoxUt1RxDamping_currentIndexChanged(int index);

    void on_comboBoxUt2TxDamping_currentIndexChanged(int index);

    void on_comboBoxUt2RxDamping_currentIndexChanged(int index);

    void on_comboBoxUtVoltage_currentIndexChanged(int index);

    void on_comboBoxPaVoltage_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Fpga *m_fpga;
};

#endif // MAINWINDOW_H
