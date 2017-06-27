#ifndef __MEASURE_DIALOG_H__
#define __MEASURE_DIALOG_H__

#include <QDialog>
#include <QMap>

#include "measure.h"

namespace Ui {
class MeasureDialog;
}

class MeasureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MeasureDialog(QWidget *parent = 0, Measure::Type type=Measure::Gate_A_Peak);
    ~MeasureDialog();

    Measure::Type get_type() const;
    QString get_type_string();
    QString get_unit() const;
    void set_type(Measure::Type type);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MeasureDialog *ui;
};

#endif // __MEASURE_DIALOG_H__
