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
    grpQty = 8;
    for (int i = grpQty; i < 8; ++i) {
        QCheckBox *checkBox = findChild<QCheckBox *>("checkBox_"+QString::number(i+1));
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

void DisplaySelectDialog::on_checkBox_all_clicked(bool checked)
{
    ui->checkBox_1->setDisabled(checked);
    ui->checkBox_2->setDisabled(checked);
    ui->checkBox_3->setDisabled(checked);
    ui->checkBox_4->setDisabled(checked);
    ui->checkBox_5->setDisabled(checked);
    ui->checkBox_6->setDisabled(checked);
    ui->checkBox_7->setDisabled(checked);
    ui->checkBox_8->setDisabled(checked);

    update_widget();
}

void DisplaySelectDialog::update_widget()
{
    DplDevice::Device *dev = DplDevice::Device::get_instance();

    m_grpIds.clear();

    if (ui->checkBox_all->isChecked()) {
        for (int i = 0; i < dev->groups(); ++i) {
            m_grpIds.append(i);
        }
    } else {
        QList<QAbstractButton *> btns = ui->buttonGroup->buttons();
        for (int i = 0; i < btns.size(); ++i) {
            if (btns[i]->isChecked()) {
                m_grpIds.append(i);
            }
        }
    }

    QObjectList objs = ui->groupBox_2->children();
    while (!objs.isEmpty()) {
        delete objs.takeFirst();
    }

    switch (m_grpIds.size()) {
    case 1:
        update(ScanLayout::A, ScanLayout::ASC);
        break;
    case 2:
        update(ScanLayout::A2, ScanLayout::ASB2);
        break;
    case 3:
        update(ScanLayout::A3, ScanLayout::ABC3);
        break;
    case 4:
        update(ScanLayout::A4, ScanLayout::S2_B2);
        break;
    case 5:
        update(ScanLayout::A5, ScanLayout::S3_B2);
        break;
    case 6:
        update(ScanLayout::A6, ScanLayout::S4_B2);
        break;
    case 7:
        update(ScanLayout::A7, ScanLayout::A7);
        break;
    case 8:
        update(ScanLayout::A8, ScanLayout::A8);
        break;
    };
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
    l->set_mode(static_cast<ScanLayout::Mode>(radioBtn->get_mode()),
                m_grpIds);

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
