#include "comboboxdelegate.h"

#include <QDebug>
#include <QListView>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QStyle>
#include <QGraphicsDropShadowEffect>
#include <QApplication>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
//    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
//    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
    m_editFlag = false;

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);

    if(m_itemList.empty()) {
        editor->addItem("on");
        editor->addItem("off");
    } else {
        for(int i = 0; i < m_itemList.count(); i ++) {
            editor->addItem(m_itemList.at(i));
         }
    }

    editor->setStyleSheet("QComboBox{"
        "background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
        "color: yellow;"
        "font: 12pt 'Times New Roman';"
        "selection-background-color: rgba(0, 130, 195, 0);"
        "selection-color: yellow;}"
        "QComboBox::drop-down{border-style: none;}"
        "QComboBox QAbstractItemView{"
        "font: 12pt 'Times New Roman';"
        "background-color: rgb(255, 255, 255);"
        "margin-bottom: 45px;"
        "outline: 0px;}"
        "QComboBox QAbstractItemView::item{height: 30px;}"
        "QComboBox QAbstractItemView::item:hover{color: yellow;"
        "background-color: rgba(0, 150, 255, 225);}"
        "QComboBox QAbstractItemView::item:selected{color: yellow;"
        "background-color: rgba(0, 150, 255, 225);}");

    editor->setView(new QListView());
    editor->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);
    editor->view()->parentWidget()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    editor->view()->setFocusPolicy(Qt::StrongFocus);
    editor->view()->setFocus();

    set_comboBox_item_width(editor);

    (const_cast<ComboBoxDelegate *>(this))->comboBoxList.append(editor);
    (const_cast<ComboBoxDelegate *>(this))->m_comboBoxMap.insert(index, editor);
    (const_cast<ComboBoxDelegate *>(this))->m_editFlag = true;

    connect(editor, SIGNAL(activated(QString)), this, SLOT(commit_and_close_editor(QString)));
    return editor;

    Q_UNUSED(index);
    Q_UNUSED(option);
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString shortText = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int i = find_list_index(m_modelItemList, shortText);
    int textIndex = comboBox->findText(m_itemList.at(i));
    comboBox->setCurrentIndex(textIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);    
    QString text = comboBox->currentText();
    int i = find_list_index(m_itemList, text);
    QString shortText = m_modelItemList.at(i);
    model->setData(index, shortText, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    Q_UNUSED(index);
}

void ComboBoxDelegate::set_comboBox_item_list(QStringList stringList)
{
    m_itemList = stringList;
}

void ComboBoxDelegate::set_model_item_list(QStringList stringList)
{
    m_modelItemList = stringList;
}

int ComboBoxDelegate::find_list_index(QStringList stringList, QString string) const
{
    int index = 0;
    for(int i = 0; i < stringList.count(); i ++) {
        if(string == stringList.at(i)) {
            index = i;
            break;
        }
    }
    return index;
}

void ComboBoxDelegate::set_minimum_contents_length(int width)
{
    m_minimumContentLength = width;
}

void ComboBoxDelegate::commit_and_close_editor(const QString &str)
{
    qDebug() << "commit close";
    QComboBox *editor = qobject_cast<QComboBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
    emit comboBox_current_text(str);
    if(str == "Chinese" || str == "English") {
        emit change_language(str);
    }
    m_editFlag = false;
}

void ComboBoxDelegate::do_rotary_event(Mcu::RotaryType type)
{
    if(m_editFlag) {
        QKeyEvent *event;
        QComboBox *comboBox = comboBoxList.at(comboBoxList.count() - 1);

        QListView *view = static_cast<QListView*>(comboBox->view());
        view->setFocusPolicy(Qt::StrongFocus);
        view->setFocus();

        if(type == Mcu::ROTARY_UP) {
            event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        } else {
            event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
        }
        QApplication::sendEvent(view, event);
    }
}

void ComboBoxDelegate::key_sure(Mcu::KeyType key)
{
    if(key == Mcu::KEY_SURE) {
        if(m_editFlag) {
            QComboBox *comboBox = comboBoxList.at(comboBoxList.count() - 1);
//            QString string = m_itemList.at(comboBox->currentIndex());
//            commit_and_close_editor(string);
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
            QApplication::sendEvent(comboBox, event);
        }
    }
}

void ComboBoxDelegate::set_comboBox_item_width(QComboBox *editor) const
{
    int maxSize = 0;
    for(int i = 0; i < m_itemList.count(); i ++) {
        int width = editor->fontMetrics().width(editor->itemText(i));
        if(maxSize < width) {
            maxSize = width;
        }
     }
    if(m_minimumContentLength < maxSize) {
        editor->view()->setFixedWidth(maxSize);
    }
}
