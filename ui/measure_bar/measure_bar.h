#ifndef __MEASURE_BAR_H__
#define __MEASURE_BAR_H__

#include "measure_calculation.h"

#include <device/device.h>
#include <source/source.h>

#include <QWidget>

namespace Ui {
class MeasureBar;
}

class MeasureBar : public QWidget
{
    Q_OBJECT

public:
    explicit MeasureBar(QWidget *parent = 0);
    ~MeasureBar();

private:
    Ui::MeasureBar *ui;
//    MeasureCalculation *measureCalculation;
    QMap<MeasureDialog::MeasureType, MeasureCalculation::Function> m_map;
//    DplDevice::GroupPointer *m_group;

    void init_map();
    double calculate_value(MeasureDialog::MeasureType type);

public slots:
    void do_type_changed(MeasureDialog::MeasureType type);
    void do_current_group_changed();
//    void do_source_type_changed(DplSource::Source::Type);

};

#endif // __MEASURE_BAR_H__

