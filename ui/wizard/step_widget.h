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
    explicit StepWidget(QWidget *parent = 0);
    ~StepWidget();

    void set_title(const QString &title);
    void set_back_ground(const QStringList &list);
    void set_selected(bool flag);

private:
    Ui::StepWidget *ui;
    QStringList m_backGroundPath;
    bool m_selected;
};



#endif // __STEP_WIDGET_H__
