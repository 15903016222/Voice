/**
 * @file label_menu_item.cpp
 * @brief label menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "label_menu_item.h"
#include "ui_label_menu_item.h"

#include <QDebug>

LabelMenuItem::LabelMenuItem(QWidget *parent, const QString &title, const QString &text) :
    MenuItem(parent),
    ui(new Ui::LabelMenuItem)
{
    ui->setupUi(this);
    connect(ui->pushButton,
            SIGNAL(clicked()),
            this, SIGNAL(clicked()));

    set_title(title);
    set_text(text);

    ui->pushButton->installEventFilter(this);
    ui->label->installEventFilter(this);
}

LabelMenuItem::~LabelMenuItem()
{
    delete ui;
}

void LabelMenuItem::set_title(const QString &title)
{
    ui->pushButton->setText(title);
    m_title = title;
}

void LabelMenuItem::set_text(const QString &text)
{
    ui->label->setText(text);
    m_text = text;
}

void LabelMenuItem::set_selected(bool flag)
{
    QString msg;
    if(flag) {
        msg = QString("QPushButton{"
                     " background-position: center;"
                      "font: 16pt \"Arial\";"
                      "background-color:rgba(0, 130, 195);"
                      "border: 0px solid black;"
                      "font-weight:bold;"
                      "color: rgb(255, 255, 255);"
                      "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), 	stop:0.559322 rgba(255, 255, 255, 255));"
                      "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));"
                      "}");
    } else {
        msg = QString("QPushButton{"
                     " background-position: center;"
                      "font: 16pt \"Arial\";"
                      "background-color:rgba(0, 130, 195);"
                      "border: 0px solid black;"
                      "color: rgb(255, 255, 0);"
                      "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), 	stop:0.559322 rgba(255, 255, 255, 255));"
                      "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));"
                      "}");
    }
    m_selected = flag;
    ui->pushButton->setStyleSheet(msg);
    ui->pushButton->setText(m_title);

}

void LabelMenuItem::set_edit(bool flag)
{
    if(flag) {
        emit clicked();
    }
}


bool LabelMenuItem::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        set_selected(true);
    } else if (event->type() == QEvent::Hide
               || event->type() == QEvent::Leave) {
        set_selected(false);
    }

    return QWidget::eventFilter(object, event);
}

