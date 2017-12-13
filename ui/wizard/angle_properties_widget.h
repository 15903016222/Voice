/**
 * @file angle_properties_widget.h
 * @brief 角度属性设置Widget
 */

#ifndef __ANGLE_PROPERTIES_WIDGET_H__
#define __ANGLE_PROPERTIES_WIDGET_H__

#include <QWidget>

namespace Ui {
class AnglePropertiesWidget;
}

class AnglePropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnglePropertiesWidget(QWidget *parent = 0);
    ~AnglePropertiesWidget();

private:
    Ui::AnglePropertiesWidget *ui;
};

#endif // __ANGLE_PROPERTIES_WIDGET_H__
