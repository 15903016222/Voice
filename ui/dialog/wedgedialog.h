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

    QListView *pListView_1;
    QListView *pListView_2;
    QStandardItemModel *pWedgeTypeModel;
    QStandardItemModel *pWedgeModel;
    QList<QStandardItemModel*> pWedgeModelList;

    void init_ui();
    void insert_wedge(int i);
    int listView_1CurrentIndex;
    int listView_2CurrentIndex;
    QString m_currentItem;

signals:
    void wedgeChanged(QString);

private slots:
    void slot_listView_1ItemClicked(QModelIndex index);
    void slot_listView_2ItemClicked(QModelIndex index);
    void on_buttonBox_accepted();
};

#endif // WEDGEDIALOG_H
