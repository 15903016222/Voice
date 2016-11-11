#include "doublespinboxdelegate.h"

#ifdef Q_OS_WIN32
#include "windows.h"
#endif

#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QLineEdit>
#include <QAbstractSpinBox>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
    editFlag = false;
    keyboardShowFlag = false;
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
    editor->setReadOnly(false);

    (const_cast<DoubleSpinBoxDelegate *>(this))->spinBoxList.append(editor);
    (const_cast<DoubleSpinBoxDelegate *>(this))->spinBoxMap.insert(index, editor);
    (const_cast<DoubleSpinBoxDelegate *>(this))->editFlag = true;
    QStringList sendList;
    sendList.append(QString::number(index.column()));
    sendList.append(step);

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
        model->setData(index, "(" + QString::number(value, 'f', decimalAmount) + ")", Qt::EditRole);
    } else {
        model->setData(index, QString::number(value, 'f', decimalAmount), Qt::EditRole);
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
    if(editFlag) {
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
    if(editFlag) {
        if(key == Mcu::KEY_SURE) {
            QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
            QApplication::sendEvent(doubleSpinBox, event);
        }
    }
}

#ifdef Q_OS_LINUX
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/XInput.h>
#include <X11/keysym.h>
#endif

void DoubleSpinBoxDelegate::input_number_to_lineedit(QString string)
{

    QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);

    doubleSpinBox->setFocusPolicy(Qt::StrongFocus);
    doubleSpinBox->setFocus();

#ifdef Q_OS_WIN32
    QWidget *widget = doubleSpinBox->focusWidget();
    HWND hwnd = (HWND)widget->winId();
    qDebug() << "string" << string;
    if(string == "." && decimalAmount > 0) {
        SendMessage(hwnd, WM_KEYDOWN, VK_DECIMAL, 0);
    } else if(string == "Left Arrow") {
        SendMessage(hwnd, WM_KEYDOWN, VK_LEFT, 0);
    } else if(string == "Right Arrow") {
        SendMessage(hwnd, WM_KEYDOWN, VK_RIGHT, 0);
    } else if(string == "BackSpace") {
        SendMessage(hwnd, WM_KEYDOWN, VK_BACK, 0);
    } else if(string == "Delete") {
        SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 0);
    } else if(string == "Enter" || string == "Close") {
        SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
    } else {
        int value = string.toInt();
        SendMessage(hwnd, WM_KEYDOWN, VK_HELP + value + 1, 0);
    }
#endif

#ifdef Q_OS_LINUX
    Display *display = XOpenDisplay (NULL);
    KeySym keysym;
    if(string == "." && decimalAmount > 0) {
        keysym = XK_KP_Decimal;
    } else if(string == "Left Arrow") {
        keysym = XK_Left;
    } else if(string == "Right Arrow") {
        keysym = XK_Right;
    } else if(string == "BackSpace") {
        keysym = XK_BackSpace;
    } else if(string == "Delete") {
        keysym = XK_Delete;
    } else if(string == "Enter" || string == "Close") {
        keysym = XK_Return;
    } else {
        int value = string.toInt();
        keysym = XK_0 + value;
    }

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, keysym), True, CurrentTime);
    XTestFakeKeyEvent(display, XKeysymToKeycode(display, keysym), False, CurrentTime);
    XCloseDisplay(display);
#endif

}

void DoubleSpinBoxDelegate::valueChanged_signal(double value)
{
    emit stringChanged(value);
}

