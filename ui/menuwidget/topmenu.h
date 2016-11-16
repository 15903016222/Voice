#ifndef TOPMENU
#define TOPMENU

#include "measurementdialog.h"

#include <QLabel>
#include <QTableView>

#define TOP_MENU_NUMBER 10

namespace Ui {
class TopMenu;
}

class TopMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TopMenu(QWidget *parent = 0);
    ~TopMenu();

    void retranslate_top_menu_ui();
    void set_top_menu_font();

    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::TopMenu *ui;

    void init_ui();
    void init_gain_angle();
    void open_editor_and_set_header_text(QLabel *label, QTableView *tableView, QStandardItemModel *model, int index);
    void set_header_text_close(QLabel *label);

    QStringList get_label_text(QString string);

    QList<QLabel* > measurementLabelList;
    QStandardItemModel *pGain;
    QStandardItemModel *pAngle;
    MeasurementDialog *pDialog;
    QString objectName;

private slots:
    void change_labelText(QString str);
    void set_gain_header_text_close(QWidget *editor);
    void set_angle_header_text_close(QWidget *editor);
    void on_tableView_angle_clicked(const QModelIndex &index);
    void on_tableView_gain_clicked(const QModelIndex &index);
};

#endif // TOPMENU

