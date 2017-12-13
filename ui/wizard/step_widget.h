/**
 * @file step_widget.h
 * @brief 设置步骤显示Widget，显示当前步骤图示。
 */

#ifndef __STEP_WIDGET_H__
#define __STEP_WIDGET_H__

#include <QWidget>

namespace Ui {
class StepWidget;
}

class StepWidget : public QWidget
{
    Q_OBJECT

public:

    enum E_STEP_TYPE {
        WORKPIECE_PROBE = 1,
        FOCALLAW,
        CALIBRATION,
        DETECT_SETTING,
        MULTI_GROUP
    };

    enum E_SELECT_TYPE {
        UNSELECTED = 0,
        SELECTED = 1
    };

public:
    explicit StepWidget(QWidget *parent = 0);
    ~StepWidget();

    void set_widget(E_STEP_TYPE type, StepWidget::E_SELECT_TYPE selectType = UNSELECTED);
    void set_selected(E_SELECT_TYPE type);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::StepWidget *ui;
    QStringList     m_pic;
    E_SELECT_TYPE   m_type;

    void select_pic(E_STEP_TYPE type);

};



#endif // __STEP_WIDGET_H__
