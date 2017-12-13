/**
 * @file calibration_widget.h
 * @brief 校准Widget，用于设置校准数据。
 */

#ifndef __CALIBRATION_WIDGET_H__
#define __CALIBRATION_WIDGET_H__

#include <QWidget>
#include <QMap>
#include "wizard_setting.h"

#include "common_setting_widget.h"

namespace Ui {
class CalibrationWidget;
}

class CalibrationWidget : public CommonSettingWidget
{
    Q_OBJECT

    enum E_SINGLE_PROPERTIES
    {
        SINGLE_DETECT_SOUND_VELOVITY_PROPERTIES = 0,
        SINGLE_DETECT_DELAY_PROPERTIES,
        SINGLE_DETECT_ANGLE_PROPERTIES,
        SINGLE_DETECT_TOFD_PROPERTIES
    };

    enum E_MULTI_GROUP_PROPERTIES
    {
        PA_ENCODER_PROPERTIES = 0,
        PA_SOUND_VELOVITY_PROPERTIES,
        PA_DELAY_PROPERTIES,
        PA_ACG_PROPERTIES,
        PA_TCG_PROPERTIES
    };

public:
    explicit CalibrationWidget(WizardSetting::E_WIZARD_TYPE type, bool isSubCalibrationWidget = false, QWidget *parent = 0);
    ~CalibrationWidget();

signals:
    void back_clicked();
    void finished_clicked();
    void next_group_clicked();

protected slots:

    void on_backBtn_clicked();
    void on_finishedBtn_clicked();

    void do_nextGroupBtn_clicked();
    void do_utDetectSettingWidget_current_mode_changed(int index);
    void do_optionComboBox_current_index_changed(int index);

private:
    Ui::CalibrationWidget *ui;
    void initItem();

    QMap<int, QWidget*>         m_widgetMap;
    int                         m_currentIndex;
    bool                        m_isSubWidget;
};

#endif // __CALIBRATION_WIDGET_H__
