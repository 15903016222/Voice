#include "thirdmenuwidget.h"
#include "ui_thirdmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"
#include "pushbuttondelegate.h"

#include <QDebug>
#include <QPainter>

ThirdMenuWidget::ThirdMenuWidget(QWidget *parent) :
QWidget(parent),
	ui(new Ui::ThirdMenuWidget)
{
	ui->setupUi(this);

	widget = new FirstSecondMenuWidget;

	QFile *fileOne = new QFile(":/json/resources/menutwo.json");
	thirdMenuHash = read_json_file(fileOne);
	fileOne->close();

	QFile *fileTwo = new QFile(":/json/resources/menuthree.json");
	fourthMenuHash = read_json_file(fileTwo);
	fileTwo->close();

	initStandardModel();
	setThirdMenuName(0, 0);
}

ThirdMenuWidget::~ThirdMenuWidget()
{
	delete ui;
}

void ThirdMenuWidget::initStandardModel()
{
	model = new QStandardItemModel(1, THIRD_MENU_NUMBER, this);
	ui->tableView->setModel(model);


	for(int k = 0; k < THIRD_MENU_NUMBER; k++)
	{
		QModelIndex index = model->index(k, 0, QModelIndex());
		model->setData(index, k);
	}
	ui->tableView->horizontalHeader()->setFixedHeight(height * 45 / 70);
	ui->tableView->verticalHeader()->setDefaultSectionSize(height * 25 / 70);
	ui->tableView->verticalHeader()->hide();
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//  ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);  //Qt-4.8.6

	ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
		"{font: 11pt 'Times New Roman';"
		"background-color: rgba(0, 130, 195, 255);"
		"color: rgba(255, 255, 255, 255);"
		"border: 0px solid black;"
		"border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
		"border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

	ui->tableView->setStyleSheet("QTableView::item{"
		"border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 120, 195, 255));"
		"border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 120, 195, 255));}");

	//  ui->tableView->show();
}

void ThirdMenuWidget::setThirdMenuName(int i, int j)
{
	currFirstNum = i;
	currSecondNum = j;
	model->clear();
	initStandardModel();
	QVariantList variantList = thirdMenuHash.values(widget->get_second_menu_list(i).at(j));
	QStringList stringList = variantList.at(0).toStringList();
	for(int k = 0; k < THIRD_MENU_NUMBER; k ++)
	{
		if(stringList.count() >= k + 1)
		{
			widgetStyleChoice(i, j, k);
			model->item(0, k)->setTextAlignment(Qt::AlignCenter);
			model->item(0, k)->setForeground(Qt::yellow);
			model->item(0, k)->setFont(QFont("Times New Roman", 11));
		} else
		{
			model->setHeaderData(k, Qt::Horizontal, "");
			ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
			QStandardItem *item = new QStandardItem(QString(tr("")));
			ui->tableView->setItemDelegateForColumn(k, comboBox);
			model->setItem(0, k, item);
			model->item(0, k)->setFlags(Qt::NoItemFlags);
		}
		QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, height * 25 / 70));
		linearGradient.setColorAt(0.4, QColor(0, 0, 0));
		linearGradient.setColorAt(1, QColor(0, 120, 195));
		linearGradient.setSpread(QGradient::PadSpread);
		model->item(0, k)->setBackground(QBrush(linearGradient));
	}
	ui->tableView->show();
}

