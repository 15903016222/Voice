/**
 * @file spin_menu_item.h
 * @brief spin menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __SPIN_MENU_ITEM_H__
#define __SPIN_MENU_ITEM_H__

#include "menu_item.h"

class QPushButton;
class QLineEdit;

class SpinMenuItem : public MenuItem
{
    Q_OBJECT
public:
    explicit SpinMenuItem(QWidget *parent, const QString &title = "", const QString &unit = "");
    ~SpinMenuItem();

    /**
     * @brief set_title 设置标题
     * @param title     标题
     */
    void set_title(const QString &title);

    /**
     * @brief set_unit  设置单位
     * @param unitName  单位字符串
     */
    void set_unit(const QString &unitName);

    /**
     * @brief set_suffix    设置后缀
     * @param text          字符串
     */
    void set_suffix(const QString &text);

    /**
     * @brief set_range 设置范围
     * @param min       最小值
     * @param max       最大值
     */
    void set_range(double min, double max);

    /**
     * @brief set_decimals  设置精度
     * @param prec          精度
     */
    void set_decimals(int prec);

    /**
     * @brief set_step  设置步进
     * @param step      步进
     */
    void set_step(double step);

    /**
     * @brief set       设置参数
     * @param min       最小值
     * @param max       最大值
     * @param decimals  小数点几位
     * @param step      步进
     */
    void set(double min, double max, int decimals, double step = 1);

    /**
     * @brief get_value 获取数值
     * @return          数值
     */
    double get_value() const;

public slots:
    /**
     * @brief set_value 设置数值
     * @param value     数值
     */
    void set_value(double value);

protected slots:
    void check_number_validity(const QString &text);
    void do_pushBtn_clicked();

signals:
    /**
     * @brief value_changed 数值改变信号
     * @param value         数值
     */
    void value_changed(double value);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

    void update_title();
    void update_spin_step();
    void set_focus();
    void set_focus_out();

    void update_value();
    void add();
    void sub();

private:
    QPushButton *m_pushBtn;
    QLineEdit *m_lineEdit;

    QString m_suffix;

    QString m_title;
    QString m_unit;
    double m_value;
    double m_min;
    double m_max;
    double m_step;
    double m_baseStep;
    int m_decimals;
};

inline void SpinMenuItem::set_title(const QString &title)
{
    m_title = title;
    update_title();
}

inline void SpinMenuItem::set_unit(const QString &unitName)
{
    m_unit = unitName;
    update_title();
}

inline void SpinMenuItem::set_suffix(const QString &text)
{
    m_suffix = text;
    update_value();
}

inline void SpinMenuItem::set(double min, double max, int decimals, double step)
{
    set_range(min, max);
    set_decimals(decimals);
    set_step(step);
}

inline double SpinMenuItem::get_value() const
{
    return m_value;
}

#endif // __MENU_ITEM_H__
