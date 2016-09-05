#include "comboboxdelegate.h"

#include <QComboBox>
#include <QString>
#include <QDebug>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) :
QItemDelegate(parent)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QComboBox *editor = new QComboBox(parent);

	editor->setFont(QFont("Times New Roman", 11));
	editor->setStyleSheet("QComboBox{"
		"background-color:qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
		"color: yellow;"
		"selection-background-color: rgba(0, 130, 195, 0);"
		"selection-color: yellow;}"
		"QComboBox::drop-down{border-style:none;}"
		"QComboBox QAbstractItemView{background-color:rgb(0, 130, 195);"
		"selection-color:yellow;}"
		"QComboBox QAbstractItemView::item{height:30px}");

	if(itemList.empty()) {
		editor->addItem("on");
		editor->addItem("off");
	} else {
		for(int i = 0; i < itemList.count(); i ++) {
			editor->addItem(itemList.at(i));
		}
	}

	return editor;

	Q_UNUSED(index);
	Q_UNUSED(option);
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString text = index.model()->data(index, Qt::EditRole).toString();
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	int textIndex = comboBox->findText(text);
	comboBox->setCurrentIndex(textIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	QString text = comboBox->currentText();
	model->setData(index, text, Qt::EditRole);
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
