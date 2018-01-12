/**
 * @file multi_group_widget.h
 * @brief 多组设置Widget，提供八组设置，每组设置类型可以PA，TOFD，PE。
 */

#ifndef __MULTI_GROUP_WIDGET_H__
#define __MULTI_GROUP_WIDGET_H__

#include <QWidget>
#include <QMap>
#include <QSharedPointer>

#include "wizard_setting.h"

namespace Ui {
class MultiGroupWidget;
}

class SubWizardSetting;
class QPushButton;
class QComboBox;
class GroupWidget;

class MultiGroupWidget : public QWidget
{
    Q_OBJECT

    enum E_GROUP_NO{
        GROUP_1 = 1,
        GROUP_2,
        GROUP_3,
        GROUP_4,
        GROUP_5,
        GROUP_6,
        GROUP_7,
        GROUP_8
    };

    enum E_SUB_MODE{
        NA,
        TOFD,
        PE,
        PA
    };

public:
    explicit MultiGroupWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent = 0);
    ~MultiGroupWidget();


signals:
    void setting_signal(int num);

protected slots:
    void do_settingBtn_clicked(int model, int index);
    void do_sub_wizard_setting_next_group();
    void do_finished_setting();

private:
    Ui::MultiGroupWidget *ui;
    QSharedPointer<SubWizardSetting> m_subWizardSetting;
    QMap<QPushButton*, QComboBox*> m_pushButtonComboBoxMap;
    QMap<E_GROUP_NO, QComboBox*> m_groupNOComboBoxMap;
    int m_currentGroup;
    QVector<GroupWidget*> m_groupVect;
};

#endif // __MULTI_GROUP_WIDGET_H__
