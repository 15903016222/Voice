#ifndef GAIN_WIDGET_H
#define GAIN_WIDGET_H

#include <QWidget>

namespace Ui {
class GainWidget;
}

class GainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GainWidget(QWidget *parent = 0);
    ~GainWidget();

    void enable_ref_gain(bool flag);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    double m_preGain;
    Ui::GainWidget *ui;
    void set_focus();
    void set_focus_out();
};

#endif // GAIN_WIDGET_H
