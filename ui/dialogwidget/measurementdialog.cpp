#include "measurementdialog.h"
#include "ui_measurementdialog.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDebug>

#define MEASUREMENT_NUMBER 54
static const char* MEASUREMENT_STRING[MEASUREMENT_NUMBER] =
{
    QT_TRANSLATE_NOOP("MeasurementDialog", "A% Peak amplitude in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AdBA Signal in gate minus gate level for gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AdBr Difference between signal and reference in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "B% Peak amplitude in gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "BdBB Signal in gate minus gate level for gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "BdBr Difference between signal and reference in gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "A^ Position in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "B^ Position in gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "I/ Position in gate I"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "I(W)/ Position in gate I in water"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "T(A^) Thickness"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "ML Percentage of Material loss"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "%(r) Amplitude value for reference cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "%(m) Amplitude value of the measurement cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "%(m-r) Amplitude (measurement cursor - reference cursor)"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "U(r) Ultrasonic position of the reference cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "U(m) Ultrasonic position of the measurement cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "U(m-r) Ultrasonic axix(measurement cursor - reference cursor)"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "P(r) Probe position of the reference cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "P(m) Probe position of the measurement cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "P(m-r) Probe (measurement cursor - reference cursor)"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "S(r)  Scan position of the reference cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "S(m)  Scan position of the measurment cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "S(m-r)  Scan (measurement cursor - reference cursor)"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "I(r) Index position of the reference cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "I(m) Index position of the measurement cursor"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "I(m-r) Index axis(measurement cursor - reference cursor)"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "RA^ Reference point to the indication in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "RB^ Reference point to the indication in gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "PA^ Probe front face to the indication in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "PB^ Probe front face to the indication in gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "DA^ Depth of the indication in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "DB^ Depth of the indication in gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "SA^ Sound path of the indication in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "SB^ Sound path of the indication in gate B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "ViA^ Volumetric position in gate A on the index axis"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "ViB^ Volumetric position in gate B on the index axis"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "VsA^ Volumetric position in gate A on the scan axis"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "VsB^ Volumetric position in gate B on the scan axis"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "LA^ Leg(skip)of the indication in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "LB^ Leg(skip)of the indication in gate B"),
 //   QT_TRANSLATE_NOOP("MeasurementDialog", "E% Peak amplitude of the envelop in gate A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-DA Indication level for AWS-D1.5A"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-DB Zero reference  level for AWS-D1.5B"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-DC Attenuation factor for AWS-D1.5 C"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-DD Indication rating for AWS-D1.5D"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-D45 Discontinuity severity class for AWS-D1.5 45"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-D60 Discontinuity severity class for AWS-D1.5 60"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-D70 Discontinuity severity class for AWS-D1.5 70"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "AWS-D CL Discontinuity severity class for AWS-D1.5"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "DA-DI"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "T-D(r) TOFD Ultrasonic Axis Reference Cursor Depth"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "T-D(m) TOFD Ultrasonic Axis Measure Cursor Depth"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "T-S(m-r) TOFD Scan Axis Cursor Space"),
    QT_TRANSLATE_NOOP("MeasurementDialog", "T-D(m-r) TOFD Ultrasonic Axis Cursor Height")
};

MeasurementDialog::MeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasurementDialog)
{
    ui->setupUi(this);

    init_ui();

    m_changedFlag = false;

    pMcu = Mcu::get_mcu();
    connect(pMcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(pMcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
}

MeasurementDialog::~MeasurementDialog()
{
    delete ui;
}

void MeasurementDialog::init_ui()
{
    buttonList.append(ui->pushButton_cancel);
    buttonList.append(ui->pushButton_ok);

    pMeasurementModel = new QStandardItemModel(this);

    for(int i = 0; i < MEASUREMENT_NUMBER; i++) {
        measurementList.append(tr(MEASUREMENT_STRING[i]));

        QString string = static_cast<QString>(measurementList.at(i));
        QStandardItem *item = new QStandardItem(string);
        pMeasurementModel->appendRow(item);
        item->setForeground(QBrush(Qt::black));
        item->setFont(QFont("Times New Roman", 14));

        QString str = MEASUREMENT_STRING[i];

        if(str.contains(" ") == true) {
            int index = str.indexOf(" ");
            QString text = str.left(index);

            if(str.contains("%") || str.contains("Percentage")) {
                text = text + "\n(%)";
            } else if(str.contains("dB")) {
                text = text + "\n(dB)";
            } else {
                text = text + "\n(mm)";
            }
            labelMap.insert(text, tr(MEASUREMENT_STRING[i]));
        } else {
            labelMap.insert(str, tr(MEASUREMENT_STRING[i]));
        }
    }

    pListView = new QListView(this);
    pListView->resize(ui->scrollArea->geometry().width(), 800);
    pListView->setSpacing(3);
    pListView->setEditTriggers(QAbstractItemView::EditKeyPressed);

    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidget(pListView);
    pListView->setModel(pMeasurementModel);
    pListView->setFrameShape(QFrame::NoFrame);
    pListView->setStyleSheet("QListView{outline: 0px;}"
                            "QListView::item{"
                            "background-color: rgba(0, 0, 0, 0);"
                            "color: black;}"
                            "QListView::item:Selected{"
                            "border: 1px solid rgba(180, 180, 180, 255);"
                            "background-color: rgba(85, 175, 255, 80);"
                            "color: red;}"
                            "QListView::item:hover{"
                            "border: 1px solid rgba(180, 180, 180, 255);"
                            "background-color: rgba(85, 175, 255, 20);"
                            "color: red;}");

    connect(pListView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_listViewItemClicked(QModelIndex)));
}

void MeasurementDialog::on_pushButton_cancel_clicked()
{
    close();
}

void MeasurementDialog::on_pushButton_ok_clicked()
{
    if(m_changedFlag) {
        emit labelTextChanged(m_changedString);
        close();
    }
}

void MeasurementDialog::slot_listViewItemClicked(QModelIndex index)
{
    m_changedFlag = true;

    QStandardItem *item = pMeasurementModel->itemFromIndex(index);
    m_changedString = labelMap.key(item->text());
}

void MeasurementDialog::set_current_index(QString string)
{
    for(int i = 0; i < MEASUREMENT_NUMBER; i ++) {
        QString longString = MEASUREMENT_STRING[i];

        if(longString.contains(string)) {
            QStandardItem *item = pMeasurementModel->item(i);

            m_currentRow = item->row();
            qDebug()<<"set_current_index_row = "<<m_currentRow<<"  set_current_MEASURE = "<<m_changedString;

            QModelIndex modelIndex = pMeasurementModel->indexFromItem(item);
            pListView->setCurrentIndex(modelIndex);
            break;
        }
    }
}

void MeasurementDialog::do_rotary_event(Mcu::RotaryType type)
{
    m_changedFlag = true;

    if (type == Mcu::ROTARY_UP) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        QApplication::sendEvent(pListView, event);

        if(m_currentRow > 0){
            m_currentRow--;
        }

    } else {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
        QApplication::sendEvent(pListView, event);

        if(m_currentRow < MEASUREMENT_NUMBER -1){
            m_currentRow++;
        }
    }

    QStandardItem *item = pMeasurementModel->item(m_currentRow);
    m_changedString = labelMap.key(item->text());

    qDebug()<<"do_rotaryRow = "<<m_currentRow<<"  value"<<m_changedString;
}

void MeasurementDialog::key_sure(Mcu::KeyType key)
{
    if(key == Mcu::KEY_SURE) {
        on_pushButton_ok_clicked();
    }
}
