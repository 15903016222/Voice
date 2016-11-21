#include "commonmenuwidget.h"
#include "ui_commonmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"
#include "pushbuttondelegate.h"

#include <QResizeEvent>
#include <QDebug>

static const char* COMMON_MENU_STRING[COMMON_MENU_NUMBER] = {
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Start\n(mm)"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Range\n(mm)"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Velocity\n(m/s)"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Video Filter"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Reset Config"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Gate"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Focal Depth\n(mm)")
};

CommonMenuWidget::CommonMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonMenuWidget)
{
    ui->setupUi(this);
    this->resize(800, 70);
    m_height = this->geometry().height();
    set_common_menu_name();

    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));

    opendSpinBoxIndex = -1;
    m_keyboardShowFlag = false;
    pTableView = ui->tableView;
}

CommonMenuWidget::~CommonMenuWidget()
{
    delete ui;
}

void CommonMenuWidget::retranslate_common_menu_ui()
{
    ui->retranslateUi(this);
}

void CommonMenuWidget::init_standard_model()
{
    model = new QStandardItemModel(1, COMMON_MENU_NUMBER, this);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setFixedHeight(m_height * 45 / 70);
    ui->tableView->verticalHeader()->setDefaultSectionSize(m_height * 25 / 70);
    ui->tableView->verticalHeader()->hide();

#if QT_VERSION >= 0x050000
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

#if QT_VERSION < 0x050000
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                     "{font: 13pt 'Times New Roman';background-color: rgba(0, 130, 195, 255);"
                                                     "color:rgba(255, 255, 255, 255);"
                                                     "border: 0px solid black;"
                                                     "border-left:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.068, x2:0.5, y2:0.75,"
                                                     "stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
                                                     "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1,"
                                                     "stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

    ui->tableView->setStyleSheet("QTableView::item{"
        "color: yellow;"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
        "border-left:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(255, 255, 255, 255), stop:1 rgba(0, 120, 195, 255));"
        "border-right:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));}");

    for(int k = 0; k < COMMON_MENU_NUMBER; k++)
    {
        QModelIndex index = model->index(k, 0, QModelIndex());
        model->setData(index, k);
    }

    ui->tableView->show();
}

void CommonMenuWidget::set_common_menu_name()
{
    init_standard_model();
    for(int k = 0; k < COMMON_MENU_NUMBER; k ++) {
        if(COMMON_MENU_STRING[k] != NULL) {
            choose_widget_style(k);
            model->item(0, k)->setTextAlignment(Qt::AlignCenter);
            model->item(0, k)->setFont(QFont("Times New Roman", 12));
        }
    }
}

void CommonMenuWidget::choose_widget_style(int k)
{
    model->setHeaderData(k, Qt::Horizontal, tr(COMMON_MENU_STRING[k]));
    switch(CHOICE_WIDGET_CHAR[k].toInt()) {
    case 1: {
        QList<int> rangeList;
        rangeList.append(0.00);
        rangeList.append(1000.00);
        QStringList stepList;
        stepList.append("0.01");
        stepList.append("0.10");
        stepList.append("1.00");
        stepList.append("10.00");
        int decimal = 2;

        DoubleSpinBoxDelegate *lineEdit = new DoubleSpinBoxDelegate(this);
        lineEdit->set_number_range(rangeList);
        lineEdit->set_number_step_list(stepList);
        lineEdit->set_number_step(stepList.at(0));
        lineEdit->set_decimal_amount(decimal);

        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString::number(0, 'f', decimal));
        model->setItem(0, k, item);
        ui->tableView->setItemDelegateForColumn(k, lineEdit);

        connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(createEditorHeaderText(QStringList)), this, SLOT(set_header_text_create(QStringList)));
        connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(closeEditor(QWidget*)), this, SLOT(set_header_text_close(QWidget*)));
        break;
    }
    case 2: {

        ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);

        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString("On"));
        model->setItem(0, k, item);
        ui->tableView->setItemDelegateForColumn(k, comboBox);
        connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(comboBox_current_text(QString)), this, SLOT(change_related_third_menu_data(QString)));
        break;
    }
    case 3: {
        PushButtonDelegate *pushButton = new PushButtonDelegate(this);

        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString("on"));
        model->setItem(0, k, item);
        model->item(0, k)->setFlags(Qt::NoItemFlags);
        ui->tableView->setItemDelegateForColumn(k, pushButton);
        break;
    }
    case 0: {
        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString("on"));
        model->setItem(0, k, item);
        model->item(0, k)->setFlags(Qt::NoItemFlags);
        break;
    }
    default:
        break;
    }
}

void CommonMenuWidget::resizeEvent(QResizeEvent *event)
{
    m_width = event->size().width();
    m_height = event->size().height();
    set_common_menu_name();
}

