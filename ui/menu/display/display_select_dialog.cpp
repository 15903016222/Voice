#include "display_select_dialog.h"
#include "ui_display_select_dialog.h"
#include "mode_list_widget_item.h"

#include <device/device.h>

#include <QCheckBox>
#include <QSpacerItem>
#include <QPushButton>

DisplaySelectDialog::DisplaySelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplaySelectDialog),
    m_listWidget(NULL)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    DplDevice::Device *dev = DplDevice::Device::get_instance();
    int grpQty = dev->groups();
    grpQty = 8;

    for (int i = grpQty+1; i <= 8; ++i) {
        QCheckBox *checkBox = findChild<QCheckBox *>("checkBox_"+QString::number(i));
        if (checkBox) {
            checkBox->hide();
        }
    }

    connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_1, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_2, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_3, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_4, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_5, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_6, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_7, SIGNAL(clicked()), this, SLOT(update_list_widget()));
    connect(ui->checkBox_8, SIGNAL(clicked()), this, SLOT(update_list_widget()));
}

DisplaySelectDialog::~DisplaySelectDialog()
{
    delete ui;
}

void DisplaySelectDialog::update_list_widget()
{
    bool allGrp = ui->checkBox->isChecked();
    int grpQty = 0;

    ui->checkBox_1->setDisabled(allGrp);
    ui->checkBox_2->setDisabled(allGrp);
    ui->checkBox_3->setDisabled(allGrp);
    ui->checkBox_4->setDisabled(allGrp);
    ui->checkBox_5->setDisabled(allGrp);
    ui->checkBox_6->setDisabled(allGrp);
    ui->checkBox_7->setDisabled(allGrp);
    ui->checkBox_8->setDisabled(allGrp);

    if (allGrp) {
        grpQty = DplDevice::Device::get_instance()->groups();
    } else {
        grpQty = ui->checkBox_1->isChecked()
                + ui->checkBox_2->isChecked()
                + ui->checkBox_3->isChecked()
                + ui->checkBox_4->isChecked()
                + ui->checkBox_5->isChecked()
                + ui->checkBox_6->isChecked()
                + ui->checkBox_7->isChecked()
                + ui->checkBox_8->isChecked();
    }

    if (m_listWidget != NULL) {
        delete m_listWidget;
    }
    m_listWidget = new QListWidget(this);
    m_listWidget->setIconSize(QSize(ModeListWidgetItem::W_SIZE, ModeListWidgetItem::H_SIZE));
    m_listWidget->setResizeMode(QListView::Adjust);
    m_listWidget->setViewMode(QListView::IconMode);
    m_listWidget->setMovement(QListView::Static);
    m_listWidget->setSpacing(20);

    switch (grpQty) {
    case 1:
        update1();
        break;
    case 2:
        update2();
        break;
    case 3:
        update3();
        break;
    case 4:
        update4();
        break;
    case 5:
        update5();
        break;
    case 6:
        update6();
        break;
    case 7:
        update7();
        break;
    case 8:
        update8();
        break;
    };

    ui->groupBox_2->layout()->addWidget(m_listWidget);
}

void DisplaySelectDialog::on_buttonBox_accepted()
{
    qDebug()<<__func__<<__LINE__;

    if (m_listWidget == NULL) {
        accept();
        return;
    }

    ModeListWidgetItem *item = static_cast<ModeListWidgetItem *>(m_listWidget->currentItem());
    if (item == NULL) {
        accept();
        return;
    }
    DplDisplay::Display *display = DplDisplay::Display::get_instance();
    if (display == NULL) {
        accept();
        return;
    }
    display->set_mode(item->get_mode());

    accept();
}

void DisplaySelectDialog::update1()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::AB_SCAN);
    m_listWidget->addItem(item);

}

void DisplaySelectDialog::update2()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::A_SCAN);
    m_listWidget->addItem(item);

}

void DisplaySelectDialog::update3()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::A_SCAN);
    m_listWidget->addItem(item);

}

void DisplaySelectDialog::update4()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::A_SCAN);
    m_listWidget->addItem(item);

}

void DisplaySelectDialog::update5()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::A_SCAN);
    m_listWidget->addItem(item);

}

void DisplaySelectDialog::update6()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::A_SCAN);
    m_listWidget->addItem(item);

}

void DisplaySelectDialog::update7()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::A_SCAN);
    m_listWidget->addItem(item);

}

void DisplaySelectDialog::update8()
{
    ModeListWidgetItem *item = new ModeListWidgetItem(DplDisplay::Display::A_SCAN);
    m_listWidget->addItem(item);
}
