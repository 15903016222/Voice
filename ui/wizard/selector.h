/**
 * @file selector.h
 * @brief 设置Widget选择器，包括工件探头设置、聚焦法则设置、检测设置、校准设置、多组设置、单组UT设置等。
 */

#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include <QObject>
#include "wizard_setting.h"

class Selector : public QObject
{
    Q_OBJECT
public:
    explicit Selector(QObject *parent = 0);
    ~Selector();


    QWidget*    get_current_widget(WizardSetting::E_WIZARD_TYPE type);
    QWidget*    get_widget(int index);
    QWidget*    get_pre_widget();
    QWidget*    get_back_widget();
    QWidget*    get_last_widget();

    bool        is_last_widget();
    bool        is_first_widget();
    int         get_current_index();
    bool        set_current_index(int index);
    void        clear_widget();

private:
    QList<QWidget *>             m_widgetList;
    WizardSetting::E_WIZARD_TYPE m_type;
    int                          m_currentIndex;

};

#endif // __SELECTOR_H__
