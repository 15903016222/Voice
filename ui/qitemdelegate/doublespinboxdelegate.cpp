#include "doublespinboxdelegate.h"

#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));

    m_editFlag = false;
}

QWidget *DoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    if(rangeList.at(0) == 0 && rangeList.at(1) == 0) {
        editor->setMinimum(0.00);
        editor->setMaximum(10000.00);
    } else {
        editor->setMinimum(rangeList.at(0));
        editor->setMaximum(rangeList.at(1));
    }
    editor->setSingleStep(m_step.toFloat());
    editor->setDecimals(m_decimalAmount);
    editor->installEventFilter(parent);
    editor->setReadOnly(false);

    (const_cast<DoubleSpinBoxDelegate *>(this))->spinBoxList.append(editor);
    (const_cast<DoubleSpinBoxDelegate *>(this))->spinBoxMap.insert(index, editor);
    (const_cast<DoubleSpinBoxDelegate *>(this))->m_editFlag = true;
    QStringList sendList;
    sendList.append(QString::number(index.column()));
    sendList.append(m_step);

    emit createEditorHeaderText(sendList);
    connect(editor, SIGNAL(editingFinished()), this, SLOT(commit_and_close_editor()));
    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(valueChanged_signal(double)));

    return editor;
    Q_UNUSED(option);
}

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value;
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    QString string = index.model()->data(index, Qt::EditRole).toString();
    if(string.contains("(")) {
        QString number = string.mid(1, string.length() - 2);
        value = number.toDouble();
    } else {
        value = index.model()->data(index, Qt::EditRole).toDouble();
    }
    doubleSpinBox->setValue(value);
}

void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->interpretText();
    double value = doubleSpinBox->value();
    if(doubleSpinBox->suffix() != NULL && doubleSpinBox->prefix() != NULL) {
        model->setData(index, "(" + QString::number(value, 'f', m_decimalAmount) + ")", Qt::EditRole);
    } else {
        model->setData(index, QString::number(value, 'f', m_decimalAmount), Qt::EditRole);
    }
}

void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void DoubleSpinBoxDelegate::set_number_range(QList<int> list)
{
    rangeList = list;
}

void DoubleSpinBoxDelegate::set_number_step_list(QStringList stringList)
{
    stepList = stringList;
}

void DoubleSpinBoxDelegate::set_number_step(QString string)
{
    m_step = string;
    if(spinBoxList.size() != 0) {
        QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
        doubleSpinBox->setSingleStep(string.toFloat());
    }
}

QString DoubleSpinBoxDelegate::get_number_step()
{
    return m_step;
}

void DoubleSpinBoxDelegate::set_decimal_amount(int amount)
{
    m_decimalAmount = amount;
}

void DoubleSpinBoxDelegate::commit_and_close_editor()
{
    QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
    m_editFlag = false;
}

void DoubleSpinBoxDelegate::do_rotary_event(Mcu::RotaryType type)
{
    if(m_editFlag) {
        QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
        if (type == Mcu::ROTARY_UP) {
            doubleSpinBox->stepUp();
        } else {
            doubleSpinBox->stepDown();
        }
    }
}

void DoubleSpinBoxDelegate::key_sure(Mcu::KeyType key)
{
    if(m_editFlag) {
        if(key == Mcu::KEY_SURE) {
            QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
            QApplication::sendEvent(doubleSpinBox, event);
        }
    }
}

void DoubleSpinBoxDelegate::valueChanged_signal(double value)
{
    emit stringChanged(value);
}

