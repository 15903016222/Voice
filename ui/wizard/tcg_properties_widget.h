/**
 * @file tcg_properties_widget.h
 * @brief TCG设置Widget.
 */

#ifndef __TCG_PROPERTIES_WIDGET_H__
#define __TCG_PROPERTIES_WIDGET_H__

#include <QWidget>

namespace Ui {
class TCGPropertiesWidget;
}

class TCGPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TCGPropertiesWidget(QWidget *parent = 0);
    ~TCGPropertiesWidget();

private:
    Ui::TCGPropertiesWidget *ui;
};

#endif // __TCG_PROPERTIES_WIDGET_H__
