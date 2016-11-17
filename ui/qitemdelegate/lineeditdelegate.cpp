#include "lineeditdelegate.h"

#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QLineEdit>
#include <QAbstractSpinBox>

//#define NUMBER_KEYBOARD_COUNT 10
//static const int NUMBER_KEYBOARD_STRING[NUMBER_KEYBOARD_COUNT] =
//{
//    Qt::Key_0, Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4,
//    Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8, Qt::Key_9
//};

LineEditDelegate::LineEditDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
    m_editFlag = false;
    m_inputCount = 0;
}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QDoubleValidator *validator = new QDoubleValidator;

    if(rangeList.at(0) == 0 && rangeList.at(1) == 0) {
        validator->setRange(0.00, 10000.00, decimalAmount);
    } else {
        validator->setRange(rangeList.at(0), rangeList.at(1), decimalAmount);
    }

    editor->setValidator(validator);

//    editor->setSingleStep(step.toFloat());
    editor->installEventFilter(parent);
    editor->setReadOnly(false);

    (const_cast<LineEditDelegate *>(this))->lineEditList.append(editor);
    (const_cast<LineEditDelegate *>(this))->lineEditMap.insert(index, editor);
    (const_cast<LineEditDelegate *>(this))->m_editFlag = true;
    qDebug() << "m_editflag";
    QStringList sendList;
    sendList.append(QString::number(index.column()));
    sendList.append(step);

    emit createEditorHeaderText(sendList);
    connect(editor, SIGNAL(editingFinished()), this, SLOT(commit_and_close_editor()));
//    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(valueChanged_signal(double)));
    connect(editor, SIGNAL(textChanged(QString)), this, SLOT(valueChanged_signal(QString)));

    return editor;
    Q_UNUSED(option);
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//    double value;
//    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
//    QString string = index.model()->data(index, Qt::EditRole).toString();
//    if(string.contains("(")) {
//        QString number = string.mid(1, string.length() - 2);
//        value = number.toDouble();
//    } else {
//        value = index.model()->data(index, Qt::EditRole).toDouble();
//    }
//    lineEdit->setValue(value);
    QString value;
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString string = index.model()->data(index, Qt::EditRole).toString();
    if(string.contains("(")) {
        value = string.mid(1, string.length() - 2);

    } else {
        value = index.model()->data(index, Qt::EditRole).toString();
    }
    lineEdit->setText(value);
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
//    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
//    lineEdit->interpretText();
//    double value = lineEdit->value();
//    if(lineEdit->suffix() != NULL && lineEdit->prefix() != NULL) {
//        model->setData(index, "(" + QString::number(value, 'f', decimalAmount) + ")", Qt::EditRole);
//    } else {
//        model->setData(index, QString::number(value, 'f', decimalAmount), Qt::EditRole);
//    }
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
//    lineEdit->interpretText();
    QString value = lineEdit->text();
//    if(lineEdit->suffix() != NULL && lineEdit->prefix() != NULL) {
//        model->setData(index, "(" + QString::number(value, 'f', decimalAmount) + ")", Qt::EditRole);
//    } else {
        model->setData(index, QString::number(value.toDouble(), 'f', decimalAmount), Qt::EditRole);
//    }
}

void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

bool LineEditDelegate::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *e = (QKeyEvent*)event;
        QLineEdit *editor = qobject_cast<QLineEdit*>(object);
        QString value = editor->text();
        int cursorPosition = editor->cursorPosition();
        editor->setEnabled(true);
        editor->setFocus();
        if(e->key() == Qt::Key_Backspace) {

        } else if(e->key() == Qt::Key_Delete) {

        } else if(e->key() == Qt::Key_Left) {
//            editor->cursorForward(true, 1);
            editor->setCursorPosition(cursorPosition - 1);
        } else if(e->key() == Qt::Key_Right) {
//            editor->cursorBackward(true, 1);
            editor->setCursorPosition(cursorPosition + 1);
        } else if(e->key() == Qt::Key_Return) {
            emit editor->returnPressed();
            editor->clearFocus();
        } else if(e->key() == Qt::Key_Period) {
            editor->insert(".");
        } else if(e->key() >= 48 && e->key() <= 57) {
            if(m_inputCount == 0) {
                editor->insert(QString::number(e->key() - 48));
            } else {
                QString newString = value + QString::number(e->key() - 48);
                const QDoubleValidator *validator = (QDoubleValidator*)(editor->validator());
                if(newString.toDouble() <= validator->top()) {
                    editor->insert(QString::number(e->key() - 48));
                }
            }
            m_inputCount += 1;
        } else if(e->key() == Qt::Key_Up) {
            double newValue = value.toDouble() + step.toDouble();
            const QDoubleValidator *validator = (QDoubleValidator*)(editor->validator());
            if(newValue <= validator->top()) {
                editor->setText(QString::number(newValue, 'f', decimalAmount));
            }
        } else if(e->key() == Qt::Key_Down) {
            double newValue = value.toDouble() - step.toDouble();
            const QDoubleValidator *validator = (QDoubleValidator*)(editor->validator());
            if(newValue >= validator->bottom()) {
                editor->setText(QString::number(newValue, 'f', decimalAmount));
            }
        } else {
            return false;
        }
    }
    return QObject::eventFilter(object, event);
}

void LineEditDelegate::set_number_range(QList<int> list)
{
    rangeList = list;
}

void LineEditDelegate::set_number_step_list(QStringList stringList)
{
    stepList = stringList;
}

void LineEditDelegate::set_number_step(QString string)
{
    step = string;
    if(lineEditList.size() != 0) {
//        QLineEdit *lineEdit = lineEditList.at(lineEditList.count() - 1);
//        lineEdit->setSingleStep(string.toFloat());
    }
}

QString LineEditDelegate::get_number_step()
{
    return step;
}

void LineEditDelegate::set_decimal_amount(int amount)
{
    decimalAmount = amount;
}

void LineEditDelegate::commit_and_close_editor()
{
    QLineEdit *editor = qobject_cast<QLineEdit*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
    m_editFlag = false;
}

void LineEditDelegate::do_rotary_event(Mcu::RotaryType type)
{
    if(m_editFlag) {
        QLineEdit *lineEdit = lineEditList.at(lineEditList.count() - 1);
        if (type == Mcu::ROTARY_UP) {
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
            QApplication::sendEvent(lineEdit, event);
        } else {
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
            QApplication::sendEvent(lineEdit, event);
        }
    }
}

void LineEditDelegate::key_sure(Mcu::KeyType key)
{
    if(m_editFlag) {
        if(key == Mcu::KEY_SURE) {
            QLineEdit *lineEdit = lineEditList.at(lineEditList.count() - 1);
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
            QApplication::sendEvent(lineEdit, event);
        }
    }
}

void LineEditDelegate::valueChanged_signal(QString text)
{
    emit stringChanged(text.toDouble());
}

