/**
 * @file acg_properties_widget.h
 * @brief ACG属性设置Widget
 */

#ifndef __ACG_PROPERTIES_WIDGET_H__
#define __ACG_PROPERTIES_WIDGET_H__

#include <QWidget>

namespace Ui {
class ACGPropertiesWidget;
}

class ACGPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ACGPropertiesWidget(QWidget *parent = 0);
    ~ACGPropertiesWidget();

private:
    Ui::ACGPropertiesWidget *ui;
};

#endif // __ACG_PROPERTIES_WIDGET_H__
