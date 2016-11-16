#include "pushbuttondelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

PushButtonDelegate::PushButtonDelegate(QObject *parent) :
QStyledItemDelegate(parent)
{

}

PushButtonDelegate::~PushButtonDelegate()
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
        button->text = "Off";
        button->state |= QStyle::State_Enabled;
        button->palette = palette;
        (const_cast<PushButtonDelegate *>(this))->buttonMap.insert(index, button);

    }
    painter->save();

    QRectF rectangle = option.rect;
    QRectF rectangleLeft = QRectF(rectangle.x(), rectangle.y(), 1, rectangle.height());
    QRectF rectangleRight = QRectF(rectangle.x() + rectangle.width() - 1, rectangle.y(), 1, rectangle.height());

    QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, 25));
    linearGradient.setColorAt(0.4, QColor(0, 0, 0));
    linearGradient.setColorAt(1, QColor(0, 120, 195));
    linearGradient.setSpread(QGradient::PadSpread);
    painter->fillRect(rectangle, QBrush(linearGradient));

    QLinearGradient linearGradientLeft(QPointF(0, 0), QPointF(0, 25));
    linearGradientLeft.setColorAt(0.3, QColor(255, 255, 255));
    linearGradientLeft.setColorAt(1, QColor(0, 120, 195));
    linearGradientLeft.setSpread(QGradient::PadSpread);
    painter->fillRect(rectangleLeft, QBrush(linearGradientLeft));

    QLinearGradient linearGradientRight(QPointF(0, 0), QPointF(0, 25));
    linearGradientRight.setColorAt(0.3, QColor(0, 0, 0));
    linearGradientRight.setColorAt(1, QColor(0, 120, 195));
    linearGradientRight.setSpread(QGradient::PadSpread);
    painter->fillRect(rectangleRight, QBrush(linearGradientRight));

    painter->restore();

    drawDisplay(painter, option, option.rect, tr("Off"));
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, button, painter);
}

bool PushButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;
        if(option.rect.adjusted(0, 0, 0, 0).contains(e->x(), e->y()) && buttonMap.contains(index)) {
            change_button_text(const_cast<QModelIndex &>(index));
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

void PushButtonDelegate::set_switch_flag(QModelIndex index)
{
    if(buttonMap.value(index)->text == "On") {
        m_switchFlag = true;
    } else {
        m_switchFlag = false;
    }
}

void PushButtonDelegate::change_button_text(QModelIndex &index)
{
    buttonMap.value(index)->state &= (~QStyle::State_Sunken);
    set_switch_flag(index);

    if(m_switchFlag == false) {
        buttonMap.value(index)->text = "On";
        emit switchPress(m_switchFlag);
    } else {
        buttonMap.value(index)->text = "Off";
        emit switchPress(m_switchFlag);
    }
    m_switchFlag = !m_switchFlag;
}