void CommonMenuWidget::onHeaderClicked(int index)
{
    QString currentHeaderText =  model->horizontalHeaderItem(index)->text();
    QModelIndex modelIndex = model->item(0, index)->index();
    if(CHOICE_WIDGET_CHAR[index].toInt() == 1) {
        //点击表头更改spinbox的步进及表头文字
        DoubleSpinBoxDelegate *lineEdit = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
        QString headerText;
        if(currentHeaderText.contains("Δ")) {
            headerText = currentHeaderText.left(currentHeaderText.indexOf("Δ"));
        } else {
            headerText = currentHeaderText;
        }

        QString currentStep = lineEdit->get_number_step();
        int stepIndex = 0;
        QStringList stringList = lineEdit->stepList;
        for(int i = 0; i < stringList.count(); i ++) {
            if(currentStep == stringList.at(i)) {
                stepIndex = i;
                break;
            }
        }

        if(!lineEdit->m_editFlag) {
            ui->tableView->edit(modelIndex);
            model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex)));
        } else {
            if(stepIndex == (stringList.count() - 1)) {
                lineEdit->set_number_step(stringList.at(0));
                model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(0)));
            } else {
                lineEdit->set_number_step(stringList.at(stepIndex + 1));
                model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex + 1)));
            }
        }

//        if(opendSpinBoxIndex >= 0) {
//            change_persistent_editor();
//        }

        if(m_keyboardShowFlag) {
            model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex)));
        } else if(!lineEdit->m_editFlag) {
            ui->tableView->edit(modelIndex);
            model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex)));
        } else {
            if(stepIndex == (stringList.count() - 1)) {
                lineEdit->set_number_step(stringList.at(0));
                model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(0)));
            } else {
                lineEdit->set_number_step(stringList.at(stepIndex + 1));
                model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex + 1)));
            }
        }
        if(opendSpinBoxIndex != index) {
            opendSpinBoxIndex = index;
            if(m_keyboardShowFlag) {
                ui->tableView->openPersistentEditor(modelIndex);
            }
        }
    } else if(CHOICE_WIDGET_CHAR[index].toInt() == 2) {
        ComboBoxDelegate *comboBox = static_cast<ComboBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
        ui->tableView->edit(modelIndex);
        QPoint point = QPoint();
        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, point, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(comboBox->comboBoxList.at(comboBox->comboBoxList.count() - 1), event);
    } else if(CHOICE_WIDGET_CHAR[index].toInt() == 3) {
        PushButtonDelegate *pushButton = static_cast<PushButtonDelegate*>(ui->tableView->itemDelegateForColumn(index));
        pushButton->change_button_text(modelIndex);
        model->setData(modelIndex, pushButton->buttonMap.value(modelIndex)->text, Qt::EditRole);
    }

    if(CHOICE_WIDGET_CHAR[index].toInt() != 1 && opendSpinBoxIndex >= 0) {
        opendSpinBoxIndex = -1;
    }
}

void CommonMenuWidget::set_header_text_create(QStringList stringList) const
{
    QString string = stringList.at(0);
    int index = string.toInt();
    QString headerText;
    QString currentHeaderText = model->horizontalHeaderItem(index)->text();
    if(currentHeaderText.contains("Δ")) {
        headerText = currentHeaderText.left(currentHeaderText.indexOf("Δ"));
    } else {
        headerText = currentHeaderText;
    }
    model->setHeaderData(index, Qt::Horizontal,QString(headerText + "Δ" + stringList.at(1)));
}

void CommonMenuWidget::set_header_text_close(QWidget *editor)
{
    int editorPosX = editor->x() + editor->width();
    int column = editorPosX / (m_width / COMMON_MENU_NUMBER) - 1;
    QString currentHeaderText = model->horizontalHeaderItem(column)->text();
    if(currentHeaderText.contains("Δ")) {
        model->setHeaderData(column, Qt::Horizontal,QString(currentHeaderText.left(currentHeaderText.indexOf("Δ"))));
    } else {
        model->setHeaderData(column, Qt::Horizontal,QString(currentHeaderText));
    }
}

void CommonMenuWidget::on_tableView_clicked(const QModelIndex &index)
{
    int column = index.column();
    if(CHOICE_WIDGET_CHAR[column].toInt() == 1) {
        int column = index.column();
        if(!m_keyboardShowFlag) {
            ui->tableView->edit(index);
        }

//        if(opendSpinBoxIndex >= 0) {
//            change_persistent_editor();
//        }
        if(opendSpinBoxIndex != column) {
            opendSpinBoxIndex = column;
//            if(m_keyboardShowFlag) {
//                ui->tableView->openPersistentEditor(index);
//            }
        }
        ui->tableView->edit(index);
    } else if(CHOICE_WIDGET_CHAR[column].toInt() == 2) {
        ComboBoxDelegate *comboBox = static_cast<ComboBoxDelegate*>(ui->tableView->itemDelegateForColumn(index.column()));
        ui->tableView->edit(index);
        QPoint point = QPoint();
        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, point, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(comboBox->comboBoxList.at(comboBox->comboBoxList.count() - 1), event);
    }

    if(CHOICE_WIDGET_CHAR[column].toInt() != 1 && opendSpinBoxIndex >= 0) {
        opendSpinBoxIndex = -1;
    }
}

//void CommonMenuWidget::change_persistent_editor()
//{
//    if(m_keyboardShowFlag) {
//        QModelIndex modelIndexLast = model->item(0, opendSpinBoxIndex)->index();
//        DoubleSpinBoxDelegate *lineEdit = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(opendSpinBoxIndex));

//        ui->tableView->closePersistentEditor(modelIndexLast);
//        set_header_text_close(lineEdit->spinBoxList.at(lineEdit->spinBoxList.count() -1));
//        lineEdit->spinBoxList.at(lineEdit->spinBoxList.count() -1)->clearFocus();
//        lineEdit->m_editFlag = false;
////        lineEdit->m_keyboardFlag = false;
//        lineEdit->m_inputCount = 0;
//    }
//}
