#include "measure_dialog.h"
#include "ui_measure_dialog.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDebug>

MeasureDialog::MeasureDialog(QWidget *parent, MeasureDialog::MeasureType type) :
    QDialog(parent),
    ui(new Ui::MeasureDialog)
{
    ui->setupUi(this);

    setWindowFlags( (windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::FramelessWindowHint);

    ui->listWidget->setCurrentRow(type);

    pMcu = Mcu::get_mcu();
    connect(pMcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(pMcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
}

MeasureDialog::~MeasureDialog()
{
    delete ui;
}

MeasureDialog::MeasureType MeasureDialog::get_type() const
{
    return (MeasureDialog::MeasureType)ui->listWidget->currentRow();
}

QString MeasureDialog::get_type_string()
{
    QString measureType = ui->listWidget->currentItem()->text();

    if(measureType.contains(" ") == true) {
        int index = measureType.indexOf(" ");
        QString text = measureType.left(index);

        if(measureType.contains("%") || measureType.contains("Percentage")) {
            text = text + "\n(%)";
        } else if(measureType.contains("dB")) {
            text = text + "\n(dB)";
        } else {
            text = text + "\n(mm)";
        }
        m_measureTypeMap.insert(text, measureType);
    } else {
        m_measureTypeMap.insert(measureType, measureType);
    }

    return m_measureTypeMap.key(measureType);
}

void MeasureDialog::set_type(MeasureDialog::MeasureType type)
{
    ui->listWidget->setCurrentRow(type);
}

void MeasureDialog::do_rotary_event(Mcu::RotaryType type)
{
    if (type == Mcu::ROTARY_UP) {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        QApplication::sendEvent(ui->listWidget, event);

    } else {
        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
        QApplication::sendEvent(ui->listWidget, event);
    }
}

void MeasureDialog::key_sure(Mcu::KeyType key)
{
    if(key == Mcu::KEY_SURE) {
        accept();
    }
}
