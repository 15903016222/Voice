#include "topmenu.h"
#include "ui_topmenu.h"
#include "measurementdialog.h"
#include "doublespinboxdelegate.h"

#include <QFile>
#include <QString>
#include <QLabel>
#include <QTextDocument>
#include <QTextBlockFormat>
#include <QDebug>
#include <QEvent>

TopMenu :: TopMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopMenu)
{
    ui->setupUi(this);

    initUI();

    for(int i = 0; i < measurementLabelList.count(); i ++)
    {
        measurementLabelList.at(i)->installEventFilter(this);
    }

    initGain_angle();
}

TopMenu :: ~TopMenu()
{
    delete(ui);
}

void TopMenu::initUI()
{
    ui->label_1->setText(tr("Gain-r\n(dB)"));
    ui->label_2->setText(tr("A%\n(%)"));
    ui->label_3->setText(tr("DA^\n(mm)"));
    ui->label_4->setText(tr("PA^\n(mm)"));
    ui->label_5->setText(tr("SA^\n(mm)"));
    ui->label_6->setText(tr("U(m-r)\n(mm)"));
    ui->label_7->setText(tr("I(m-r)\n(mm)"));
    ui->label_8->setText(tr("S(m-r)\n(mm)"));
    ui->label_9->setText(tr("TCG-SL\n(±dB)"));
    ui->label_10->setText(tr("Angle\n(°)"));
    for(int i = 1; i <= 10; i ++)
    {
        QLabel *label=findChild<QLabel*>("label_" + QString::number(i));
        if(i == 1)
        {
            label->setStyleSheet("QLabel{background-color:rgba(0, 130, 195);"
                                 "line-height:80%;"
                                 "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");
            QString str = label->text();
            QString text1, text2;
            if(str.contains("\n") == true)
            {
                int index = str.indexOf("\n");
                text1 = str.left(index);
                text2 = str.right(str.length() - index - 1);
                label->setText("<font color=yellow face='Times New Roman' style=font-size:12pt>"
                               +text1+
                               "</font><br><font color=yellow face='Times New Roman' style=font-size:8pt>"
                               +text2+"</font>");
            }
        }
        else if(i == 10)
        {
            label->setStyleSheet("QLabel{background-color:rgba(0, 130, 195);"
                                 "line-height:80%;"
                                 "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
                                 "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");
            QString str = label->text();
            QString text1, text2;
            if(str.contains("\n") == true)
            {
                int index = str.indexOf("\n");
                text1 = str.left(index);
                text2 = str.right(str.length() - index - 1);
                label->setText("<font color=yellow face='Times New Roman' style=font-size:12pt>"
                               +text1+
                               "</font><br><font color=yellow face='Times New Roman' style=font-size:8pt>"
                               +text2+"</font>");
            }
        }
        else
        {
            label->setStyleSheet("QLabel{background-color:rgba(0, 130, 195);"
                                 "line-height:80%;"
                                 "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
                                 "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");
            QString str = label->text();
            QString text1, text2;
            if(str.contains("\n") == true)
            {
                int index = str.indexOf("\n");
                text1 = str.left(index);
                text2 = str.right(str.length() - index - 1);
                label->setText("<font color=white face='Times New Roman' style='font-size:12pt'>"
                               +text1+
                               "</font><br><font color=white face='Times New Roman' style='font-size:8pt'>"
                               +text2+"</font>");
            }
            measurementLabelList.append(label);
        }

    }

    for(int i = 1; i <= 8; i++)
    {
        QLabel *label=findChild<QLabel*>("measurement_" + QString::number(i));
        label->setStyleSheet("QLabel{background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.559322 rgba(0, 130, 195, 255));"
                             "font: 14pt 'Times New Roman';"
                             "color: rgb(255, 255, 255);"
                             "border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));"
                             "border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));}");
    }
}

void TopMenu::initGain_angle()
{
  ui->tableView_gain->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_gain->verticalHeader()->hide();
  ui->tableView_gain->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_gain->horizontalHeader()->hide();

  QStandardItemModel *model_gain = new QStandardItemModel(1, 2, this);
  ui->tableView_gain->setModel(model_gain);

  DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
  QStandardItem *item_gain1 = new QStandardItem(QString::number(100, 'f', 1));
  QStandardItem *item_gain2 = new QStandardItem("(" + QString::number(10, 'f', 2) + ")");
  model_gain->setItem(0, 0, item_gain1);
  model_gain->setItem(0, 1, item_gain2);
  model_gain->item(0, 0)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
  model_gain->item(0, 1)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  model_gain->item(0, 0)->setForeground(Qt::white);
  model_gain->item(0, 1)->setForeground(Qt::yellow);
  model_gain->item(0, 0)->setFont(QFont("Times New Roman", 11));
  model_gain->item(0, 1)->setFont(QFont("Times New Roman", 9));
  ui->tableView_gain->setItemDelegate(doubleSpinBox);
  ui->tableView_gain->setEditTriggers(QAbstractItemView::CurrentChanged);
  ui->tableView_gain->show();


  ui->tableView_angle->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_angle->verticalHeader()->hide();
  ui->tableView_angle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->tableView_angle->horizontalHeader()->hide();

  QStandardItemModel *model_angle = new QStandardItemModel(1, 1, this);
  ui->tableView_angle->setModel(model_angle);

  DoubleSpinBoxDelegate *doubleSpinBox_angle = new DoubleSpinBoxDelegate(this);
  QStandardItem *item_angle = new QStandardItem(QString::number(70, 'f', 1));
  model_angle->setItem(0, item_angle);
  model_angle->item(0)->setTextAlignment(Qt::AlignCenter);
  model_angle->item(0)->setForeground(Qt::white);
  model_angle->item(0)->setFont(QFont("Times New Roman", 11));
  ui->tableView_angle->setItemDelegate(doubleSpinBox_angle);
  ui->tableView_angle->setEditTriggers(QAbstractItemView::CurrentChanged);
  ui->tableView_angle->show();

}

bool TopMenu::eventFilter(QObject *object, QEvent *event)
{
  if(object == measurementLabelList.at(0) ||
            object == measurementLabelList.at(1) ||
            object == measurementLabelList.at(2) ||
            object == measurementLabelList.at(3) ||
            object == measurementLabelList.at(4) ||
            object == measurementLabelList.at(5) ||
            object == measurementLabelList.at(6) ||
            object == measurementLabelList.at(7) )

  {
    if(event->type() == QEvent::MouseButtonPress)
    {
        MeasurementDialog *mDialog=new MeasurementDialog;
        mDialog->show();

    }
    return QWidget::eventFilter(object,event);
  }
}
