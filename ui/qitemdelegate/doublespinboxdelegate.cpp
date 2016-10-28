#include "doublespinboxdelegate.h"

#include "windows.h"

#include <QEvent>
#include <QDebug>
#include <QKeyEvent>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(m_mcu, SIGNAL(key_event(int)), this, SLOT(key_sure(int)));
    editFlag = false;
    inputCount = 0;
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
    editor->setSingleStep(step.toFloat());
    editor->setDecimals(decimalAmount);
    editor->installEventFilter(parent);

    (const_cast<DoubleSpinBoxDelegate *>(this))->spinBoxList.append(editor);
    (const_cast<DoubleSpinBoxDelegate *>(this))->spinBoxMap.insert(index, editor);
    (const_cast<DoubleSpinBoxDelegate *>(this))->editFlag = true;
    QStringList sendList;
    sendList.append(QString::number(index.column()));
    sendList.append(step);

    emit createEditorHeaderText(sendList);
    connect(editor, SIGNAL(editingFinished()), this, SLOT(commit_and_close_editor()));

    return editor;
    Q_UNUSED(option);
}

void DoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index,Qt::EditRole).toDouble();
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->setValue(value);
}

void DoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->interpretText();
    double value = doubleSpinBox->value();
    model->setData(index, QString::number(value, 'f', decimalAmount), Qt::EditRole);
}

void DoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

bool DoubleSpinBoxDelegate::eventFilter(QObject *object, QEvent *event)
{
    QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
    if(event->type() == QEvent::KeyPress && object == doubleSpinBox) {
        doubleSpinBox->setFocus();
        QKeyEvent *e = (QKeyEvent*)event;
        if(e->key() == Qt::Key_1) {
            qDebug() << "eventFilter:" << "key1";

//            double newValue;
//            QString string = "1";
//            const QModelIndex &index = spinBoxMap.key(doubleSpinBox);

//            if(inputCount == 0) {
//                doubleSpinBox->cleanText();
//                newValue = string.toInt();

//            } else {
//                double value = doubleSpinBox->value();
//                QString addedString = QString::number(value, 10, decimalAmount) + string;
//                newValue = addedString.toDouble();
//            }

//            if(newValue > doubleSpinBox->maximum()) {
//                const_cast<QAbstractItemModel*>(index.model())->setData(index, QString::number(doubleSpinBox->maximum(), 'f', decimalAmount), Qt::EditRole);
//                doubleSpinBox->setValue(doubleSpinBox->maximum());
//            } else if(newValue < doubleSpinBox->minimum()) {
//                const_cast<QAbstractItemModel*>(index.model())->setData(index, QString::number(doubleSpinBox->minimum(), 'f', decimalAmount), Qt::EditRole);
//                doubleSpinBox->setValue(doubleSpinBox->minimum());
//            } else {
//                const_cast<QAbstractItemModel*>(index.model())->setData(index, QString::number(newValue, 'f', decimalAmount), Qt::EditRole);
//                doubleSpinBox->setValue(newValue);
//            }
        }

    }
    return QObject::eventFilter(object, event);
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
    step = string;
    if(spinBoxList.size() != 0) {
        QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
        doubleSpinBox->setSingleStep(string.toFloat());
    }
}

QString DoubleSpinBoxDelegate::get_number_step()
{
    return step;
}

void DoubleSpinBoxDelegate::set_decimal_amount(int amount)
{
    decimalAmount = amount;
}

void DoubleSpinBoxDelegate::commit_and_close_editor()
{
    QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
    editFlag = false;
}

void DoubleSpinBoxDelegate::do_rotary_event(Mcu::RotaryType type)
{
    if(spinBoxList.size() != 0) {
        QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
//        double value = doubleSpinBox->value();

        if (type == Mcu::ROTARY_UP) {
//            value = value + 1;
            doubleSpinBox->stepUp();
        } else {
//            value = value - 1;
            doubleSpinBox->stepDown();
        }
//        doubleSpinBox->setValue(value);
    }
}

#include <QShortcut>
void DoubleSpinBoxDelegate::key_sure(int key)
{
    if(key == 214) {
        if(spinBoxList.size() != 0) {
            QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
//            connect(doubleSpinBox, SIGNAL(editingFinished()), this, SLOT(editFinished()));
            emit doubleSpinBox->editingFinished();
        }
      //  QShortcut *key_return = new QShortcut(QKeySequence(Qt::Key_Return), doubleSpinBox);
      //  connect(key_return, SIGNAL(activated()), this, SLOT());
    }
}

void DoubleSpinBoxDelegate::editFinished()
{

}

void DoubleSpinBoxDelegate::input_number_to_lineedit(QString string)
{
//    double newValue;
    QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
//    const QModelIndex &index = spinBoxMap.key(doubleSpinBox);

    doubleSpinBox->setFocusPolicy(Qt::StrongFocus);
    doubleSpinBox->setFocus();
    QWidget *widget = doubleSpinBox->focusWidget();
    HWND hwnd = (HWND)widget->winId();

    if(string == "." && decimalAmount > 0) {
        PostMessage(hwnd, WM_KEYDOWN, VK_DECIMAL, 0);
    } else if(string == "Left Arrow") {
        PostMessage(hwnd, WM_KEYDOWN, VK_LEFT, 0);
    } else if(string == "Right Arrow") {
        PostMessage(hwnd, WM_KEYDOWN, VK_RIGHT, 0);
    } else if(string == "BackSpace") {
        PostMessage(hwnd, WM_KEYDOWN, VK_BACK, 0);
    } else if(string == "Delete") {
        PostMessage(hwnd, WM_KEYDOWN, VK_DELETE, 0);
    } else if(string == "Enter" || string == "Close") {
        PostMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
    } else {
        int value = string.toInt();
        PostMessage(hwnd, WM_KEYDOWN, VK_HELP + value + 1, 0);
    }
//    PostMessage(hwnd, WM_KEYUP, VK_HELP + value + 1, 0);

//    if(inputCount == 0) {
//        doubleSpinBox->cleanText();
//        newValue = string.toInt();

//    } else {
//        double value = doubleSpinBox->value();
//        QString addedString = QString::number(value, 10, decimalAmount) + string;
//        newValue = addedString.toDouble();
//    }
//    newValue = doubleSpinBox->value();

//    if(newValue > doubleSpinBox->maximum()) {
//        const_cast<QAbstractItemModel*>(index.model())->setData(index, QString::number(doubleSpinBox->maximum(), 'f', decimalAmount), Qt::EditRole);
//        doubleSpinBox->setValue(doubleSpinBox->maximum());
//    } else if(newValue < doubleSpinBox->minimum()) {
//        const_cast<QAbstractItemModel*>(index.model())->setData(index, QString::number(doubleSpinBox->minimum(), 'f', decimalAmount), Qt::EditRole);
//        doubleSpinBox->setValue(doubleSpinBox->minimum());
//    } else {
//        const_cast<QAbstractItemModel*>(index.model())->setData(index, QString::number(newValue, 'f', decimalAmount), Qt::EditRole);
//        doubleSpinBox->setValue(newValue);
//    }

}

