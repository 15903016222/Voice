#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include <QTreeWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    enum Type {
        UTSettings_General      = 0x00,
        UTSettings_Pulser,
        UTSettings_Receiver,
        UTSettings_Advanced,
        GateCurves_Gate         = 0x10,
        GateCurves_Alarm,
        GateCurves_Output,
        GateCurves_DAC,
        GateCurves_TCG,
        Display_Selection       = 0x20,
        Display_ColorSettings,
        Displsy_Properties,
        ProbePart_Select        = 0x30,
        ProbePart_Position,
        ProbePart_FFT,
        ProbePart_Part,
        ProbePart_Advanced,
        FocalLaw_LawConfig      = 0x40,
        FocalLaw_Angle,
        FocalLaw_Apeture,
        FacalLaw_FocalPoint,
        Scan_Inspection         = 0x50,
        Scan_Encoder,
        Scan_Area,
        Scan_Start,
        Measurement_Cursors     = 0x60,
        Measurement_TOFD,
        Measurement_FlawRecord,
        FileReport_File         = 0x70,
        FileReport_SaveMode,
        FileReport_Report,
        FileReport_Format,
        FileReport_UserField,
        Preference_Preference   = 0x80,
        Preference_System,
        Preference_Network,
        Preference_Service
    };

    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

signals:
    void click(MainMenu::Type type);

private slots:
    void on_pushButton_up_clicked();
    void on_pushButton_down_clicked();

    void do_change_arrow();

    void on_treeWidget_clicked(const QModelIndex &index);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::MainMenu *ui;

    bool eventFilter(QObject *object, QEvent *event);

    bool do_keypress_event(QKeyEvent *e);
    bool do_keyrelease_event(QKeyEvent *e);

    void do_keyescape_event(const QModelIndex &index);
    void do_keyreturn_event(const QModelIndex &index);

};

#endif // __MAIN_MENU_H__
