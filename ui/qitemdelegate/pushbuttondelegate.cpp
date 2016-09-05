#include "pushbuttondelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QDialog>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QPushButton>
#include <QDebug>

PushButtonDelegate::PushButtonDelegate(QObject *parent) :
QItemDelegate(parent)
{
	//    m_Button->setStyleSheet("QPushButton{border:0px;border-radius:0px;color:yellow;font: 10pt 'Levenim MT';background-color:rgba(90, 90, 90, 225);}");
}

void PushButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = buttonMap.value(index);
    QPalette palette;
    palette.setBrush(QPalette::ButtonText,Qt::yellow);
    if (!button) {
        button = new QStyleOptionButton();
        button->rect = option.rect.adjusted(0, 0, 0, 0);
        button->text = "on";
        button->state |= QStyle::State_Enabled;
        button->palette=palette;
        (const_cast<PushButtonDelegate *>(this))->buttonMap.insert(index, button);
    }
    painter->save();

    QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, 25));
    linearGradient.setColorAt(0.4, QColor(0, 0, 0));
    linearGradient.setColorAt(1, QColor(0, 120, 195));
    linearGradient.setSpread(QGradient::PadSpread);
    painter->fillRect(option.rect, QBrush(linearGradient));
    painter->restore();

    drawDisplay(painter, option, option.rect, tr("on"));
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}

bool PushButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	//    if (event->type() == QEvent::MouseButtonPress) {

	//        QMouseEvent* e =(QMouseEvent*)event;

	//        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && m_btns.contains(index)) {
	//            m_btns.value(index)->state |= QStyle::State_Sunken;
	//        }
	//    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;
        setSwitchFlag(index);
        if (option.rect.adjusted(0, 0, 0, 0).contains(e->x(), e->y()) && buttonMap.contains(index)) {
            buttonMap.value(index)->state &= (~QStyle::State_Sunken);

            if(switchFlag == true) {
                buttonMap.value(index)->text = "off";
            } else {
                buttonMap.value(index)->text = "on";
            }
            switchFlag = !switchFlag;
        }
    }
    model->setData(index, buttonMap.value(index)->text, Qt::EditRole);
    Q_UNUSED(model);
    return true;
}

QSize PushButtonDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QSize(option.rect.width(), option.rect.height());
}

void PushButtonDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QFont font("Times New Roman", 11, false, false);
    painter->setFont(font);
    Q_UNUSED(option);
    Q_UNUSED(rect);
    Q_UNUSED(text);
}

void PushButtonDelegate::setSwitchFlag(QModelIndex index)
{
    if(buttonMap.value(index)->text == "on") {
        switchFlag = true;
    } else {
        switchFlag = false;
    }
}


PushButtonDelegate::~PushButtonDelegate()
{
//	QPainter *painter;
//	foreach(QStyleOptionButton *button, buttonMap.values())
//	{
//		painter->eraseRect(button->rect);
//	}
//	qDebug() << "erase painter.";
}


//QWidget *PushButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QPushButton *editor = new QPushButton(parent);
//    editor->setText("on");

//    (const_cast<PushButtonDelegate *>(this))->modelIndex.append(index);
//    (const_cast<PushButtonDelegate *>(this))->buttonMap.insert(index, editor);
//    editor->installEventFilter(parent);
//    return editor;

//    Q_UNUSED(index);
//    Q_UNUSED(option);
//}

//void PushButtonDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    QString value = index.model()->data(index,Qt::EditRole).toString();
//    QPushButton *pushButton = static_cast<QPushButton*>(editor);
//    pushButton->setText(value);
//}

//void PushButtonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{
//    QPushButton *pushButton = static_cast<QPushButton*>(editor);
//    QString text = pushButton->text();
//    model->setData(index, text, Qt::EditRole);
//}

//void PushButtonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    Q_UNUSED(index);
//    editor->setGeometry(option.rect);
//}

//void PushButtonDelegate::change_editor_text(QModelIndex index)
//{
//    bool switchFlag;
//    if(buttonMap.value(index)->text() == "on") {
//        switchFlag = true;
//    } else {
//        switchFlag = false;
//    }
//    if(switchFlag == true) {
//        buttonMap.value(index)->setText("off");
//    } else {
//        buttonMap.value(index)->setText("on");
//    }
//    switchFlag = !switchFlag;
//}

//bool PushButtonDelegate::eventFilter(QObject *object, QEvent *event)
//{
//    if(event->type() == QEvent::MouseButtonPress && object == buttonMap.value(modelIndex.at(0))) {
//        change_editor_text(modelIndex.at(0));
//    }
//    return QObject::eventFilter(object, event);
//}

