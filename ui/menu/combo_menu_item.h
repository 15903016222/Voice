#ifndef __COMBO_MENU_ITEM_H__
#define __COMBO_MENU_ITEM_H__

#include <QWidget>

namespace Ui {
class ComboMenuItem;
}

class ComboMenuItem : public QWidget
{
    Q_OBJECT

public:
    explicit ComboMenuItem(QWidget *parent = 0);
    ~ComboMenuItem();

    void set_title(const QString &title);

    void add_item(const QString &text);
    void set_items(const QStringList &texts);

    void set(const QString &title, const QStringList &texts);

signals:
    void value_changed(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::ComboMenuItem *ui;
};

#endif // __COMBO_MENU_ITEM_H__
