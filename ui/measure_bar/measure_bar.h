#ifndef __MEASURE_BAR_H__
#define __MEASURE_BAR_H__

#include "measure_dialog.h"

#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>

#define TOP_MENU_NUMBER 10

namespace Ui {
class MeasureBar;
}

class MeasureBar : public QWidget
{
    Q_OBJECT

public:
    explicit MeasureBar(QWidget *parent = 0);
    ~MeasureBar();

    void retranslate_top_menu_ui();
    void set_top_menu_font();

signals:
    void currentDialogIndex(QString);

private slots:
    void set_angle_header_text_close(QWidget *editor);
    void on_tableView_angle_clicked(const QModelIndex &index);

private:
    Ui::MeasureBar *ui;

    void init_ui();
    void init_gain_angle();
    void open_editor_and_set_header_text(QLabel *label, QTableView *tableView, QStandardItemModel *model, int index);
    void set_header_text_close(QLabel *label);

    QStringList get_label_text(QString string);

    QList<QLabel* > measurementLabelList;
    QStandardItemModel *pAngle;
    QString objectName;
};

#endif // __MEASURE_BAR_H__

