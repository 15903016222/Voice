/**
 * @file main_menu.cpp
 * @brief main menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
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

    do_change_arrow();

    set_opacity_main_menu(80);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::show()
{
    ui->treeWidget->setFocus();
    QWidget::show();
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
    switch ((int)e->key()) {
    case Qt::Key_Back:
    case Qt::Key_Cancel:
    case Qt::Key_Escape:
        do_keyescape_event(ui->treeWidget->currentIndex());
        break;
    case Qt::Key_Return:
        do_keyreturn_event(ui->treeWidget->currentIndex());
        break;
    default:
        break;
    }

    return true;
}

void MainMenu::do_keyescape_event(const QModelIndex &index)
{
    QModelIndex nextModelIndex = index.parent();

    if (nextModelIndex.isValid()) {
        ui->treeWidget->collapseAll();
        ui->treeWidget->setCurrentIndex(nextModelIndex);
    }
}

void MainMenu::do_keyreturn_event(const QModelIndex &index)
{
    QModelIndex nextIndex = index.child(0, 0);
    if (nextIndex.isValid()) {
        ui->treeWidget->collapseAll();
        ui->treeWidget->scrollTo(nextIndex, QTreeWidget::PositionAtCenter);
    } else {
    }

    if (nextIndex.isValid()) {
        ui->treeWidget->setCurrentIndex(nextIndex);
    }
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

void MainMenu::on_treeWidget_clicked(const QModelIndex &index)
{
    do_keyreturn_event(index);
}

void MainMenu::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);

    Type type;

    do_change_arrow();

    if (current->childCount() > 0) {
        return;
    }

    type = (Type)(((ui->treeWidget->indexOfTopLevelItem(current->parent()))<<4)|current->parent()->indexOfChild(current));

    emit click(type);
}

void MainMenu::set_opacity_main_menu(double value)
{
    QString alpha = QString::number(qRound(qreal(value / 100 * 256 - 1)));
    qDebug() << alpha;
    ui->widget->setStyleSheet(QString("QWidget{background-color:rgba(37, 76, 124," + alpha + ");" +
                              "border-radius: 5px;}" + "QWidget QPushButton{background-color: rgba(37, 76, 124, 0);}"));

}

void MainMenu::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    ui->treeWidget->setColumnWidth(0, width * 4 / 5);
    ui->treeWidget->setColumnWidth(1, width / 5);

}
