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

class QPushButton;
class QLabel;

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
    QString title() const;

    /**
     * @brief set_title 设置标题
     * @param title     标题
     */
    void set_title(const QString &title);

    /**
     * @brief text  获取显示文本
     * @return      字符串
     */
    QString text() const;

    /**
     * @brief set_text  设置显示文本
     * @param text      字符串
     */
    void set_text(const QString &text);

    /**
     * @brief set_selected  设置当前Item是否选中
     * @param flag  true：选中；false：不选中
     */
    virtual void set_selected(bool flag);

    /**
     * @brief set_edit  设置当前Item进行编辑状态
     * @param flag  true：编辑状态；false：非编辑
     */
    virtual void set_edit(bool flag);

signals:
    /**
     * @brief clicked   点击信号
     */
    void clicked();

private:
    QPushButton *m_pushBtn;
    QLabel *m_label;
    QString m_text;
};

#endif // __LABEL_MENU_ITEM_H__
