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

    void set(const QString &title, const QString &unit, double min, double max, int decimals);
    double get_current_value() const;

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::SpinMenuItem *ui;

    QString m_unit;
    QString m_title;

    void update_title();
    void update_spin_step();
    void set_focus();
    void set_focus_out();
};

#endif // __MENU_ITEM_H__
