#ifndef DELEGATEMODEL_H
#define DELEGATEMODEL_H

#include <QStandardItemModel>

class DelegateModel:public QStandardItemModel
{
    Q_OBJECT

public:
    DelegateModel(QObject *parent=0):QStandardItemModel(parent){}
    DelegateModel(int row, int column,QObject *parent=NULL)
        :QStandardItemModel(row,column,parent){}
    QVariant data(const QModelIndex &index, int role) const
    {
        if(Qt::TextAlignmentRole==role)
            return Qt::AlignCenter;
        return QStandardItemModel::data(index,role);
    }
};


#endif // DELEGATEMODEL_H
