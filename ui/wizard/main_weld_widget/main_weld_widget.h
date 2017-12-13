#ifndef __MAIN_WELD_WIDGET_H__
#define __MAIN_WELD_WIDGET_H__

#include <QWidget>
#include <QDebug>

namespace Ui {
class MainWeldWidget;
}

namespace DplWeld {

class BaseWeldWidget;
class BaseWeldInformation;
class WeldWidgetFactory;
class WeldInformationFactory;

}


class MainWeldWidget : public QWidget
{
    Q_OBJECT

    struct S_RulerSize
    {
        double defaultSize;
        double currentSize;
    };

public:
    explicit MainWeldWidget(QWidget *parent = 0);
    ~MainWeldWidget();

    void set_thickness(double value);

    QSharedPointer<DplWeld::BaseWeldInformation> get_weld_information();

    void show_widget(int weldType, double thickness);

private slots:
    void do_weldProperties_weld_info_changed(int type, const QMap<QString, double> &valueList);
    void do_btn_clicked();

private:
    Ui::MainWeldWidget *ui;

    void init();
    void append_value(int type, QMap<QString, double> &valueList);
    void append_value_tky(int type, QMap<QString, double> &valueList);
    void append_value_other(int type, QMap<QString, double> &valueList);

    void config_ruler();
    void connect_signals(int type);
    void set_default_value(int weldType, QMap<QString, double> &valueList);

    DplWeld::BaseWeldWidget                        *m_pbaseWeldWidget;
    QSharedPointer<DplWeld::BaseWeldInformation>    m_pbaseWeldInformation;

    S_RulerSize m_horizontalSize;
    S_RulerSize m_verticalSize;

protected:
    bool event(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

};

#endif // __MAIN_WELD_WIDGET_H__
