/**
 * @file tofd_properties_widget.h
 * @brief TOFD设置Widget.
 */

#ifndef __TOFD_PROPERTIES_WIDGET_H__
#define __TOFD_PROPERTIES_WIDGET_H__

#include <QWidget>

namespace Ui {
class TOFDPropertiesWidget;
}

class TOFDPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TOFDPropertiesWidget(QWidget *parent = 0);
    ~TOFDPropertiesWidget();

private:
    Ui::TOFDPropertiesWidget *ui;
};

#endif // __TOFD_PROPERTIES_WIDGET_H__
