/**
 * @file spin_menu_item.h
 * @brief spin menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __SPIN_MENU_ITEM_H__
#define __SPIN_MENU_ITEM_H__

#include "menu_item.h"

namespace Ui {
class SpinMenuItem;
}

class SpinMenuItem : public MenuItem
{
    Q_OBJECT

public:
    explicit SpinMenuItem(QWidget *parent = 0);
    ~SpinMenuItem();

    void set_title(const QString &title);
    void set_unit(const QString &unitName);
    void set_suffix(const QString &text);
    void set_range(double min, double max);
    void set_decimals(int prec);

    void set(const QString &unit, double min, double max, int decimals);
    void set(const QString &title, const QString &unit, double min, double max, int decimals);

    double get_value() const;

public slots:
    void set_value(double value);

signals:
    void value_changed(double value);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::SpinMenuItem *ui;

    QString m_unit;
    QString m_title;

    QString m_suffix;

    double m_value;
    double m_max;
    double m_min;
    double m_step;
    int m_decimals;

    void update_title();
    void update_spin_step();
    void set_focus();
    void set_focus_out();

    void update_value();
    void add();
    void sub();
};

inline void SpinMenuItem::set_title(const QString &title)
{
    m_title = title;
    update_title();
}

inline void SpinMenuItem::set_unit(const QString &unitName)
{
    m_unit = unitName;
    update_title();
}

inline void SpinMenuItem::set_suffix(const QString &text)
{
    m_suffix = text;
    update_value();
}

inline void SpinMenuItem::set(const QString &unit, double min, double max, int decimals)
{
    set(m_title, unit, min, max, decimals);
}

inline double SpinMenuItem::get_value() const
{
    return m_value;
}

inline void SpinMenuItem::set_value(double value)
{
    if (m_value != value) {
        m_value = value;
        update_value();
        emit value_changed(m_value);
    }
}

#endif // __MENU_ITEM_H__
