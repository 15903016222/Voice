/**
 * @file menu_item.h
 * @brief menu item base class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include <QWidget>

class MenuItem : public QWidget
{
    Q_OBJECT
public:
    enum Type {
        Label,
        Spin,
        Combo
    };

    explicit MenuItem(QWidget *parent = 0, MenuItem::Type type = MenuItem::Label);

    virtual void set(const QString &title, const QString &text);
    virtual void set(const QString &title, const QStringList &texts);
    virtual void set(const QString &title, const QString &unit, double min, double max, int decimals);

    void set_type(MenuItem::Type type) { m_type = type; }
    MenuItem::Type type() const { return m_type;}

signals:
    void value_changed(double value);
    void value_changed(int index);
    void clicked();

public slots:

private:
    Type m_type;
};

#endif // __MENU_ITEM_H__
