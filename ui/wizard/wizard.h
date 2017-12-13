/**
 * @file wizard.h
 * @brief 向导设置主Widget，提供焊缝PA向导、通用PA向导、多组设置、单组设置、打开数据文件、打开配置文件六组功能入口。
 */

#ifndef ___WIZARD_WINDOW_H__
#define ___WIZARD_WINDOW_H__

#include <QWidget>
#include "wizard_setting.h"


namespace Ui {
class Wizard;
}

class Wizard : public QWidget
{
    Q_OBJECT

public:
    explicit Wizard(QWidget *mainWindow, QWidget *parent = 0);
    ~Wizard();

public slots:

    void slot_finished_wizard_setting(WizardSetting::E_WIZARD_TYPE type);

protected slots:

    void on_weldPADetectBtn_clicked();
    void on_currentPADetectBtn_clicked();
    void on_multiGroupDetectBtn_clicked();
    void on_singleDetectBtn_clicked();
    void on_openDataBtn_clicked();
    void on_openConfigFileBtn_clicked();

private:

    Ui::Wizard      *ui;
    QWidget         *m_mainWindow;
    WizardSetting   *m_wizardSetting;

    void keyPressEvent(QKeyEvent *event);

};

#endif // ___WIZARD_WINDOW_H__
