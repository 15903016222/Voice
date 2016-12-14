#include "main_menu.h"
#include "ui_main_menu.h"

#include <QKeyEvent>
#include <QScrollBar>
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(0);

    ui->treeWidget->expandItem(item);

    QTreeWidgetItem *initItem = item->child(0);
    ui->treeWidget->setCurrentItem(initItem);

    ui->treeWidget->installEventFilter(this);

    ui->treeWidget->setFocus();

    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(do_change_arrow()));

    do_change_arrow();
}

MainMenu::~MainMenu()
{
    delete ui;
}

bool MainMenu::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        return do_keypress_event(static_cast<QKeyEvent *>(event));
    } else if ( event->type() == QEvent::KeyRelease) {
        return do_keyrelease_event(static_cast<QKeyEvent *>(event));
    } else {
        return QWidget::eventFilter(object, event);
    }
}

void MainMenu::on_pushButton_up_clicked()
{
    QWheelEvent *e = new QWheelEvent(QCursor::pos(), 40, Qt::MiddleButton, Qt::NoModifier, Qt::Vertical);
    QApplication::sendEvent(ui->treeWidget->verticalScrollBar(), e);
    do_change_arrow();
}

void MainMenu::on_pushButton_down_clicked()
{
    QWheelEvent *e = new QWheelEvent(QCursor::pos(), -40, Qt::MiddleButton, Qt::NoModifier, Qt::Vertical);
    QApplication::sendEvent(ui->treeWidget->verticalScrollBar(), e);
    do_change_arrow();
}

bool MainMenu::do_keypress_event(QKeyEvent *e)
{
    QModelIndex modelIndex = ui->treeWidget->currentIndex();
    QModelIndex nextModelIndex;

    if (e->key() == Qt::Key_Up) {
        nextModelIndex = modelIndex.sibling(modelIndex.row()-1, modelIndex.column());
    } else if (e->key() == Qt::Key_Down) {
        nextModelIndex = modelIndex.sibling(modelIndex.row()+1, modelIndex.column());
    }

    if (nextModelIndex.isValid()) {
        ui->treeWidget->setCurrentIndex(nextModelIndex);
    }

    return true;
}

bool MainMenu::do_keyrelease_event(QKeyEvent *e)
{
    QModelIndex modelIndex = ui->treeWidget->currentIndex();
    QModelIndex nextModelIndex;

    switch ((int)e->key()) {
    case Qt::Key_Back:
    case Qt::Key_Cancel:
    case Qt::Key_Escape:
        nextModelIndex = modelIndex.parent();
        ui->treeWidget->collapseAll();
        break;
    case Qt::Key_Return:
        nextModelIndex = modelIndex.child(0, 0);
        if (nextModelIndex.isValid()) {
            ui->treeWidget->collapseAll();
            ui->treeWidget->scrollTo(nextModelIndex, QTreeWidget::PositionAtCenter);
        } else {
            emit click((Type)((modelIndex.parent().row() << 4) | modelIndex.row()));
        }
        break;
    default:
        break;
    }

    if (nextModelIndex.isValid()) {
        ui->treeWidget->setCurrentIndex(nextModelIndex);
    }

    return true;
}

void MainMenu::do_change_arrow()
{
    if (ui->treeWidget->verticalScrollBar()->maximum() == 0) {
        ui->pushButton_down->hide();
        ui->pushButton_up->hide();
    } else if(ui->treeWidget->verticalScrollBar()->value() == ui->treeWidget->verticalScrollBar()->maximum()){
        ui->pushButton_down->hide();
        ui->pushButton_up->show();
    } else if(ui->treeWidget->verticalScrollBar()->value() == 0) {
        ui->pushButton_up->hide();
        ui->pushButton_down->show();
    } else {
        ui->pushButton_up->show();
        ui->pushButton_down->show();
    }
}
