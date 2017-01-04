/**
 * @file label_menu_item.h
 * @brief label menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __LABEL_MENU_ITEM_H__
#define __LABEL_MENU_ITEM_H__

#include "menu_item.h"

namespace Ui {
class LabelMenuItem;
}

class LabelMenuItem : public MenuItem
{
    Q_OBJECT

public:
    explicit LabelMenuItem(QWidget *parent = 0);
    ~LabelMenuItem();

    void set_title(const QString &title);

    void set_text(const QString &text);

    void set(const QString &title, const QString &text);

    QString get_title() const;

    QString get_text() const;

signals:
    void clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::LabelMenuItem *ui;

    QString m_title;
    QString m_text;
};

inline QString LabelMenuItem::get_title() const
{
    return m_title;
}

inline QString LabelMenuItem::get_text() const
{
    return m_text;
}

#endif // __LABEL_MENU_ITEM_H__
