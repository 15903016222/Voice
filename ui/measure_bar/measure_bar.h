#ifndef __MEASURE_BAR_H__
#define __MEASURE_BAR_H__

#include "measure_calculation.h"
#include "measure_dialog.h"

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
    QMap<MeasureDialog::MeasureType, MeasureCalculation::Function> m_map;
    DplDevice::GroupPointer m_group;
    DplSource::BeamGroupPointer m_beamGroup;
    int m_beamIndex;

    void init_map();
    void set();

    QString calculate_value(MeasureDialog::MeasureType type);

public slots:
    void do_type_changed(MeasureDialog::MeasureType type);
    void do_current_group_changed();
//    void do_beam_qty_changed(int qty);
    void do_beamgroup_data_event();
    void do_ut_unit_changed(DplDevice::Group::UtUnit unit);

};

#endif // __MEASURE_BAR_H__

