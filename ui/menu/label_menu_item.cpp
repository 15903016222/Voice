#include "label_menu_item.h"
#include "ui_label_menu_item.h"

LabelMenuItem::LabelMenuItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelMenuItem)
{
    ui->setupUi(this);

    ui->nameLabel->installEventFilter(this);
}

LabelMenuItem::~LabelMenuItem()
{
    delete ui;
}

void LabelMenuItem::set_title(const QString &title)
{
    QString msg("<p align=\"center\"><font size=4 color=yellow>");
    msg += title;
    msg += "</font>";
    msg += "</p>";
    ui->nameLabel->setText(msg);
}

bool LabelMenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease) {
        emit clicked();
        return true;
    }

    return QWidget::eventFilter(obj, e);
}

void LabelMenuItem::set_text(const QString &text)
{
    ui->label->setText(text);
}

void LabelMenuItem::set(const QString &title, const QString &text)
{
    set_title(title);
    set_text(text);
}
