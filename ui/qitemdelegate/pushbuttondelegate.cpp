#include "pushbuttondelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

PushButtonDelegate::PushButtonDelegate(QObject *parent) :
QItemDelegate(parent)
{
}

void PushButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton* button = buttonMap.value(index);
    QPalette palette;
    palette.setBrush(QPalette::ButtonText,Qt::yellow);
    if (!button) {
        button = new QStyleOptionButton();
        button->rect = option.rect.adjusted(0, 0, 0, 0);
        button->text = "On";
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

    drawDisplay(painter, option, option.rect, tr("On"));
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
                buttonMap.value(index)->text = "Off";
            } else {
                buttonMap.value(index)->text = "On";
            }
            switchFlag = !switchFlag;
        }
    }
    model->setData(index, buttonMap.value(index)->text, Qt::EditRole);
    return true;
}

QSize PushButtonDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QSize(option.rect.width(), option.rect.height());
}

void PushButtonDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QFont font("Times New Roman", 12, false, false);
    painter->setFont(font);
    Q_UNUSED(option);
    Q_UNUSED(rect);
    Q_UNUSED(text);
}

void PushButtonDelegate::setSwitchFlag(QModelIndex index)
{
    if(buttonMap.value(index)->text == "On") {
        switchFlag = true;
    } else {
        switchFlag = false;
    }
}


PushButtonDelegate::~PushButtonDelegate()
{

}


