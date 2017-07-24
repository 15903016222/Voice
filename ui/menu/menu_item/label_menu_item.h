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
    explicit LabelMenuItem(QWidget *parent, const QString &title = "", const QString &text = "");

    ~LabelMenuItem();

    /**
     * @brief get_title 获取标题
     * @return          标题
     */
    const QString &title() const;

    /**
     * @brief set_title 设置标题
     * @param title     标题
     */
    void set_title(const QString &title);

    /**
     * @brief text  获取显示文本
     * @return      字符串
     */
    const QString &text() const;

    /**
     * @brief set_text  设置显示文本
     * @param text      字符串
     */
    void set_text(const QString &text);

signals:
    /**
     * @brief clicked   点击信号
     */
    void clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::LabelMenuItem *ui;

    QString m_title;
    QString m_text;
};

inline const QString &LabelMenuItem::title() const
{
    return m_title;
}

inline const QString &LabelMenuItem::text() const
{
    return m_text;
}

#endif // __LABEL_MENU_ITEM_H__
