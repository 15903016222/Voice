#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
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

    void on_comboBoxFreeze_currentIndexChanged(int index);

    void on_comboBoxSound_currentIndexChanged(int index);

    void on_spinBoxEcho_editingFinished();

    void on_comboBoxAlarmOuput_currentIndexChanged(int index);

    void on_comboBoxAlarmOutputValid_currentIndexChanged(int index);

    void do_checkBox_changed();

    void on_comboBoxAlarmOutputLogicGroup_currentIndexChanged(int index);

    void on_comboBoxAlarmOutputOperator_currentIndexChanged(int index);

    void on_comboBoxAlarmOutputCondition_currentIndexChanged(int index);

    void on_spinBoxAlarmOutputCount_editingFinished();

    void on_spinBoxAlarmOutputDelay_editingFinished();

    void on_spinBoxAlarmOutputHoldTime_editingFinished();

    void on_comboBoxAlarmAnalog_currentIndexChanged(int index);

    void on_comboBoxAlarmAnalogValid_currentIndexChanged(int index);

    void on_comboBoxSoundAlarmAnalogLogicGroup_currentIndexChanged(int index);

    void on_comboBoxAlarmAnalogType_currentIndexChanged(int index);

    void on_pushButtonReset_clicked();

private:
    Ui::MainWindow *ui;
    Fpga *m_fpga;
    AlarmOutput *m_alarmOutput;
    AlarmAnalog *m_alarmAnalog;
};

#endif // MAINWINDOW_H
