/**
 * @file wizard_setting.h
 * @brief 向导设置Widget，显示各设置窗口。
 */

#ifndef __WIZARD_SETTING_H__
#define __WIZARD_SETTING_H__

#include <QDialog>
#include <QSharedPointer>
#include "device/group.h"

class StepWidget;
class Selector;

namespace Ui {
class WizardSetting;
}

class WizardSetting : public QDialog
{
    Q_OBJECT

public:

    enum E_WIZARD_TYPE
    {
        WELD_PA_DETECT,
        COMMON_PA_DETECT,
        MULTI_GROUP_DETECT,
        UT_DETECT,
        OPEN_DATA,
        OPEN_CONFIG_FILE,
        SUB_WELD_PA_DETECT,
        SUB_UT_DETECT
    };

    enum E_STEP
    {
        STEP_1,
        STEP_2,
        STEP_3,
        STEP_4
    };


    explicit WizardSetting(QWidget *parent = 0);
    ~WizardSetting();

    void show(WizardSetting::E_WIZARD_TYPE type);

signals:

   void finished_wizard_setting(WizardSetting::E_WIZARD_TYPE type);
   void cancle_wizard_setting();
   void next_group();

protected slots:
    virtual void on_backBtn_clicked();
    virtual void on_nextBtn_clicked();

   void do_step_widget_clicked(int step);

protected:
   QSharedPointer<Selector> m_widgetSelector;
   WizardSetting::E_WIZARD_TYPE m_type;
   DplDevice::GroupPointer m_currentGroup;

private:
    Ui::WizardSetting *ui;

    void init_widget();
    void update_step_widget();
};

#endif // __WIZARD_SETTING_H__