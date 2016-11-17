#include "topmenu.h"
#include "ui_topmenu.h"

#include "doublespinboxdelegate.h"
#include "thirdmenuwidget.h"
#include "firstsecondmenuwidget.h"

#include <QDebug>

#define HTML_TEXT_ONE "<font color=yellow face='Times New Roman' style=font-size:14pt>"
#define HTML_TEXT_TWO "</font><br>"
#define HTML_TEXT_THREE "<font color=yellow face='Times New Roman' style=font-size:12pt>"
#define HTML_TEXT_FOUR "</font>"
#define HTML_TEXT_FIVE "<font color=white face='Times New Roman' style='font-size:14pt'>"
#define HTML_TEXT_SIX  "<font color=white face='Times New Roman' style='font-size:12pt'>"



TopMenu :: TopMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopMenu)
{
    ui->setupUi(this);
    init_ui();

    init_gain_angle();

}

TopMenu :: ~TopMenu()
{
    delete(ui);
}

void TopMenu::retranslate_top_menu_ui()
{
    ui->retranslateUi(this);
}

void TopMenu::init_ui()
{
    set_top_menu_font();

    for(int i = 0; i < TOP_MENU_NUMBER; i ++) {
        measurementLabelList.at(i)->installEventFilter(this);
    }
}

void TopMenu::set_top_menu_font()
{
    for(int i = 1; i <= TOP_MENU_NUMBER; i ++){
        QLabel *label = findChild<QLabel*>("label_" + QString::number(i));
        measurementLabelList.append(label);

        QString str = label->text();
        QString text1, text2;

        if(str.contains("\n") == true) {
            int index = str.indexOf("\n");
            text1 = str.left(index);
            text2 = str.right(str.length() - index - 1);

            if(i == 1 || i == TOP_MENU_NUMBER){
                label->setText(HTML_TEXT_ONE + text1 + HTML_TEXT_TWO + HTML_TEXT_THREE + text2 + HTML_TEXT_FOUR);
            }else{
                label->setText(HTML_TEXT_FIVE + text1 + HTML_TEXT_TWO + HTML_TEXT_SIX + text2 + HTML_TEXT_FOUR);
            }
        }
    }
}

void TopMenu::init_gain_angle()
{
#if QT_VERSION >= 0x050000
    ui->tableView_gain->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_gain->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

#if QT_VERSION < 0x050000
    ui->tableView_gain->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView_gain->verticalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ui->tableView_gain->horizontalHeader()->hide();
    ui->tableView_gain->verticalHeader()->hide();

    pGain = new QStandardItemModel(1, 2, this);
    ui->tableView_gain->setModel(pGain);

    ThirdMenuWidget *thirdMenuWidget = new ThirdMenuWidget;
    FirstSecondMenuWidget *mainMenuWidget = new FirstSecondMenuWidget;
    QFile *file = new QFile(":/file/json/menuconf.json");
    QVariantMap map = mainMenuWidget->read_json_file(file);

    QVariantMap firstMapOne = map["UT Settings"].toMap();
    QVariantMap secondMapOne = firstMapOne["General"].toMap();
    QVariantMap variantMapGain = secondMapOne["Gain"].toMap();

    QVariantMap firstMapTwo = map["Focal Law"].toMap();
    QVariantMap secondMapTwo = firstMapTwo["Angle"].toMap();
    QVariantMap variantMapAngle = secondMapTwo["Min. Angle"].toMap();

    int decimalGain = variantMapGain["decimal"].toInt();
    QList<int> rangeListGain = thirdMenuWidget->get_spinBox_range_list(variantMapGain);
    QStringList stepListGain = thirdMenuWidget->get_spinBox_step_list(variantMapGain);

    DoubleSpinBoxDelegate *doubleSpinBoxOne = new DoubleSpinBoxDelegate(this);
    doubleSpinBoxOne->set_number_range(rangeListGain);
    doubleSpinBoxOne->set_number_step_list(stepListGain);
    doubleSpinBoxOne->set_number_step(stepListGain.at(0));
    doubleSpinBoxOne->set_decimal_amount(decimalGain);

    QStandardItem *item_gain1 = new QStandardItem(QString::number(100, 'f', decimalGain));
    QStandardItem *item_gain2 = new QStandardItem("(" + QString::number(10, 'f', decimalGain) + ")");
    pGain->setItem(0, 0, item_gain1);
    pGain->setItem(0, 1, item_gain2);
    pGain->item(0, 0)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    pGain->item(0, 1)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    pGain->item(0, 0)->setForeground(Qt::white);
    pGain->item(0, 1)->setForeground(Qt::yellow);
    pGain->item(0, 0)->setFont(QFont("Times New Roman", 14));
    pGain->item(0, 1)->setFont(QFont("Times New Roman", 10));

    ui->tableView_gain->setItemDelegate(doubleSpinBoxOne);
    ui->tableView_gain->show();

#if QT_VERSION >= 0x050000
    ui->tableView_angle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_angle->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

#if QT_VERSION < 0x050000
    ui->tableView_angle->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView_angle->verticalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ui->tableView_angle->horizontalHeader()->hide();
    ui->tableView_angle->verticalHeader()->hide();

    pAngle = new QStandardItemModel(1, 1, this);
    ui->tableView_angle->setModel(pAngle);

    int decimalAngle = variantMapAngle["decimal"].toInt();
    QList<int> rangeListAngle = thirdMenuWidget->get_spinBox_range_list(variantMapAngle);
    QStringList stepListAngle = thirdMenuWidget->get_spinBox_step_list(variantMapAngle);

    DoubleSpinBoxDelegate *doubleSpinBoxAngle = new DoubleSpinBoxDelegate(this);
    doubleSpinBoxAngle->set_number_range(rangeListAngle);
    doubleSpinBoxAngle->set_number_step_list(stepListAngle);
    doubleSpinBoxAngle->set_number_step(stepListAngle.at(0));
    doubleSpinBoxAngle->set_decimal_amount(decimalAngle);

    QStandardItem *item_angle = new QStandardItem(QString::number(70, 'f', decimalAngle));
    pAngle->setItem(0, item_angle);
    pAngle->item(0)->setTextAlignment(Qt::AlignCenter);
    pAngle->item(0)->setForeground(Qt::white);
    pAngle->item(0)->setFont(QFont("Times New Roman", 14));
    ui->tableView_angle->setItemDelegate(doubleSpinBoxAngle);
    ui->tableView_angle->show();

    connect(ui->tableView_gain->itemDelegate(), SIGNAL(closeEditor(QWidget*)), this, SLOT(set_gain_header_text_close(QWidget*)));
    connect(ui->tableView_angle->itemDelegate(), SIGNAL(closeEditor(QWidget*)), this, SLOT(set_angle_header_text_close(QWidget*)));
}

