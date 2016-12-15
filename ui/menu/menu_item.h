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
    void set_suffix(const QString &text);
    void set_range(double min, double max);
    void set_decimals(int prec);

    void add_combo_item(const QString &text);
    void set_combo_items(const QStringList &texts);

    void set_label_text(const QString &text);

    void set_spin(const QString &title, const QString &unit, double min, double max, int decimals);
    void set_combo(const QString &title, const QStringList &texts);
    void set_label(const QString &title);

    QString get_title();
    QString get_label_text();

signals:
    void clicked();
    void spin_event(double value);
    void combo_event(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::MenuItem *ui;

    Type m_type;
    QString m_unit;
    QString m_title;
    QString m_labelText;

    void update_title();
    void update_spin_step();
    void set_spin_focus();
    void set_focus_out();

    bool do_namelabel_event(QEvent *e);
    bool do_doubleSpinBox_event(QEvent *e);

private slots:
    bool do_comboBox_activated(const QString &label);
};

#endif // __MENU_ITEM_H__
