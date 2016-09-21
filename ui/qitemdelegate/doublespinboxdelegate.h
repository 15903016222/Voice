#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include <QItemDelegate>
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
    void set_decimal_amount(int amount);
    QString get_number_step();

    QList<QDoubleSpinBox*> spinBoxList;
    QList<int> rangeList;
    QStringList stepList;
    QString step;
    int decimalAmount;

signals:
    void createEditorHeaderText(QStringList) const;
    void closeEditorHeaderText(QModelIndex) const;

private slots:
    void commit_and_close_editor();
};

#endif // DOUBLESPINBOXDELEGATE_H
