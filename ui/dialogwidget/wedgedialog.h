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
    void init_ui();

public:
    QListView *listView_1;
    QListView *listView_2;
    QStandardItemModel *wedgeTypeModel;
    QStandardItemModel *wedgeModel;
    QList<QStandardItemModel*> wedgeModelList;

    void insert_wedge(int i);
    int currentIndex;

private slots:
    void slot_listViewItemClicked(QModelIndex index);
};

#endif // WEDGEDIALOG_H
