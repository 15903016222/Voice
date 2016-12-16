#include "combo_menu_item.h"
#include "ui_combo_menu_item.h"

#include <QDebug>
#include <QListView>

ComboMenuItem::ComboMenuItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComboMenuItem)
{
    ui->setupUi(this);

    ui->nameLabel->installEventFilter(this);

    ui->comboBox->hide();
    ui->label->show();
    ui->comboBox->setView(new QListView());

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(value_changed(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), ui->label, SLOT(setText(QString)));
}

ComboMenuItem::~ComboMenuItem()
{
    delete ui;
}

void ComboMenuItem::set_title(const QString &title)
{
    QString msg("<p align=\"center\"><font size=4 color=yellow>");
    msg += title;
    msg += "</font>";
    msg += "</p>";
    ui->nameLabel->setText(msg);
}

void ComboMenuItem::add_item(const QString &text)
{
    ui->comboBox->addItem(text);
}

void ComboMenuItem::set_items(const QStringList &texts)
{
    ui->comboBox->addItems(texts);
}

bool ComboMenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease) {
        ui->comboBox->showPopup();
        return true;
    }

    return QWidget::eventFilter(obj, e);
}

void ComboMenuItem::set(const QString &title, const QStringList &texts)
{
    set_title(title);

    ui->comboBox->clear();
    ui->comboBox->addItems(texts);
}
