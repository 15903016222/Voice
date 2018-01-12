/**
 * @file main_menu.h
 * @brief main menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include <QWidget>

class MainMenuPrivate;
class MainMenu : public QWidget
{
    friend class MainMenuPrivate;
    Q_OBJECT
public:
    enum Type {
        UTSettings_General,
        UTSettings_Pulser,
        UTSettings_Receiver,
        UTSettings_Advanced,

        GateCurves_Gate,
        GateCurves_Alarm,
        GateCurves_Analog,
        GateCurves_DAC,
        GateCurves_TCG,

        Display_Selection,
        Display_ColorSettings,
        Displsy_Properties,

        ProbePart_Select,
        ProbePart_Position,
        ProbePart_FFT,
        ProbePart_Part,
        ProbePart_Advanced,

        FocalLaw_LawConfig,
        FocalLaw_Angle,
        FocalLaw_Aperture,
        FocalLaw_FocalPoint,

        Scan_Inspection,
        Scan_Encoder,
        Scan_Area,
        Scan_Start,

        Measurement_Cursors,
        Measurement_TOFD,
        Measurement_FlawRecord,

        FileReport_File,
        FileReport_Report,
        FileReport_Format,
        FileReport_UserField,

        Preference_Preference,
        Preference_System,
        Preference_Network
    };

    explicit MainMenu(QWidget *parent = 0);

    /**
     * @brief show  显示MainMenu
     */
    void show();

public slots:
    /**
     * @brief set_opacity   设置透明度
     * @param val           透明度(%)
     */
    void set_opacity(double val);

signals:
    void type_changed(MainMenu::Type type);

protected:
    void keyPressEvent(QKeyEvent *e);
    void changeEvent(QEvent *e);

private:
    MainMenuPrivate *d;
};

#endif // __MAIN_MENU_H__
