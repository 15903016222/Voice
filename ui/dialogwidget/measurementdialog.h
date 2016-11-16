#ifndef MEASUREMENTDIALOG_H
#define MEASUREMENTDIALOG_H

#include "mcu.h"

#include <QDialog>
#include <QListView>
#include <QStandardItemModel>

namespace Ui {
class MeasurementDialog;
}

class MeasurementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MeasurementDialog(QWidget *parent = 0);
    ~MeasurementDialog();

    void set_current_index(QString string);

private:
    Ui::MeasurementDialog *ui;

    Mcu *pMcu;

    QList<QPushButton *> buttonList;
    QListView *pListView;
    QStandardItemModel *pMeasurementModel;

    void init_ui();

    QMap<QString, QString> labelMap;
    QStringList measurementList;
    QString m_changedString;
    bool m_changedFlag;
    int m_currentRow;

signals:
    void labelTextChanged(QString);

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();
    void slot_listViewItemClicked(QModelIndex index);

    void do_rotary_event(Mcu::RotaryType type);
    void key_sure(Mcu::KeyType key);

};

#endif // MEASUREMENTDIALOG_H
