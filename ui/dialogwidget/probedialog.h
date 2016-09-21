#ifndef PROBEDIALOG_H
#define PROBEDIALOG_H

#include <QDialog>
#include <QListView>
#include <QStandardItemModel>

#define PROBETYPE_NUMBER 24

namespace Ui {
class ProbeDialog;
}

class ProbeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProbeDialog(QWidget *parent = 0);
    ~ProbeDialog();

private:
    Ui::ProbeDialog *ui;
    void initUI();

public:
  //  QList<QPushButton *> buttonList;
  //  QList<QListView*> listView_1;
    QListView *listView_1;
    QListView *listView_2;
    QStringList probeTypeList;
    QStringList probeList;
    QStandardItemModel *probeTypeModel;
    QStandardItemModel *probeModel;
    QMap<QString, QString> labelMap;
    QString changedString;

    void insertProbe(int i);
    int currentIndex;

private slots:
//    void on_pushButton_cancel_clicked();
//    void on_pushButton_ok_clicked();
    void slot_listViewItemClicked(QModelIndex index);
};

#endif // PROBEDIALOG_H
