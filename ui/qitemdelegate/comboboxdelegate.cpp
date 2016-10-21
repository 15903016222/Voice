#include "comboboxdelegate.h"

#include <QDebug>
#include <QListView>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QStyle>
#include <QGraphicsDropShadowEffect>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
  //  connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    editFlag = false;

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);

    if(itemList.empty()) {
        editor->addItem("on");
        editor->addItem("off");
    } else {
        for(int i = 0; i < itemList.count(); i ++) {
            editor->addItem(itemList.at(i));
         }
    }

    editor->setStyleSheet("QComboBox{"
        "background-color:qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
        "color: yellow;"
        "font:12pt 'Times New Roman';"
        "selection-background-color: rgba(0, 130, 195, 0);"
        "selection-color: yellow;}"
        "QComboBox::drop-down{border-style:none;}"
        "QComboBox QAbstractItemView{"
        "font:12pt 'Times New Roman';"
        "background-color:rgb(255, 255, 255);"
        "margin-bottom:45px;"
        "outline:0px;}"
        "QComboBox QAbstractItemView::item{height:30px}"
        "QComboBox QAbstractItemView::item:hover{color:yellow;"
        "background-color:rgba(0, 150, 255, 225);}"
        "QComboBox QAbstractItemView::item:selected{color:yellow;"
        "background-color:rgba(0, 150, 255, 225);}");

    editor->setView(new QListView());
    editor->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);
    editor->view()->parentWidget()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
//    editor->view()->setFrameShape(QFrame::NoFrame);
//    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
//    effect->setBlurRadius(0);
//    effect->setColor(Qt::black);
//    effect->setOffset(2,2);
//    editor->view()->parentWidget()->setGraphicsEffect(effect);

    qDebug() << "1";

    set_comboBox_item_width(editor);
//    editor->view()->setVisible(true);

    qDebug() << editor->view()->isVisible();
//    editor->view()->selectionModel()->setCurrentIndex(index,QItemSelectionModel::ClearAndSelect);
//    static_cast<QAbstractItemView*>(editor->view())->setState(QAbstractItemView::EditingState);
//    editor->view()->parentWidget()->show();
//    editor->view()->parentWidget()->setFocus();

    (const_cast<ComboBoxDelegate *>(this))->comboBoxList.append(editor);
    (const_cast<ComboBoxDelegate *>(this))->comboBoxMap.insert(index, editor);
    (const_cast<ComboBoxDelegate *>(this))->editFlag = true;

    connect(editor, SIGNAL(activated(QString)), this, SLOT(commit_and_close_editor(QString)));
    return editor;

    Q_UNUSED(index);
    Q_UNUSED(option);
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString shortText = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int i = find_list_index(modelItemList, shortText);
    int textIndex = comboBox->findText(itemList.at(i));
    comboBox->setCurrentIndex(textIndex);
    qDebug() << "2";
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);    
    QString text = comboBox->currentText();
    int i = find_list_index(itemList, text);
    QString shortText = modelItemList.at(i);
    model->setData(index, shortText, Qt::EditRole);
    qDebug() << "3";
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    Q_UNUSED(index);
}

//bool ComboBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//    if(event->type() == QEvent::MouseButtonRelease) {
//        QMouseEvent* e =(QMouseEvent*)event;
//        if(option.rect.adjusted(0, 0, 0, 0).contains(e->x(), e->y()) && comboBoxMap.contains(index)) {
//            comboBoxMap.value(index)->showPopup();
//        }
//    }
//    return true;

//}

void ComboBoxDelegate::set_comboBox_item_list(QStringList stringList)
{
    itemList = stringList;
}

void ComboBoxDelegate::set_model_item_list(QStringList stringList)
{
    modelItemList = stringList;
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
    minimumContentLength = width;
}

void ComboBoxDelegate::commit_and_close_editor(const QString &str)
{
    QComboBox *editor = qobject_cast<QComboBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
    emit comboBox_current_text(str);
    if(str == "Chinese" || str == "English") {
        emit change_language(str);
    }
    editFlag = false;
    editor->hidePopup();
}

void ComboBoxDelegate::do_rotary_event(Mcu::RotaryType type)
{
  //  if(comboBoxList.size() != 0){
        QComboBox *comboBox = comboBoxList.at(comboBoxList.count() - 1);
        int index = comboBox->currentIndex();

        if(modelItemList.count() > 1){
            if (type == Mcu::ROTARY_UP) {
                if(index == 0){
                    index = modelItemList.count() - 1;
                }else {
                    index = index - 1;
                }
            } else {
                if(index == modelItemList.count() - 1){
                    index = 0;
                }else {
                    index = index + 1;
                }
            }
        }
        comboBox->setCurrentIndex(index);
  //  }
}

void ComboBoxDelegate::set_comboBox_item_width(QComboBox *editor) const
{
    int maxSize = 0;
    for(int i = 0; i < itemList.count(); i ++) {
        int width = editor->fontMetrics().width(editor->itemText(i));
        if(maxSize < width) {
            maxSize = width;
        }
     }
    if(minimumContentLength < maxSize) {
        editor->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    } else {
        editor->setMinimumContentsLength(minimumContentLength);
    }
}

//void ComboBoxDelegate::showPopup() {
//    QComboBox::showPopup();
//    QWidget *popup = this->findChild<QFrame*>();
//    popup->move(popup->x(),popup->y() - this->height() - popup->height());
//}
