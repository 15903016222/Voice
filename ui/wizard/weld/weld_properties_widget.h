#ifndef WELD_PROPERTIES_WIDGET_H_
#define WELD_PROPERTIES_WIDGET_H_

#include <QWidget>
#include <QDoubleSpinBox>
#include <QMap>
#include <QString>

namespace Ui {
class WeldPropertiesWidget;
}

class WeldPropertiesWidget : public QWidget
{
    Q_OBJECT

#define MIN(a, b) (((a) < (b)) ? (a):(b))
#define MAX(a, b) (((a) > (b)) ? (a):(b))

public:
    explicit WeldPropertiesWidget(QWidget *parent = 0);
    ~WeldPropertiesWidget();

public slots:

    void set_weld_info(const QMap<QString, double> &valueList);

    void slot_max_W1(double value);
    void slot_max_W2(double value);
    void slot_max_W3(double value);
    void slot_min_H1(double value);
    void slot_min_H2(double value);
    void slot_min_R1(double value);
    void slot_min_R2(double value);

    void slot_min_X1(double value);
    void slot_max_Y1(double value);
    void slot_min_X2(double value);
    void slot_max_Y2(double value);
    void slot_min_angle(double value);
    void slot_max_angle(double value);

    void set_thickness(double value);

protected slots:

    void slot_weld_type_changed(int index);
    void slot_weld_info_changed(double value);

signals:
    void weld_info_changed(int type, const QMap<QString, double> &valueList);

private:
    Ui::WeldPropertiesWidget *ui;

    void show_item();
    void show_i_weld_item(QMap<QString, double> &valueList);
    void show_v_weld_item(QMap<QString, double> &valueList);
    void show_u_weld_item(QMap<QString, double> &valueList);
    void show_vy_weld_item(QMap<QString, double> &valueList);
    void show_vv_weld_item(QMap<QString, double> &valueList);
    void show_uu_weld_item(QMap<QString, double> &valueList);
    void show_uv_weld_item(QMap<QString, double> &valueList);
    void show_tky_weld_item(QMap<QString, double> &valueList);

    void reset_value();
    void set_value(const QMap<QString, double> &valueList);

    void check_vv_weld_properties_limit(const QDoubleSpinBox *current, double value);
    void check_u_weld_properties_limit(const QDoubleSpinBox *current, double value);

    double  m_thickness;

    QMap<QString, double> m_valueList;

};

#endif // WELD_PROPERTIES_WIDGET_H_
