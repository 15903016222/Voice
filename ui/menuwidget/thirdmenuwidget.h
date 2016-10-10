#ifndef THIRDMENUWIDGET_H
#define THIRDMENUWIDGET_H

#include "firstsecondmenuwidget.h"
#include "verticalsliderdialog.h"

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

private:
    Ui::ThirdMenuWidget *ui;

public:
    void retranslate_third_menu_ui();
    void init_standard_model();
    void set_third_menu_name(int i, int j);
    void choose_widget_style(int k);
    void resizeEvent(QResizeEvent *event);
    void set_model_item(int startIndex, int count);

    QStringList get_third_menu_list();
    QVariantMap read_json_file(QString string);
    QVariantMap get_sub_menu_map(QVariantMap variantMap, QString thirdMenuString, QString subString);
    QList<int> get_spinBox_range_list(QVariantMap variantMap);
    QStringList get_spinBox_step_list(QVariantMap variantMap, QString thirdMenuString);
    QList<QStringList> get_comboBox_option_list(QVariantMap variantMap, QString thirdMenuString);
    QString set_long_contents_header(int index, QString string);

    int width;
    int height;
    int currFirstNum;
    int currSecondNum;
    int measurementIndex;
    int inputIndex;
    int brightIndex;
    int probeIndex;
    int wedgeIndex;

    QStandardItemModel *model;
    FirstSecondMenuWidget *widget;
    QVariantMap thirdMenuMap;
    QVariantMap fourthMenuMap;
    QVariantMap menuCacheMap;
    QString firstMenuString;
    QString secondMenuString;
    QString relatedMenuString;


private:
    VerticalSliderDialog *verticalSliderDialog;
    Mcu *m_mcu;

protected slots:
    void do_rotary_event(Mcu::RotaryType type);
    void do_probe_event(const Probe& probe);

private slots:
    void onHeaderClicked(int index);
    void change_related_third_menu_data(QString string);
    void set_header_text_create(QStringList stringList) const ;
    void set_header_text_close(QWidget *editor) ;
    void on_tableView_clicked(const QModelIndex &index);
    void change_measurement_label(QString string);
    void select_probe(QString string);
    void select_wedge(QString string);
    void set_edited_text(QString string);
    void setBrightValue(int value);
    void set_autoDetect_probeModel(bool flag);

};

#endif // THIRDMENUWIDGET_H
