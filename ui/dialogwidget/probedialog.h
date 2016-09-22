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
    QListView *listView_1;
    QListView *listView_2;
    QStandardItemModel *probeTypeModel;
    QStandardItemModel *probeModel;
    QList<QStandardItemModel*> probeModelList;

    void insertProbe(int i);
    int currentIndex;

private slots:
    void slot_listViewItemClicked(QModelIndex index);
};

#endif // PROBEDIALOG_H
