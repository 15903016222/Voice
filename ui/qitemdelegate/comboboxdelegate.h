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

    QList<QComboBox*> comboBoxList;

private:
    Mcu *m_mcu;

    int find_list_index(QStringList stringList, QString string) const;
    void set_comboBox_item_width(QComboBox *editor) const;

    QMap<QModelIndex, QComboBox*> m_comboBoxMap;
    QStringList m_itemList;
    QStringList m_modelItemList;
    int m_minimumContentLength;
    bool m_editFlag;

signals:
    void comboBox_current_text(QString);
    void change_language(QString);

private slots:
    void commit_and_close_editor(const QString &str);
    void do_rotary_event(Mcu::RotaryType type);
    void key_sure(Mcu::KeyType key);
};

#endif // COMBOBOXDELEGATE_H
