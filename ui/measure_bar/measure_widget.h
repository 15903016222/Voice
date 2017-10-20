/**
 * @file measure_widget.h
 * @brief 测量部件
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-19
 */

#ifndef __MEASURE_WIDGET_H__
#define __MEASURE_WIDGET_H__

#include <QWidget>
#include <measure.h>
#include <QReadWriteLock>

namespace Ui {
class MeasureWidget;
}

class MeasureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasureWidget(QWidget *parent = 0);
    ~MeasureWidget();

    /**
     * @brief type      获取显示测量类型
     * @return          测量类型
     */
    Measure::Type type() const;

    /**
     * @brief set_type  设置显示测量类型
     * @param type      测量类型
     */
    void set_type(Measure::Type type);

    QString title() const;
    void set_title(const QString &name);

    QString unit() const;
    void set_unit(const QString &unit);

    QString value() const;
    void set_value(const QString &value);

signals:
    void clicked(MeasureWidget *w);
    void calculated(const QString &text);

protected:
    bool eventFilter(QObject *object, QEvent *event);
    void update_name_label();

protected slots:
    void do_current_group_changed(const DplDevice::GroupPointer &grp);
    void do_data_event();

private:
    Ui::MeasureWidget *ui;
    QString m_title;
    QString m_unit;
    Measure::Type m_type;
    DplDevice::GroupPointer m_group;
    QReadWriteLock m_rwLock;
};

inline Measure::Type MeasureWidget::type() const
{
    return m_type;
}

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
