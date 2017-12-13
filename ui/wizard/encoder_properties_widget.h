/**
 * @file encoder_properties_widget.h
 * @brief 编码器属性设置Widget，用于设置编码器的相关属性数据。
 */

#ifndef __ENCODER_PROPERTIES_WIDGET_H__
#define __ENCODER_PROPERTIES_WIDGET_H__

#include <QWidget>

namespace Ui {
class EncoderPropertiesWidget;
}

class EncoderPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EncoderPropertiesWidget(QWidget *parent = 0);
    ~EncoderPropertiesWidget();

private:
    Ui::EncoderPropertiesWidget *ui;
};

#endif // __ENCODER_PROPERTIES_WIDGET_H__
