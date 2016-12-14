#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include <QWidget>

namespace Ui {
class MenuItem;
}

class MenuItem : public QWidget
{
    Q_OBJECT

public:
    enum Type {
        None,
        Label,
        Spin,
        Combo
    };

    explicit MenuItem(QWidget *parent = 0);
    ~MenuItem();

    void set_type(Type type);

    void clean();

    void set_title(const QString &title);
    void set_unit(const QString &unitName);
    void set_steps(const QList<double> &steps);
    void set_suffix(const QString &text);
    void set_range(double min, double max);
    void set_decimals(int prec);

    void add_combo_item(const QString &text);
    void set_combo_items(const QStringList &texts);

    void set_label_text(const QString &text);

    void set_spin(const QString &title, const QString &unit, const QList<double> &steps, double min, double max, int decimals);
    void set_combo(const QString &title, const QStringList &texts);
    void set_label(const QString &title);

    QString get_title();
    QString get_label_text();

signals:
    void clicked();
    void spin_event(double value);
    void combo_enevt(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::MenuItem *ui;

    QString m_unit;
    QString m_title;
    QString m_labelText;

    QList<double> m_steps;
    int m_curStep;

    void update_title();
    void update_spin_step();
    void set_spin_focus();
    void set_focus_out();
};

#endif // __MENU_ITEM_H__
