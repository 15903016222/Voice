/**
 * @file combo_menu_item.h
 * @brief combo menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __COMBO_MENU_ITEM_H__
#define __COMBO_MENU_ITEM_H__

#include "menu_item.h"

namespace Ui {
class ComboMenuItem;
}

class ComboMenuItem : public MenuItem
{
    Q_OBJECT

public:
    explicit ComboMenuItem(QWidget *parent = 0);
    ~ComboMenuItem();

    void set_title(const QString &title);

    void add_item(const QString &text);
    void set_items(const QStringList &texts);

    void set(const QString &title, const QStringList &texts);

    void set_current_index(int index);
    int get_current_index() const;

    enum DisplayMode {
        ALL,
        PREFIX,
        SUFFIX
    };
    void set_dispay_mode(DisplayMode mode);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::ComboMenuItem *ui;

    int m_displayMode;

private slots:
    void set_label_text(QString text);
};

#endif // __COMBO_MENU_ITEM_H__
