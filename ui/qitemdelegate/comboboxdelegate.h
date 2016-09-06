#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QWidget>
#include <QStringList>

class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ComboBoxDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index)const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)const;

    void set_comboBox_item_list(QStringList stringList);
    void set_model_item_list(QStringList stringList);
    int find_list_index(QStringList stringList, QString string) const;

    QStringList itemList;
    QStringList modelItemList;
};

#endif // COMBOBOXDELEGATE_H
