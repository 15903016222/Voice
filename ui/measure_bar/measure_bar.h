#ifndef __MEASURE_BAR_H__
#define __MEASURE_BAR_H__

#include "measure.h"
#include "measure_widget.h"

#include <QWidget>

namespace Ui {
class MeasureBar;
}

class MeasureDialog;

class MeasureBar : public QWidget
{
    Q_OBJECT

public:
    explicit MeasureBar(QWidget *parent = 0);
    ~MeasureBar();

public slots:
    void do_measureWidget_clicked(MeasureWidget *w);

    void do_current_group_changed(const DplDevice::GroupPointer &group);
    void do_beamgroup_data_event();

signals:
    void calculated(MeasureWidget *w, const QString &str);

protected slots:
    void do_calculated(MeasureWidget *w, const QString &str);

private:
    Ui::MeasureBar *ui;

    DplDevice::GroupPointer m_group;

    void set_measure_widget(MeasureWidget *w, Measure::Type type);
    void set_measure_widget(MeasureWidget *w, MeasureDialog &dlg);
};

#endif // __MEASURE_BAR_H__