bool TopMenu::eventFilter(QObject *object, QEvent *event)
{
    if((object == measurementLabelList.at(1) ||
            object == measurementLabelList.at(2) ||
            object == measurementLabelList.at(3) ||
            object == measurementLabelList.at(4) ||
            object == measurementLabelList.at(5) ||
            object == measurementLabelList.at(6) ||
            object == measurementLabelList.at(7) ||
            object == measurementLabelList.at(8)) &&
            event->type() == QEvent::MouseButtonPress) {
        objectName = object->objectName();
        pDialog = new MeasurementDialog;
        pDialog->setModal(true);
        pDialog->setWindowFlags(Qt::FramelessWindowHint);
        pDialog->show();

        QLabel *label = qobject_cast<QLabel*>(object);
        QString string = label->text();
        QString text;
        if(string.contains(HTML_TEXT_FIVE)) {
            QString firstHtmlString = HTML_TEXT_FIVE;
            QString text1 = string.right(string.length() - string.indexOf(firstHtmlString) - firstHtmlString.length());
            if(text1.contains(HTML_TEXT_TWO)) {
                text = text1.left(text1.indexOf(HTML_TEXT_TWO));
            } else if(text1.contains(HTML_TEXT_FOUR)) {
                text = text1.left(text1.indexOf(HTML_TEXT_FOUR));
            }
        } else {
            text = string;
        }

        pDialog->set_current_index(text);

        connect(pDialog, SIGNAL(labelTextChanged(QString)), this, SLOT(change_labelText(QString)));
    } else if(object == measurementLabelList.at(0) && event->type() == QEvent::MouseButtonPress) {
        open_editor_and_set_header_text(measurementLabelList.at(0), ui->tableView_gain, pGain, 0);

    } else if(object == measurementLabelList.at(9) && event->type() == QEvent::MouseButtonPress) {
        open_editor_and_set_header_text(measurementLabelList.at(9), ui->tableView_angle, pAngle, 0);

    }
    return QWidget::eventFilter(object, event);
}

void TopMenu::change_labelText(QString str)
{
    for(int i = 1; i < TOP_MENU_NUMBER; i++) {
        if(measurementLabelList.at(i)->objectName() == objectName ){
            QString text1, text2;
            if(str.contains("\n") == true) {
                int index = str.indexOf("\n");
                text1 = str.left(index);
                text2 = str.right(str.length() - index - 1);
                measurementLabelList.at(i)->setText(HTML_TEXT_FIVE + text1 + HTML_TEXT_TWO + HTML_TEXT_SIX + text2 + HTML_TEXT_FOUR);
            } else {
                measurementLabelList.at(i)->setText(HTML_TEXT_FIVE + str + HTML_TEXT_FOUR);
            }
            break;
        }
    }
}

