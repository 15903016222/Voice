#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include <QItemDelegate>
#include <QWidget>
#include <QDoubleSpinBox>

class DoubleSpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    DoubleSpinBoxDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void set_number_range(QList<int> list);
    void set_number_step_list(QStringList stringList);
    void set_number_step(QString string);
    QString get_number_step();
    void set_decimal_amount(int amount);
    QList<QDoubleSpinBox*> spinBoxList;

    QList<int> rangeList;
    QStringList stepList;
    QString step;
    int decimalAmount;

signals:
    void editorHeaderText(QStringList);

private slots:
    void commit_and_close_editor();
};

#endif // DOUBLESPINBOXDELEGATE_H
