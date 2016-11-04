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
    void on_spinBoxPaLawQty_valueChanged(int arg1);

    void on_spinBoxUtLawQty_valueChanged(int arg1);

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

    void on_spinBoxEcho_valueChanged(int arg1);

    void on_comboBoxAlarmOutput_currentIndexChanged(int index);

    void on_comboBoxAlarmOutputValid_currentIndexChanged(int index);

    void do_checkBox_changed();

    void on_comboBoxAlarmOutputLogicGroup_currentIndexChanged(int index);

    void on_comboBoxAlarmOutputOperator_currentIndexChanged(int index);

    void on_comboBoxAlarmOutputCondition_currentIndexChanged(int index);

    void on_spinBoxAlarmOutputCount_valueChanged(int arg1);

    void on_spinBoxAlarmOutputDelay_valueChanged(int arg1);

    void on_spinBoxAlarmOutputHoldTime_valueChanged(int arg1);

    void on_comboBoxAlarmAnalog_currentIndexChanged(int index);

    void on_comboBoxAlarmAnalogValid_currentIndexChanged(int index);

    void on_comboBoxAlarmAnalogLogicGroup_currentIndexChanged(int index);

    void on_comboBoxAlarmAnalogType_currentIndexChanged(int index);

    void on_pushButtonReset_clicked();    

    void on_pushButtonGroupCreate_clicked();

    void on_pushButtonGroupDelete_clicked();

    void on_comboBoxCurrentGroup_currentIndexChanged(int index);


    void on_comboBoxGroupFreqBand_currentIndexChanged(int index);

    void on_comboBoxGroupVideoFilter_currentIndexChanged(int index);

    void on_comboBoxGroupRectifier_currentIndexChanged(int index);

    void on_spinBoxGroupCompressRato_valueChanged(int arg1);

    void on_spinBoxGroupGain_valueChanged(int arg1);


    void on_spinBoxGroupThicknessFactor_valueChanged(int arg1);

    void on_comboBoxGroupUt1_currentIndexChanged(int index);

    void on_comboBoxGroupUt2_currentIndexChanged(int index);

    void on_comboBoxGroupPa_currentIndexChanged(int index);

    void on_spinBoxGroupSumGain_valueChanged(int arg1);

    void on_spinBoxGroupSampleRange_valueChanged(int arg1);

    void on_spinBoxGroupPointQty_valueChanged(int arg1);

    void on_spinBoxGroupTcgPointQty_valueChanged(int arg1);

    void on_comboBoxGroupTcg_currentIndexChanged(int index);

    void on_spinBoxGroupRxTime_valueChanged(int arg1);

    void on_spinBoxGroupIdelTime_valueChanged(int arg1);

    void on_spinBoxGroupGateAHeight_valueChanged(int arg1);

    void on_spinBoxGroupGateALogic_valueChanged(int arg1);

    void on_spinBoxGroupGateBHeight_valueChanged(int arg1);

    void on_spinBoxGroupGateBLogic_valueChanged(int arg1);

    void on_spinBoxGroupGateIHeight_valueChanged(int arg1);

    void on_spinBoxGroupGateILogic_valueChanged(int arg1);

    void on_spinBoxGroupThinknessMin_valueChanged(int arg1);

    void on_spinBoxGroupReject_valueChanged(int arg1);

    void on_spinBoxGroupSampleStart_valueChanged(int arg1);

    void on_spinBoxGroupAverage_valueChanged(int arg1);

    void on_spinBoxGroupThicknessMax_valueChanged(int arg1);

    void on_spinBoxGroupThicknessSource_valueChanged(int arg1);

    void on_spinBoxGroupTxEnd_valueChanged(int arg1);

    void on_spinBoxGroupTxStart_valueChanged(int arg1);

    void on_pushButtonGroupReflesh_clicked();

    void on_pushButtonBeamCreate_clicked();

    void on_pushButtonBeamDelete_clicked();


    void on_comboBoxCurrentBeam_currentIndexChanged(int index);

    void on_spinBoxBeamGainOffset_valueChanged(int arg1);

    void on_spinBoxBeamInfo_valueChanged(int arg1);

    void on_spinBoxBeamDelay_valueChanged(int arg1);

    void on_spinBoxBeamGateASTart_valueChanged(int arg1);

    void on_spinBoxBeamGateAEnd_valueChanged(int arg1);

    void on_spinBoxBeamGateBStart_valueChanged(int arg1);

    void on_spinBoxBeamGateBEnd_valueChanged(int arg1);

    void on_spinBoxBeamGateIStart_valueChanged(int arg1);

    void on_spinBoxBeamGateIEnd_valueChanged(int arg1);

    void on_spinBoxBeamTxChannel_valueChanged(int arg1);

    void on_spinBoxBeamRxChannel_valueChanged(int arg1);

    void on_spinBoxBeamTxChannelSelect_valueChanged(int arg1);

    void on_spinBoxBeamRxChannelSelect_valueChanged(int arg1);

    void on_spinBoxBeamTxDelay_valueChanged(int arg1);

    void on_spinBoxBeamRxDelay_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Fpga *m_fpga;
    AlarmOutput *m_alarmOutput;
    AlarmAnalog *m_alarmAnalog;

    GroupPointer m_group;
    BeamPointer m_beam;
};

#endif // MAINWINDOW_H
