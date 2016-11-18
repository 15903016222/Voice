#include "virtualkeyboard.h"
#include "ui_virtualkeyboard.h"

#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>

VirtualKeyboard::VirtualKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualKeyboard)
{
    ui->setupUi(this);

    for(int i = 0; i < 10; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("panelButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(do_click_button()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

    for(int i = 1; i < 6; i ++) {
        QPushButton *pushButton = findChild<QPushButton*>("pushButton_" + QString::number(i));
        connect(pushButton, SIGNAL(clicked()), this, SLOT(do_click_button()));
        pushButton->setFocusPolicy(Qt::NoFocus);
    }

//#if QT_VERSION >= 0x050000
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::Tool);
//#endif

//#if QT_VERSION < 0x050000
//    setAttribute(Qt::WA_ShowWithoutActivating, true);
//    myInputPanelDlg->setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
//#endif
}

VirtualKeyboard::~VirtualKeyboard()
{
    delete ui;
}

void VirtualKeyboard::do_click_button()
{
    QString string;
    QPushButton *pushButton = qobject_cast<QPushButton*>(this->sender());
    if(pushButton->objectName() == "pushButton_3") {
        string = "Left Arrow";
    } else if(pushButton->objectName() == "pushButton_4") {
        string = "Right Arrow";
    } else {
        string = pushButton->text();
    }
    emit input_number(string);
    if(string == "Enter") {
        close();
        emit close_keyboard();
    }
}

void VirtualKeyboard::input_number_to_lineedit(QLineEdit *lineEdit, QString string, int decimal)
{
    QKeyEvent *event;
    if(string == "." && decimal > 0) {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Period, Qt::NoModifier);
    } else if(string == "Left Arrow") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    } else if(string == "Right Arrow") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    } else if(string == "Del") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    } /*else if(string == "Delete") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
    } */else if(string == "Enter" || string == "Close") {
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    } else {
        int value = string.toInt();
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_0 + value, Qt::NoModifier);
    }
    QApplication::sendEvent(lineEdit, event);
}

void VirtualKeyboard::open_persistent_editor( QStandardItemModel *model, QTableView *tableView, int index)
{
    if(index >= 0) {
        if(index >= model->columnCount()) {
            index = 0;
        }
        LineEditDelegate *lineEdit = static_cast<LineEditDelegate*>(tableView->itemDelegateForColumn(index));
        qDebug() << lineEdit->m_editFlag;
        if(!lineEdit->m_editFlag) {
            QModelIndex modelIndex = model->item(0, index)->index();
            tableView->openPersistentEditor(modelIndex);
        }
        qDebug() << lineEdit->m_editFlag;
    }
}

void VirtualKeyboard::close_persistent_editor(QStandardItemModel *model, QTableView *tableView, int index)
{
    qDebug() << index;
    if(index >= model->columnCount()) {
        index = 0;
    }
    LineEditDelegate *lineEdit = static_cast<LineEditDelegate*>(tableView->itemDelegateForColumn(index));
//    m_keyboardShowFlag = false;
    qDebug() << model->columnCount();
    qDebug() << index;
    if(/*lineEdit->m_inputCount > 0 && */index >= 0) {
        QModelIndex modelIndex = model->item(0, index)->index();
        tableView->closePersistentEditor(modelIndex);
        qDebug() << "closeeditor";
//        set_header_text_close(lineEdit->lineEditList.at(lineEdit->lineEditList.count() -1));
        lineEdit->m_editFlag = false;
        lineEdit->m_keyboardFlag = false;
        lineEdit->m_inputCount = 0;
    }
}

void VirtualKeyboard::input_lineedit_data(QTableView *tableView, QString string, int index)
{
    qDebug() << "index" << index;
    if(index >= 0) {
        if(index >= tableView->model()->columnCount()) {
            index = 0;
        }
        qDebug() << "new" << index;
        LineEditDelegate *lineEdit = static_cast<LineEditDelegate*>(tableView->itemDelegateForColumn(index));
        qDebug() << lineEdit->m_editFlag;
        if(lineEdit->m_editFlag) {
            qDebug() << "run1";
            QLineEdit *editor = lineEdit->lineEditList.at(lineEdit->lineEditList.count() - 1);
            int decimal = lineEdit->decimalAmount;
            editor->setFocusPolicy(Qt::StrongFocus);
            editor->setFocus();
            lineEdit->m_keyboardFlag = true;
            input_number_to_lineedit(editor, string, decimal);
        }

    }
}

