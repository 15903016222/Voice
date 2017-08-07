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
    explicit ComboMenuItem(QWidget *parent, const QString &title);
    ~ComboMenuItem();

    /**
     * @brief set_title 设置标题
     * @param title     标题
     */
    void set_title(const QString &title);

    /**
     * @brief add_item  添加显示项字符串
     * @param text      项字符串
     */
    void add_item(const QString &text);

    /**
     * @brief add_items 添加显示项字符串列表
     * @param texts     显示项字符串列表
     */
    void add_items(const QStringList &texts);

    /**
     * @brief set       设置显示项字符串列表
     * @param texts     显示项字符串列表
     */
    void set(const QStringList &texts);

    /**
     * @brief set_current_index 设置当前索引
     * @param index             索引值
     */
    void set_current_index(int index);

    /**
     * @brief current_index 获取当前索引值
     * @return              索引值
     */
    int current_index() const;

    /**
     * @brief current_text  获取当前文本信息
     * @return              字符串
     */
    QString current_text() const;

    enum DisplayMode {
        ALL,
        PREFIX,
        SUFFIX
    };

    /**
     * @brief set_dispay_mode   设置显示方式
     * @param mode              显示方式
     */
    void set_dispay_mode(DisplayMode mode);

signals:    
    void value_changed(int index);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::ComboMenuItem *ui;

    int m_displayMode;

private slots:
    void set_label_text(QString text);
};

#endif // __COMBO_MENU_ITEM_H__
