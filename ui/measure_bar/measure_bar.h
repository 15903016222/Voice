/**
 * @file measure_bar.h
 * @brief 测量显示栏
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-19
 */
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

private:
    Ui::MeasureBar *ui;

    void set_measure_widget(MeasureWidget *w, Measure::Type type);
    void set_measure_widget(MeasureWidget *w, MeasureDialog &dlg);
};

#endif // __MEASURE_BAR_H__

