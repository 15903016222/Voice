/**
 * @file workpiece_probe_widget.h
 * @brief 工件探头设置Widget。
 */

#ifndef __WORKPIECE_PROBE_WIDGET_H__
#define __WORKPIECE_PROBE_WIDGET_H__

#include <QWidget>
#include "wizard_setting.h"

class MainWeldWidget;

namespace Ui {
class WorkpieceProbeWidget;
}

class WorkpieceProbeWidget : public QWidget
{
    Q_OBJECT

    enum E_GEOMETRY{
        PLATE = 0,
        OD,
        ID
    };


public:
    explicit WorkpieceProbeWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~WorkpieceProbeWidget();

private slots:
    void do_editWeldBtn_clicked();
    void do_shapeComboBox_current_index_changed(int index);

    void on_probeModelDefineBtn_clicked();
    void on_moduleModelDefineBtn_clicked();
    void on_importCADBtn_clicked();

private:
    Ui::WorkpieceProbeWidget    *ui;
    MainWeldWidget              *m_mainWeldWidget;
    WizardSetting::E_WIZARD_TYPE m_type;
};

#endif // __WORKPIECE_PROBE_WIDGET_H__
