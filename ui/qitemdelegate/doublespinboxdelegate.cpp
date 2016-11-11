#include "doublespinboxdelegate.h"

//#ifdef PC_WIN
//#include "windows.h"
//#endif

//#ifdef PC_UNIX
//#include  <linux/input.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <sys/time.h>
//#include <unistd.h>
//#endif

#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QLineEdit>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
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
    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(valueChanged_signal(double)));

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
        if(spinBoxList.size() != 0) {
            QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);

            if (type == Mcu::ROTARY_UP) {
                doubleSpinBox->stepUp();
            } else {
                doubleSpinBox->stepDown();
            }
            emit stringChanged(doubleSpinBox->value());
        }
    }
}

#include <QShortcut>
void DoubleSpinBoxDelegate::key_sure(Mcu::KeyType key)
{
    if(editFlag){
        if(spinBoxList.size() != 0) {
            if(key == Mcu::KEY_SURE) {
                QDoubleSpinBox *doubleSpinBox = spinBoxList.at(spinBoxList.count() - 1);
                QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
                QApplication::sendEvent(doubleSpinBox, event);
            }
        }
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
//    QLineEdit *lineEdit = new QLineEdit(doubleSpinBox);
//    doubleSpinBox->setLineEdit(lineEdit);
    doubleSpinBox->setFocusPolicy(Qt::StrongFocus);
    doubleSpinBox->setFocus();
//    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier);
//    QCoreApplication::sendEvent(doubleSpinBox, event);
//    QWidget *widget = doubleSpinBox->focusWidget();
//    HWND hwnd = (HWND)widget->winId();
//    qDebug() << "string" << string;
//    if(string == "." && decimalAmount > 0) {
//        SendMessage(hwnd, WM_KEYDOWN, VK_DECIMAL, 0);
//    } else if(string == "Left Arrow") {
//        SendMessage(hwnd, WM_KEYDOWN, VK_LEFT, 0);
//    } else if(string == "Right Arrow") {
//        SendMessage(hwnd, WM_KEYDOWN, VK_RIGHT, 0);
//    } else if(string == "BackSpace") {
//        SendMessage(hwnd, WM_KEYDOWN, VK_BACK, 0);
//    } else if(string == "Delete") {
//        SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 0);
//    } else if(string == "Enter" || string == "Close") {
//        SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
//    } else {
//        int value = string.toInt();
//        SendMessage(hwnd, WM_KEYDOWN, VK_HELP + value + 1, 0);
//    }
    
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

////    linux
//    int fd_kbd;
//    qDebug() << "open:" << fd_kbd;
//    fd_kbd = open("/dev/input/event1", O_RDWR);
//    if(fd_kbd <= 0) {
//        qDebug() << "Open keyboard failed.";
//    }

//    if(string == "." && decimalAmount > 0) {
////        PostMessage(hwnd, WM_KEYDOWN, VK_DECIMAL, 0);
//        simulate_key(fd_kbd, KEY_0);
//    } else if(string == "Left Arrow") {
//        simulate_key(fd_kbd, KEY_LEFT);
//    } else if(string == "Right Arrow") {
//        simulate_key(fd_kbd, KEY_RIGHT);
//    } else if(string == "BackSpace") {
//        simulate_key(fd_kbd, KEY_BACKSPACE);
//    } else if(string == "Delete") {
//        simulate_key(fd_kbd, KEY_DELETE);
//    } else if(string == "Enter" || string == "Close") {
//        simulate_key(fd_kbd, KEY_ENTER);
//    } else {
//        int value = string.toInt();
//        simulate_key(fd_kbd, KEY_0 + value);
//    }

    //    close(fd_kbd);
}

void DoubleSpinBoxDelegate::valueChanged_signal(double value)
{
    emit stringChanged(value);
}

//void DoubleSpinBoxDelegate::simulate_key(int fd, int value)
//{
//    struct input_event event;
//    qDebug() << value;
//    event.type = EV_KEY;
//    event.value = 1;
//    event.code = value;
//    gettimeofday(&event.time, 0);
//    write(fd, &event, sizeof(event));
//    qDebug() << "write:" << write(fd, &event, sizeof(event));
////    if(write(fd, &event, sizeof(event)) < 0) {
////        qDebug() << "write failed";
////    }
//}
