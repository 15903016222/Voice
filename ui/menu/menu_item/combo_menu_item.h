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

class QMenu;
class QAction;
class QPushButton;
class QLabel;

class ComboMenuItem : public MenuItem
{
    Q_OBJECT
public:
    explicit ComboMenuItem(QWidget *parent, const QString &title="");
    ~ComboMenuItem();

    /**
     * @brief set_title 设置标题
     * @param title     标题
     */
    void set_title(const QString &title);

    /**
     * @brief add_item  添加显示项字符串
     * @param text      项显示字符串
     * @param tooTip    项提示字符串
     */
    void add_item(const QString &text, const QString &toolTip = "");

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

    /**
     * @brief clear 清除所有项
     */
    void clear();

    /**
     * @brief retranslate_items 重新翻译项目列表
     * @param list              子项名称列表
     */
    void retranslate_items(const QStringList &list);

signals:    
    void value_changed(int index);

protected slots:
    void do_pushBtn_clicked(bool checked);
    void do_triggered(QAction *action);

private:
    QMenu *m_menu;
    QAction *m_action;
    QPushButton *m_pushBtn;
    QLabel *m_label;
};

inline void ComboMenuItem::set(const QStringList &texts)
{
    clear();
    add_items(texts);
}

#endif // __COMBO_MENU_ITEM_H__
