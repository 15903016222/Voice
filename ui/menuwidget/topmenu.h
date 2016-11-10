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

private:
    Ui::TopMenu *ui;

public:
    QList<QLabel* > measurementLabelList;
//    QStandardItemModel *model;
    QStandardItemModel *model_gain;
    QStandardItemModel *model_angle;
    MeasurementDialog *mDialog;
    QString objectName;

    void retranslate_top_menu_ui();
    void init_ui();
    void set_top_menu_font();
    void init_gain_angle();
    QStringList get_label_text(QString string);
    void open_editor_and_set_header_text(QLabel *label, QTableView *tableView, QStandardItemModel *model, int index);

    bool eventFilter(QObject *object, QEvent *event);

signals:
    void currentDialogIndex(QString);

private slots:
    void changeLabelText(QString str);

    void on_tableView_angle_clicked(const QModelIndex &index);
};

#endif // TOPMENU

