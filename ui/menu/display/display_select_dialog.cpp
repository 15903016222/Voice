#include "display_select_dialog.h"
#include "ui_display_select_dialog.h"
#include "mode_radio_button.h"

#include <device/device.h>
#include "../display/display_widget.h"
#include <QPushButton>

DisplaySelectDialog::DisplaySelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplaySelectDialog),
    m_radioBtnGrp(new QButtonGroup(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    DplDevice::Device *dev = DplDevice::Device::instance();
    int grpQty = dev->group_qty();
    grpQty = 8;
    for (int i = grpQty; i < 8; ++i) {
        QCheckBox *checkBox = findChild<QCheckBox *>("checkBox_"+QString::number(i+1));
        if (checkBox) {
            checkBox->hide();
        }
    }

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

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
    DplDevice::Device *dev = DplDevice::Device::instance();

    m_grpIds.clear();

    if (ui->checkBox_all->isChecked()) {
        for (int i = 0; i < dev->group_qty(); ++i) {
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
        update(DplDisplay::Display::A, DplDisplay::Display::ASC);
        break;
    case 2:
        update(DplDisplay::Display::A2, DplDisplay::Display::ASB2);
        break;
    case 3:
        update(DplDisplay::Display::A3, DplDisplay::Display::ABC3);
        break;
    case 4:
        update(DplDisplay::Display::A4, DplDisplay::Display::S2_B2);
        break;
    case 5:
        update(DplDisplay::Display::A5, DplDisplay::Display::S3_B2);
        break;
    case 6:
        update(DplDisplay::Display::A6, DplDisplay::Display::S4_B2);
        break;
    case 7:
        update(DplDisplay::Display::A7, DplDisplay::Display::A7);
        break;
    case 8:
        update(DplDisplay::Display::A8, DplDisplay::Display::A8);
        break;
    };
}

void DisplaySelectDialog::on_buttonBox_accepted()
{
    ModeRadioButton *radioBtn = static_cast<ModeRadioButton *>(m_radioBtnGrp->checkedButton());
    if (radioBtn == NULL) {
        accept();
        return;
    }

    DplDevice::Device::instance()->display()->set_layout(
                static_cast<DplDisplay::Display::Layout>(radioBtn->get_mode()),
                m_grpIds);

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
                          (mode-startMode)%4,
                          Qt::AlignHCenter|Qt::AlignTop);
        m_radioBtnGrp->addButton(btn);
        if (mode == startMode) {
            btn->setChecked(true);
        }
    }
}
