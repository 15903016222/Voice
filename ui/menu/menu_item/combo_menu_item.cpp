/**
 * @file combo_menu_item.cpp
 * @brief combo box menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "combo_menu_item.h"
#include "ui_combo_menu_item.h"

#include <QDebug>
#include <QListView>

ComboMenuItem::ComboMenuItem(QWidget *parent) :
    MenuItem(parent),
    ui(new Ui::ComboMenuItem),
    m_displayMode(ALL)
{
    ui->setupUi(this);

    ui->nameLabel->installEventFilter(this);

    ui->comboBox->hide();
    ui->label->show();
    ui->comboBox->setView(new QListView());
    ui->comboBox->setMinimumWidth(ui->comboBox->width());
    ui->comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(value_changed(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(set_label_text(QString)));
}

ComboMenuItem::~ComboMenuItem()
{
    delete ui;
}

void ComboMenuItem::set_title(const QString &title)
{
    QString msg("<p align=\"center\"><font style='font-size:16pt' face='Arial' color=yellow>");
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
        if (ui->comboBox->count() == 2) {
            ui->comboBox->setCurrentIndex((ui->comboBox->currentIndex()+1)%2);
        } else {
        ui->comboBox->showPopup();
        }
        return true;
    } else if (e->type() == QEvent::Hide) {
        ui->comboBox->hidePopup();
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

void ComboMenuItem::set_current_index(int index)
{
    ui->comboBox->setCurrentIndex(index);
}

int ComboMenuItem::current_index() const
{
    return ui->comboBox->currentIndex();
}

void ComboMenuItem::set_dispay_mode(ComboMenuItem::DisplayMode mode)
{
    m_displayMode = mode;
    set_label_text(ui->comboBox->currentText());
}

void ComboMenuItem::set_label_text(QString text)
{
    switch (m_displayMode) {
    case ALL:
        ui->label->setText(text);
        break;
    case PREFIX:
        ui->label->setText(text.left(text.indexOf(" ")));
        break;
    case SUFFIX:
        ui->label->setText(text.right(text.length() - text.indexOf(" ") - 1));
        break;
    default:
        break;
    }
}
