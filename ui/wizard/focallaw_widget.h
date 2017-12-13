/**
 * @file focallaw_widget.h
 * @brief 聚焦法则属性设置Widget，用于聚焦法则的相关属性数据设置。
 */

#ifndef __FOCALLAW_WIDGET_H__
#define __FOCALLAW_WIDGET_H__

#include <QWidget>
#include "wizard_setting.h"

namespace Ui {
class FocallawWidget;
}

class FocallawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FocallawWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~FocallawWidget();

private:
    Ui::FocallawWidget *ui;
};

#endif // __FOCALLAW_WIDGET_H__
