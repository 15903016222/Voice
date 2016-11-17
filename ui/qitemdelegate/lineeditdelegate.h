#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include "mcu.h"

#include <QStyledItemDelegate>
#include <QLineEdit>

class LineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    LineEditDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void set_number_range(QList<int> list);
    void set_number_step_list(QStringList stringList);
    void set_number_step(QString string);
    void set_decimal_amount(int amount);

    bool eventFilter(QObject *object, QEvent *event);
    QString get_number_step();

    QList<QLineEdit*> lineEditList;
    QStringList stepList;

    int m_inputCount;
    bool m_editFlag;
    int decimalAmount;
    bool m_keyboardFlag;

private:
    Mcu *m_mcu;

    QMap<QModelIndex, QLineEdit*> lineEditMap;
    QList<int> rangeList;

    QString step;


signals:
    void createEditorHeaderText(QStringList) const;
    void closeEditorHeaderText(QModelIndex) const;
    void stringChanged(double value);

private slots:
    void commit_and_close_editor();
    void do_rotary_event(Mcu::RotaryType type);
    void key_sure(Mcu::KeyType key);
    void valueChanged_signal(QString text);
};

#endif // LINEEDITDELEGATE_H
