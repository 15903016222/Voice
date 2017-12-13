/**
 * @file sub_wizard_setting.h
 * @brief 子向导设置，继承向导设置。用于多组设置时的各组设置切换。
 */

#ifndef __SUB_WIZARD_SETTING_H__
#define __SUB_WIZARD_SETTING_H__

#include "wizard_setting.h"


class SubWizardSetting : public WizardSetting
{

public:
    SubWizardSetting(QWidget *parent = 0);
    void show(WizardSetting::E_WIZARD_TYPE type);

protected slots:
    virtual void on_backBtn_clicked();
    virtual void on_nextBtn_clicked();
    virtual void do_next_group();

};

#endif // __SUB_WIZARD_SETTING_H__
