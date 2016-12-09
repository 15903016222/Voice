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

    QString get_current_item_text();

private:
    Ui::ProbeDialog *ui;

    QListView *pListView_1;
    QListView *pListView_2;
    QStandardItemModel *probeTypeModel;
    QStandardItemModel *probeModel;
    QList<QStandardItemModel*> probeModelList;

    void init_ui();
    void insert_probe(int i);

    int listView_1CurrentIndex;
    int listView_2CurrentIndex;

    QString m_currentItem;

signals:
    void probeChanged(QString);

private slots:
    void slot_listView_1ItemClicked(QModelIndex index);
    void slot_listView_2ItemClicked(QModelIndex index);
    void on_buttonBox_accepted();
};

#endif // PROBEDIALOG_H