QStringList TopMenu::get_label_text(QString string)
{
    QString text, textUnit;
    QStringList stringList;
    if(string.contains(HTML_TEXT_ONE)) {
        QString firstHtmlString = HTML_TEXT_ONE;
        QString text1 = string.right(string.length() - string.indexOf(firstHtmlString) - firstHtmlString.length());
        if(text1.contains(HTML_TEXT_TWO)) {
            text = text1.left(text1.indexOf(HTML_TEXT_TWO));
            if(text1.contains(HTML_TEXT_THREE)) {
                QString secondHtmlString = HTML_TEXT_THREE;
                QString text2 = text1.right(text1.length() - text1.indexOf(secondHtmlString) - secondHtmlString.length());
                if(text2.contains(HTML_TEXT_FOUR)) {
                   textUnit = text2.left(text2.indexOf(HTML_TEXT_FOUR));
                }
            }
        } else if(text1.contains(HTML_TEXT_FOUR)) {
            text = text1.left(text1.indexOf(HTML_TEXT_FOUR));
            textUnit = "";
        }
    } else {
        text = string;
        textUnit = "";
    }
    stringList.append(text);
    stringList.append(textUnit);
    return stringList;
}

void TopMenu::open_editor_and_set_header_text(QLabel *label, QTableView *tableView, QStandardItemModel *model, int index)
{
    QString headerTextUnit;
    QModelIndex modelIndex = model->item(0, index)->index();
    DoubleSpinBoxDelegate *doubleSpinBox = static_cast<DoubleSpinBoxDelegate*>(tableView->itemDelegate(modelIndex));


    QStringList stringList = get_label_text(label->text());
    QString headerText = stringList.at(0);
    QString textUnit = stringList.at(1);


    if(textUnit.contains("Δ")) {
        headerTextUnit = textUnit.left(textUnit.indexOf("Δ"));
    } else {
        headerTextUnit = textUnit;
    }

    QString currentStep = doubleSpinBox->get_number_step();
    int stepIndex = 0;
    QStringList stepList = doubleSpinBox->stepList;
    for(int i = 0; i < stepList.count(); i ++) {
        if(currentStep == stepList.at(i)) {
            stepIndex = i;
            break;
        }
    }

    if(!doubleSpinBox->m_editFlag) {
        tableView->edit(modelIndex);
        label->setText(HTML_TEXT_ONE + headerText + HTML_TEXT_TWO + HTML_TEXT_THREE +
                                            headerTextUnit + "Δ" + stepList.at(stepIndex) + HTML_TEXT_FOUR);

    } else {
        if(stepIndex == (stepList.count() - 1)) {
            doubleSpinBox->set_number_step(stepList.at(0));
            label->setText(HTML_TEXT_ONE + headerText + HTML_TEXT_TWO + HTML_TEXT_THREE +
                                                headerTextUnit + "Δ" + stepList.at(0) + HTML_TEXT_FOUR);
        } else {
            doubleSpinBox->set_number_step(stepList.at(stepIndex + 1));
            label->setText(HTML_TEXT_ONE + headerText + HTML_TEXT_TWO + HTML_TEXT_THREE +
                                                headerTextUnit + "Δ" + stepList.at(stepIndex + 1) + HTML_TEXT_FOUR);
        }
    }
}

void TopMenu::set_gain_header_text_close(QWidget *editor)
{
    Q_UNUSED(editor);
    set_header_text_close(measurementLabelList.at(0));
}

void TopMenu::set_angle_header_text_close(QWidget *editor)
{
    Q_UNUSED(editor);
    set_header_text_close(measurementLabelList.at(9));
}

void TopMenu::set_header_text_close(QLabel *label)
{
    QString string = label->text();
    QStringList stringList = get_label_text(string);
    QString headerText = stringList.at(0);
    QString textUnit = stringList.at(1);
    if(textUnit.contains("Δ")) {
        textUnit = textUnit.left(textUnit.indexOf("Δ"));
        label->setText(HTML_TEXT_ONE + headerText + HTML_TEXT_TWO + HTML_TEXT_THREE + textUnit  + HTML_TEXT_FOUR);
    } else {
        label->setText(HTML_TEXT_ONE + headerText + HTML_TEXT_TWO + HTML_TEXT_THREE + textUnit  + HTML_TEXT_FOUR);
    }
}

void TopMenu::on_tableView_angle_clicked(const QModelIndex &index)
{
    DoubleSpinBoxDelegate *doubleSpinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView_angle->itemDelegate(index));
    if(!doubleSpinBox->m_editFlag) {
        ui->tableView_angle->edit(index);
    }
}

void TopMenu::on_tableView_gain_clicked(const QModelIndex &index)
{
    DoubleSpinBoxDelegate *doubleSpinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView_gain->itemDelegate(index));
    if(!doubleSpinBox->m_editFlag) {
        ui->tableView_gain->edit(index);
        if(index.column() == 1) {
            QDoubleSpinBox *editor = doubleSpinBox->spinBoxList.at(doubleSpinBox->spinBoxList.count() - 1);
            editor->setPrefix("(");
            editor->setSuffix(")");
        }
    }
}
