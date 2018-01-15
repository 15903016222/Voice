#ifndef __TITLE_WIDGET_H__
#define __TITLE_WIDGET_H__

#include <QWidget>
#include <wizard_setting.h>

namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();

    void set_step(int step);
    void set_type(WizardSetting::E_WIZARD_TYPE type);

signals:
    void clicked(int step);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::TitleWidget *ui;
    WizardSetting::E_WIZARD_TYPE m_type;
    QVector<StepWidget*> m_stepWidgetVect;
};

#endif // __TITLE_WIDGET_H__
