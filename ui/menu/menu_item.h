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
    void set_steps(QList<double> &steps);

    void add_item(const QString &text);

signals:
    void clicked();
    void spin_event(double value);
    void combo_event(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::MenuItem *ui;

    QString m_title;
    QString m_unit;

    QList<double> m_steps;
    int m_curStep;

    void update_title();
    void update_step();
    void set_focus();
    void set_focus_out();
};

#endif // __MENU_ITEM_H__
