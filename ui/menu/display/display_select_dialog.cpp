#include "display_select_dialog.h"
#include "ui_display_select_dialog.h"
#include "mode_radio_button.h"

#include <device/device.h>
#include <display/display.h>

DisplaySelectDialog::DisplaySelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplaySelectDialog),
    m_radioBtnGrp(new QButtonGroup)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    DplDevice::Device *dev = DplDevice::Device::get_instance();
    int grpQty = dev->groups();

    /* set id */
    ui->buttonGroup->setId(ui->checkBox_all, 0);
    ui->buttonGroup->setId(ui->checkBox_1, 1);
    ui->buttonGroup->setId(ui->checkBox_2, 2);
    ui->buttonGroup->setId(ui->checkBox_3, 3);
    ui->buttonGroup->setId(ui->checkBox_4, 4);
    ui->buttonGroup->setId(ui->checkBox_5, 5);
    ui->buttonGroup->setId(ui->checkBox_6, 6);
    ui->buttonGroup->setId(ui->checkBox_7, 7);
    ui->buttonGroup->setId(ui->checkBox_8, 8);

    for (int i = grpQty+1; i <= 8; ++i) {
        QCheckBox *checkBox = findChild<QCheckBox *>("checkBox_"+QString::number(i));
        if (checkBox) {
            checkBox->hide();
        }
    }

    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(update_widget()));
}

DisplaySelectDialog::~DisplaySelectDialog()
{
    delete ui;
}

void DisplaySelectDialog::update_widget()
{
    bool allGrp = ui->checkBox_all->isChecked();
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

    QObjectList objs = ui->groupBox_2->children();
    while (!objs.isEmpty()) {
        delete objs.takeFirst();
    }

    switch (grpQty) {
    case 1:
        update(ScanLayout::A, ScanLayout::ASC);
        break;
    case 2:
        update(ScanLayout::A2, ScanLayout::ASB2);
        break;
//    case 3:
//        update3();
//        break;
//    case 4:
//        update4();
//        break;
//    case 5:
//        update5();
//        break;
//    case 6:
//        update6();
//        break;
//    case 7:
//        update7();
//        break;
//    case 8:
//        update8();
//        break;
    };

//    ui->groupBox_2->layout()->setAlignment(m_widget, Qt::AlignHCenter | Qt::AlignTop);
}

void DisplaySelectDialog::on_buttonBox_accepted()
{
    ModeRadioButton *radioBtn = static_cast<ModeRadioButton *>(m_radioBtnGrp->checkedButton());
    DplDisplay::Display *display = DplDisplay::Display::get_instance();
    if (radioBtn == NULL || display == NULL) {
        accept();
        return;
    }

    ScanLayout *l = new ScanLayout;
    QList<int> grpIds;
    DplDevice::Device *dev = DplDevice::Device::get_instance();

    if (ui->checkBox_all->isChecked()) {
        for (int i = 0; i < dev->groups(); ++i) {
            grpIds.append(i+1);
        }
    } else {
        QList<QAbstractButton *> btns = ui->buttonGroup->buttons();
        for (int i = 1; i < btns.size(); ++i) {
            if (btns[i]->isChecked()) {
                grpIds.append(i);
            }
        }
    }

    l->set_mode(static_cast<ScanLayout::Mode>(radioBtn->get_mode()),
                grpIds);

    display->set_layout(l);

    accept();
}


void DisplaySelectDialog::update(int startMode, int endMode)
{
    QGridLayout *layout = new QGridLayout(ui->groupBox_2);
    ModeRadioButton *btn = NULL;

    layout->setSpacing(10);

    for (int mode=startMode;
         mode<= endMode;
         ++mode) {
        btn = new ModeRadioButton(mode, ui->groupBox_2);
        layout->addWidget(btn,
                          (mode-startMode)/4,
                          (mode-startMode)%4);
        m_radioBtnGrp->addButton(btn);
        if (mode == startMode) {
            btn->setChecked(true);
        }
    }
}
