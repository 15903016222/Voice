#ifndef __MULTI_COMBO_MENU_ITEM_H__
#define __MULTI_COMBO_MENU_ITEM_H__

#include "menu_item.h"

class QMenu;
class QAction;
class QPushButton;
class QLabel;

class MultiComboMenuItem : public MenuItem
{
    Q_OBJECT
public:
    explicit MultiComboMenuItem(const QString &title, QWidget *parent);
    ~MultiComboMenuItem();

    /**
     * @brief add_item  追加一个项
     * @param text      项名称
     */
    void add_item(const QString &text);

    /**
     * @brief add_items 追加多个项
     * @param text      多个项名称列表
     */
    void add_items(const QStringList &texts);

    /**
     * @brief clear 清除多个项
     */
    void clear();

    /**
     * @brief value 获取数值
     * @return      数值
     */
    int value() const;

    /**
     * @brief set_value 设置数值
     * @param value     数值
     */
    void set_value(int value);

    void set_selected(bool flag) {}
    void set_edit(bool flag) {}

signals:
    void triggered(int, bool);

protected slots:
    void do_triggered(QAction *act);
    void do_pushBtn_clicked();

protected:
    void update_label();

private:
    QMenu *m_menu;
    QPushButton *m_pushBtn;
    QLabel *m_label;
};

#endif // __MULTI_COMBO_MENU_ITEM_H__
