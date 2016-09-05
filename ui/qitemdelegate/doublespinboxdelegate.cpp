#include "doublespinboxdelegate.h"

#include <QDoubleSpinBox>

DoubleSpinBoxDelegate::DoubleSpinBoxDelegate(QObject *parent) :
QItemDelegate(parent)
{
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
	return editor;
	Q_UNUSED(index);
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
	model->setData(index, QString::number(value, 'f', 2), Qt::EditRole);
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
