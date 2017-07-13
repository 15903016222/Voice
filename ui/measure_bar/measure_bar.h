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

private:
    Ui::MeasureBar *ui;

    DplDevice::GroupPointer m_group;
    DplSource::BeamsPointer m_beams;

    void set_measure_widget(MeasureWidget *w, Measure::Type type);
    void set_measure_widget(MeasureWidget *w, MeasureDialog &dlg);

    QString calculate_string(Measure::Type type);
};

#endif // __MEASURE_BAR_H__

