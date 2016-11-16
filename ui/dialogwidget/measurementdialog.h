#ifndef MEASUREMENTDIALOG_H
#define MEASUREMENTDIALOG_H

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

private:
    Ui::MeasurementDialog *ui;

    QList<QPushButton *> buttonList;
    QListView *pListView;
    QStandardItemModel *pMeasurementModel;

    void init_ui();

    QMap<QString, QString> labelMap;
    QStringList measurementList;
    QString m_changedString;
    bool m_changedFlag;

signals:
    void labelTextChanged(QString);

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();
    void slot_listViewItemClicked(QModelIndex index);
    void set_current_index(QString string);

};

#endif // MEASUREMENTDIALOG_H
