#include "base_dialog.h"
#include "ui_base_dialog.h"
#include <QPainter>
#include <QColor>

static const QColor s_defaultBaseDialogBg(0, 130, 195);

BaseDialog::BaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseDialog),
   m_bgColor(s_defaultBaseDialogBg)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);       /* 设置窗口背景透明 */
}

BaseDialog::~BaseDialog()
{
    delete ui;
}

void BaseDialog::set_background(const QColor &color)
{
    m_bgColor = color;
    update();
}

void BaseDialog::paintEvent(QPaintEvent *event)
{
    /* 圆角实现，并且需设置窗口背景透明 setAttribute(Qt::WA_TranslucentBackground); */
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  /* 反锯齿; */
    painter.setBrush(QBrush(m_bgColor));
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(this->rect(), 8, 8);

    QWidget::paintEvent(event);
}