void ThirdMenuWidget::widgetStyleChoice(int i, int j, int k)
{
	QVariantList thirdVariantList = thirdMenuHash.values(widget->get_second_menu_list(i).at(j));
	QStringList thirdStringList = thirdVariantList.at(0).toStringList();

	QFile *file = new QFile(":/json/resources/menuthree.json");
	QJsonObject jsonObject = get_json_object(file);
	file->close();
	QJsonObject subObject = get_fourth_object_list(thirdStringList.at(k), jsonObject);
	if(subObject.contains("unit")) {
		model->setHeaderData(k, Qt::Horizontal, QString(thirdStringList.at(k) + "\n(" + subObject["unit"].toString() + ")"));
	} else {
		model->setHeaderData(k, Qt::Horizontal, thirdStringList.at(k));
	}

	if(subObject.contains("style")) {
		switch(subObject["style"].toString().toInt()) {
		case 1: {
			int minimum = subObject["minimum"].toInt();
			int maximum = subObject["maximum"].toInt();
			QList<int> rangeList;
			rangeList.append(minimum);
			rangeList.append(maximum);

			DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
			doubleSpinBox->set_number_range(rangeList);

			model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			QStandardItem *item = new QStandardItem(QString::number((minimum + maximum) / 2, 'f', 2));
			model->setItem(0, k, item);
			ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
			ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
			break;
				}
		case 2: {
			QVariantList tmpList = subObject["options"].toArray().toVariantList();
			QStringList optionList;
			if(tmpList.size() != 0) {
				for(int index = 0; index < tmpList.size(); index ++) {
					QMap<QString, QVariant> map = tmpList.at(index).toMap();
					QVariant result = map.value(thirdStringList.at(k));
					optionList.append(result.toString());
				}
			} else {
				optionList.append("");
			}

			ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
			comboBox->set_comboBox_item_list(optionList);

			model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			QStandardItem *item = new QStandardItem(optionList.at(0));
			model->setItem(0, k, item);
			ui->tableView->setItemDelegateForColumn(k, comboBox);
			break;
				}
		case 3: {
			//切换字on/off
			QVariantList tmpList = subObject["label"].toArray().toVariantList();
			QStringList switchList;
			if(tmpList.size() != 0) {
				for(int index = 0; index < tmpList.size(); index ++) {
					QMap<QString, QVariant> map = tmpList.at(index).toMap();
					QVariant result = map.value(thirdStringList.at(k));
					switchList.append(result.toString());
				}
			} else {
				switchList.append("");
			}

			PushButtonDelegate *pushButton = new PushButtonDelegate(this);


			model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			QStandardItem *item = new QStandardItem(QString("on"));
			model->setItem(0, k, item);
			//          model->item(0, k)->setFlags(Qt::ItemIsEnabled);
			ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
			ui->tableView->setItemDelegateForColumn(k, pushButton);
			break;
				}
		case 0: {
			model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			QStandardItem *item = new QStandardItem(QString(""));
			model->setItem(0, k, item);
			model->item(0, k)->setFlags(Qt::NoItemFlags);
			break;
				}
		default:
			break;

		}
	} else {
		model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		QStandardItem *item = new QStandardItem(QString(""));
		model->setItem(0, k, item);
		model->item(0, k)->setFlags(Qt::NoItemFlags);
	}
}

void ThirdMenuWidget::resizeEvent(QResizeEvent *event)
{
	width = event->size().width();
	height = event->size().height();
	model->clear();
	initStandardModel();
	setThirdMenuName(currFirstNum, currSecondNum);
}

QVariantHash ThirdMenuWidget::read_json_file(QFile *file)
{
	file->open(QIODevice::ReadOnly | QIODevice::Text);
	QString str = file->readAll();
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(str.toUtf8(), &error);
	QVariantHash variantHash;
	if(error.error == QJsonParseError::NoError) {
		if(!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
			if(jsonDocument.isObject()) {
				QJsonObject jsonObject = jsonDocument.object();
				variantHash = jsonObject.toVariantHash();
			} else if(jsonDocument.isArray()) {
			}
		}
	} else {
		qDebug() << "Error Type" << error.error;
		qDebug() << "Error Message:" << error.errorString();
	}
	return variantHash;
}

QJsonObject ThirdMenuWidget::get_json_object(QFile *file)
{
	file->open(QIODevice::ReadOnly | QIODevice::Text);
	QString str = file->readAll();
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(str.toUtf8(), &error);
	QJsonObject jsonObject;
	if(error.error == QJsonParseError::NoError) {
		if(!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
			if(jsonDocument.isObject()) {
				jsonObject = jsonDocument.object();
			} else if(jsonDocument.isArray()) {
			}
		}
	} else {
		qDebug() << "Error Type" << error.error;
		qDebug() << "Error Message:" << error.errorString();
	}
	return jsonObject;
}

QJsonObject ThirdMenuWidget::get_fourth_object_list(QString string, QJsonObject jsonObject)
{
	QJsonObject subObject;
	if(jsonObject.contains(string)) {
		if(jsonObject[string].isObject()) {
			subObject = jsonObject[string].toObject();
		}
	}
	return subObject;
}

//void ThirdMenuWidget::paintBorder()
//{
//  QPainter painter(ui->tableView);
//  QLinearGradient linearGradientOne(QPointF(0, 0), QPointF(0, height * 25 / 70));
//  linearGradientOne.setColorAt(0.158192, QColor(255, 255, 255));
//  linearGradientOne.setColorAt(0.757062, QColor(0, 120, 195));
//  QLinearGradient linearGradientTwo(QPointF(0, 0), QPointF(0, height * 25 / 70));
//  linearGradientTwo.setColorAt(0.158192, QColor(0, 0, 0));
//  linearGradientTwo.setColorAt(0.757062, QColor(0, 120, 195));
//  painter.setBrush(linearGradientOne);

//  for(int i = 0; i < 6; i ++)
//  {
//    painter.drawRect(i * width / 6, 0, 1, height);
//  }
//  painter.setBrush(linearGradientTwo);
//  for(int i = 0; i < 6; i ++)
//  {
//    painter.drawRect((i + 1) * (width / 6), 0, 1, height);
//  }
//  update();
//}

//bool ThirdMenuWidget::eventFilter(QObject *object, QEvent *event)
//{
//  if(object == ui->tableView && event->type() == QEvent::Paint)
//  {
//    paintBorder();
//  }
//  return QWidget::eventFilter(object, event);
//}
