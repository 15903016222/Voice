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

    m_languageOption = 1;

    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(0);
    ui->treeWidget->expandItem(item);

    QTreeWidgetItem *initItem = item->child(0);
    ui->treeWidget->setCurrentItem(initItem);

    ui->treeWidget->setExpandsOnDoubleClick(false);
    ui->treeWidget->setRootIsDecorated(false);
    ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeWidget->installEventFilter(this);

    m_firstCount = ui->treeWidget->topLevelItemCount();
    qDebug() << m_firstCount;
    ui->treeWidget->setFocus();

    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(change_item_selection()));

    show_or_hide_arrow();

}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::change_item_selection()
{
    qDebug() << "click";
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item->childCount() > 0) {
        ui->treeWidget->collapseAll();
        ui->treeWidget->expandItem(item);
        QTreeWidgetItem *initItem = item->child(0);
        ui->treeWidget->setCurrentItem(initItem);

        int index = ui->treeWidget->indexOfTopLevelItem(item);
        if(index >= 4 && index < m_firstCount) {
            ui->treeWidget->scrollToItem(item, QAbstractItemView::PositionAtCenter);
        }
        emit click_main_menu(item->text(0), initItem->text(0));
    } else {        
        emit click_main_menu(item->parent()->text(0), item->text(0));
    }
    show_or_hide_arrow();
}

bool MainMenu::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        QTreeWidgetItem *previous = ui->treeWidget->currentItem();
        int index = ui->treeWidget->indexOfTopLevelItem(previous->parent());
        int subIndex = previous->parent()->indexOfChild(previous);

        QTreeWidgetItem *current;

        switch (keyEvent->key()) {
        case Qt::Key_Up:
            if(subIndex == 0) {
                if(index > 0) {
                    QTreeWidgetItem *newItem = ui->treeWidget->topLevelItem(index - 1);
                    ui->treeWidget->collapseItem(previous->parent());
                    ui->treeWidget->expandItem(newItem);
                    current = newItem->child(newItem->childCount() - 1);
                    ui->treeWidget->setCurrentItem(current);
                }
            } else {
                current = previous->parent()->child(subIndex - 1);
                ui->treeWidget->setCurrentItem(current);
            }
            return true;
            break;
        case Qt::Key_Down:
            if(subIndex == (previous->parent()->childCount() - 1)) {
                if(index < m_firstCount - 1) {
                    QTreeWidgetItem *newItem = ui->treeWidget->topLevelItem(index + 1);
                    ui->treeWidget->collapseItem(previous->parent());
                    ui->treeWidget->expandItem(newItem);
                    current = newItem->child(0);
                    ui->treeWidget->setCurrentItem(current);
                }
            } else {
                current = previous->parent()->child(subIndex + 1);
                ui->treeWidget->setCurrentItem(current);
            }
            return true;
            break;
        case Qt::Key_Enter:
            break;
//        case Qt::Key_Alt:
//            if(this->isHidden()) {
//                this->show();
//            } else {
//               this->hide();
//            }

//            return true;
//            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(object, event);
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
