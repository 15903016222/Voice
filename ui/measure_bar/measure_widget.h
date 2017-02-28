#ifndef __MEASURE_WIDGET_H__
#define __MEASURE_WIDGET_H__

#include "measure_dialog.h"

#include <QWidget>

namespace Ui {
class MeasureWidget;
}

class MeasureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeasureWidget(QWidget *parent = 0);
    ~MeasureWidget();

    QString name() const;
    MeasureDialog::MeasureType type() const { return m_type; }
    void set_type(MeasureDialog::MeasureType type);
    void set_value(const QString &value);

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::MeasureWidget *ui;
    MeasureDialog::MeasureType m_type;
    QString m_unit;
    QString m_title;

    void update_title();

signals:
    void type_changed(MeasureDialog::MeasureType);
};

#endif // __MEASURE_WIDGET_H__
