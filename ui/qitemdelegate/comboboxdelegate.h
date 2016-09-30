#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include "mcu.h"

#include <QComboBox>
#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
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
    void set_minimum_contents_length(int width);
    int find_list_index(QStringList stringList, QString string) const;

    QList<QComboBox*> comboBoxList;
    QStringList itemList;
    QStringList modelItemList;
    int minimumContentLength;
    bool editFlag;

private:
    Mcu *m_mcu;

signals:
    void comboBox_current_text(QString);

private slots:
    void commit_and_close_editor(const QString &str);
    void do_rotary_event(Mcu::RotaryType type);
};

#endif // COMBOBOXDELEGATE_H
