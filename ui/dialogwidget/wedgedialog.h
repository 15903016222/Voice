#ifndef WEDGEDIALOG_H
#define WEDGEDIALOG_H

#include <QDialog>
#include <QListView>
#include <QStandardItemModel>

#define WEDGETYPE_NUMBER 22

namespace Ui {
class WedgeDialog;
}

class WedgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WedgeDialog(QWidget *parent = 0);
    ~WedgeDialog();

private:
    Ui::WedgeDialog *ui;
    void initUI();

public:
    QListView *listView_1;
    QListView *listView_2;
    QStandardItemModel *wedgeTypeModel;
    QStandardItemModel *wedgeModel;
    QList<QStandardItemModel*> wedgeModelList;

    void insertWedge(int i);
    int listView_1CurrentIndex;
    int listView_2CurrentIndex;

private slots:
    void slot_listView_1ItemClicked(QModelIndex index);
    void slot_listView_2ItemClicked(QModelIndex index);

};

#endif // WEDGEDIALOG_H
