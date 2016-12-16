#ifndef __SPIN_MENU_ITEM_H__
#define __SPIN_MENU_ITEM_H__

#include <QWidget>

namespace Ui {
class SpinMenuItem;
}

class SpinMenuItem : public QWidget
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

signals:
    void value_changed(double value);

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
