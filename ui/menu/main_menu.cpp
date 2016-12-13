#include "main_menu.h"
#include "ui_main_menu.h"

#include <QKeyEvent>
#include <QWheelEvent>
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

    m_firstCount = ui->treeWidget->topLevelItemCount();

    ui->treeWidget->setFocus();

    QTreeWidgetItem *pItem;
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        pItem = ui->treeWidget->topLevelItem(i);
        m_map.insert(i + 1, pItem->childCount());
    }

    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(change_item_selection()));

    show_or_hide_arrow();
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::change_item_selection()
{
    return;

    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item->childCount() > 0) {
        /* 一级菜单 */
        ui->treeWidget->collapseAll();
        ui->treeWidget->expandItem(item);

        ui->treeWidget->setCurrentItem(item->child(0));

        int index = ui->treeWidget->indexOfTopLevelItem(item);
        ui->treeWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
        emit click_main_menu(count_menu_number(index, 1));
    } else {
        /* 二级菜单 */
        int index = ui->treeWidget->indexOfTopLevelItem(item->parent());
        int indexChild = item->parent()->indexOfChild(item);
        ui->treeWidget->scrollToItem(item->parent(), QAbstractItemView::PositionAtCenter);
        emit click_main_menu(count_menu_number(index, indexChild + 1));
    }
    show_or_hide_arrow();
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
    show_or_hide_arrow();
}

void MainMenu::on_pushButton_down_clicked()
{
    QWheelEvent *e = new QWheelEvent(QCursor::pos(), -40, Qt::MiddleButton, Qt::NoModifier, Qt::Vertical);
    QApplication::sendEvent(ui->treeWidget->verticalScrollBar(), e);
    show_or_hide_arrow();
}

void MainMenu::show_or_hide_arrow()
{
    if(ui->treeWidget->verticalScrollBar()->value() == 0) {
        ui->pushButton_up->hide();
        ui->pushButton_down->show();
    } else if(ui->treeWidget->verticalScrollBar()->value() == ui->treeWidget->verticalScrollBar()->maximum()){
        ui->pushButton_down->hide();
        ui->pushButton_up->show();
    } else {
        ui->pushButton_up->show();
        ui->pushButton_down->show();
    }
}

int MainMenu::count_menu_number(int parent, int child)
{
    int num = 0;
    for(int i = 0; i < parent; i ++) {
        num += m_map.value(i + 1);
    }
    num += child;
    return num;
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
