/**
 * @file tofd_properties_widget.h
 * @brief UT中的检测设置Widget.
 */

#ifndef __UT_DETECT_SETTING_WIDGET_H__
#define __UT_DETECT_SETTING_WIDGET_H__

#include <QWidget>

#include "wizard_setting.h"

namespace Ui {
class UTDetectSettingWidget;
}

class UTDetectSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UTDetectSettingWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~UTDetectSettingWidget();

signals:

    void current_mode_changed(int index);

protected slots:
    void do_modeComboBox_current_index_changed(int index);

private:
    Ui::UTDetectSettingWidget *ui;
};

#endif // __UT_DETECT_SETTING_WIDGET_H__
