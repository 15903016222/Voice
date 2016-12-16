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

    QString get_text();

signals:
    void clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::LabelMenuItem *ui;
};

#endif // __LABEL_MENU_ITEM_H__
