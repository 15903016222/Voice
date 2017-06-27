#ifndef __MEASURE_WIDGET_H__
#define __MEASURE_WIDGET_H__

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

    QString title() const;
    void set_title(const QString &name);

    QString unit() const;
    void set_unit(const QString &unit);

    QString value() const;
    void set_value(const QString &value);

signals:
    void clicked(MeasureWidget *w);

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::MeasureWidget *ui;
    QString m_title;
    QString m_unit;

    void update_name_label();
};

inline QString MeasureWidget::title() const
{
    return m_title;
}

inline void MeasureWidget::set_title(const QString &name)
{
    m_title = name;
    update_name_label();
}

inline QString MeasureWidget::unit() const
{
    return m_unit;
}

inline void MeasureWidget::set_unit(const QString &unit)
{
    m_unit = unit;
    update_name_label();
}


#endif // __MEASURE_WIDGET_H__
