#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    m_mcu = Mcu::get_mcu();
  //  connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);

    editor->setFont(QFont("Times New Roman", 12));
    editor->setStyleSheet("QComboBox{"
        "background-color:qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
        "color: yellow;"
        "selection-background-color: rgba(0, 130, 195, 0);"
        "selection-color: yellow;}"
        "QComboBox::drop-down{border-style:none;}"
        "QComboBox QAbstractItemView{background-color:rgb(0, 130, 195);"
        "selection-color:yellow;}"
        "QComboBox QAbstractItemView::item{height:30px}");

    (const_cast<ComboBoxDelegate *>(this))->comboBoxList.append(editor);

    int maxSize = 0;
    if(itemList.empty()) {
        editor->addItem("on");
        editor->addItem("off");
    } else {
        for(int i = 0; i < itemList.count(); i ++) {
            editor->addItem(itemList.at(i));
            int width = editor->fontMetrics().width(editor->itemText(i));
            if(maxSize < width) {
                maxSize = width;
            }
         }
    }
    if(minimumContentLength < maxSize) {
        editor->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    } else {
        editor->setMinimumContentsLength(minimumContentLength);
    }

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
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    int i = find_list_index(itemList, text);
    QString shortText = modelItemList.at(i);
    model->setData(index, shortText, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);

    Q_UNUSED(index);
}

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
