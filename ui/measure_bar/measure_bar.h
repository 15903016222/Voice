#ifndef __MEASURE_BAR_H__
#define __MEASURE_BAR_H__

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
};

#endif // __MEASURE_BAR_H__

