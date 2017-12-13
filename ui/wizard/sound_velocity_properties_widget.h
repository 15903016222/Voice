/**
 * @file sound_velocity_properties_widget.h
 * @brief 声速设置Widget,对声速各属性进行设置
 */

#ifndef __SOUND_VELOCITY_PROPERTIES_WIDGET_H__
#define __SOUND_VELOCITY_PROPERTIES_WIDGET_H__

#include <QWidget>
#include "wizard_setting.h"

namespace Ui {
class SoundVelocityPropertiesWidget;
}

class SoundVelocityPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoundVelocityPropertiesWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~SoundVelocityPropertiesWidget();

private:
    Ui::SoundVelocityPropertiesWidget *ui;
};

#endif // __SOUND_VELOCITY_PROPERTIES_WIDGET_H__
