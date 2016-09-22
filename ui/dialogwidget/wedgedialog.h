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
  //  QList<QPushButton *> buttonList;
    QListView *listView_1;
    QListView *listView_2;

   // QStringList wedgeTypeList;
    QStandardItemModel *wedgeTypeModel;
    QStandardItemModel *wedgeModel;
    QList<QStandardItemModel*> wedgeModelList;
//    QMap<QString, QString> labelMap;
//    QString changedString;
    void insertWedge(int i);
    int currentIndex;

private slots:
//    void on_pushButton_cancel_clicked();
//    void on_pushButton_ok_clicked();
    void slot_listViewItemClicked(QModelIndex index);
};

#endif // WEDGEDIALOG_H
