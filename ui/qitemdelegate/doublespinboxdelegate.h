#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include "mcu.h"

#include <QStyledItemDelegate>
#include <QDoubleSpinBox>

class DoubleSpinBoxDelegate : public QStyledItemDelegate
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
    QStringList stepList;

    int m_inputCount;
    bool m_editFlag;


private:
    Mcu *m_mcu;

    QMap<QModelIndex, QDoubleSpinBox*> spinBoxMap;
    QList<int> rangeList;
      
    QString step;
    int decimalAmount;

signals:
    void createEditorHeaderText(QStringList) const;
    void closeEditorHeaderText(QModelIndex) const;
    void stringChanged(double value);

private slots:
    void commit_and_close_editor();
    void do_rotary_event(Mcu::RotaryType type);
    void key_sure(Mcu::KeyType key);
    void input_number_to_lineedit(QString string);
    void valueChanged_signal(double value);
};

#endif // DOUBLESPINBOXDELEGATE_H
