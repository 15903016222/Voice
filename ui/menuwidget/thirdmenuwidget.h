#ifndef THIRDMENUWIDGET_H
#define THIRDMENUWIDGET_H

#include "firstsecondmenuwidget.h"
#include "datetimesetdialog.h"
#include "networkdialog.h"
#include "mcu.h"
#include "virtualkeyboard.h"

#define THIRD_MENU_NUMBER 6

namespace Ui {
    class ThirdMenuWidget;
}

class ThirdMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThirdMenuWidget(QWidget *parent = 0);
    ~ThirdMenuWidget();

    void set_third_menu_name(int i, int j);
    void resizeEvent(QResizeEvent *event);   
//    void open_spinbox_persistent_editor(int index);
//    void close_spinbox_persistent_editor(int index);
    QList<int> get_spinBox_range_list(QVariantMap variantMap);
    QStringList get_spinBox_step_list(QVariantMap variantMap);

    int opendSpinBoxIndex;
    bool m_keyboardShowFlag;
    QTableView *pTableView;
    QStandardItemModel *pModel;

private:
    Ui::ThirdMenuWidget *ui;

    Mcu *pMcu;
    DateTimeSetDialog *pDateTimeSetDialog;
    NetworkDialog *pNetworkDialog;

    FirstSecondMenuWidget *pFirstSecondMenuWidget;
    VirtualKeyboard *pVirtualKeyboard;

    void init_standard_model();
    void choose_widget_style(int k, QVariantMap thirdMenuMap, QString thirdMenuString);
    void set_model_item(int startIndex, QStringList thirdMenuList);
    void set_currentTime();
    void change_persistent_editor();

    QStringList get_translate_third_menu_list();
    QList<QStringList> get_comboBox_option_list(QVariantMap variantMap);
    QList<QStringList> get_translate_comboBox_option_list(QVariantMap variantMapEng, QVariantMap variantMapTran);
    QStringList get_abbreviate_comboBox_option_list(QStringList stringList);
    QString set_long_contents_header(int index, QString string);
    QVariantMap get_translate_option_map(QString thirdMenuString);
    QList<int> get_dialog_value_list(int index, QString str);
    QStringList get_third_menu_list();

    int m_width;
    int m_height;
    int m_currFirstNum;
    int m_currSecondNum;
    int m_measurementIndex;
    int m_inputIndex;
    int m_probeIndex;
    int m_wedgeIndex;
    int m_dateTimeSetIndex;
    int m_networkIndex;
    double m_brightness;
    double m_opacity;
    int m_languageOption;
    QString m_language;
    QVariantMap m_secondMenuMap;
    QString m_firstMenuString;
    QString m_secondMenuString;
    QString m_relatedMenuString;

signals:
    void retranslate_ui(QString);
    void translater_ZH();
    void translater_EN();
//    void send_string_to_delegate(QString);
    void opacityChanged(double value);

protected slots:
    void do_probe_event(const Probe& probe);

    void onHeaderClicked(int index);
    void change_related_third_menu_data(QString str);
    void set_header_text_create(QStringList stringList) const ;
    void set_header_text_close(QWidget *editor) ;
    void on_tableView_clicked(const QModelIndex &index);
    void change_measurement_label(QString string);
    void select_probe(QString string);
    void select_wedge(QString string);
    void set_edited_text(QString string);
    void setBrightness(double value);
    void set_autoDetect_probeModel(bool flag);
    void set_time(QString value);
    void set_ip_subNet(QString value);
    void retranslate_third_menu_ui(QString string);
//    void input_spinbox_number(QString string);
    void setOpacity(double value);

};

#endif // THIRDMENUWIDGET_H
