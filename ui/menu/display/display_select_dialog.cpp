#include "display_select_dialog.h"
#include "ui_display_select_dialog.h"
#include "mode_radio_button.h"

#include <device/device.h>
#include <display/display.h>

DisplaySelectDialog::DisplaySelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplaySelectDialog),
    m_widget(NULL),
    m_radioBtnGrp(new QButtonGroup)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    DplDevice::Device *dev = DplDevice::Device::get_instance();
    int grpQty = dev->groups();

    /* set id */
    ui->buttonGroup->setId(ui->checkBox, 0);
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

    if (m_widget != NULL) {
        delete m_widget;
    }
    m_widget = new QWidget(this);

    switch (grpQty) {
    case 1:
        update(A, ASC);
        break;
    case 2:
        update(A2, ASB2);
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

    ui->groupBox_2->layout()->addWidget(m_widget);
    ui->groupBox_2->layout()->setAlignment(m_widget, Qt::AlignHCenter | Qt::AlignTop);
}

void DisplaySelectDialog::on_buttonBox_accepted()
{
    if (m_widget == NULL) {
        accept();
        return;
    }

    ModeRadioButton *radioBtn = static_cast<ModeRadioButton *>(m_radioBtnGrp->checkedButton());
    DplDisplay::Display *display = DplDisplay::Display::get_instance();
    if (radioBtn == NULL || display == NULL) {
        accept();
        return;
    }

    QWidget *w = NULL;
    switch (radioBtn->get_mode()) {
    case A:
        w = a_layout();
        break;
    default:
        break;
    }

    display->set_layout(w);

    accept();
}

QWidget *DisplaySelectDialog::a_layout()
{
    QWidget *w = new QWidget();
    QVBoxLayout *l = new QVBoxLayout(w);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);
    l->setObjectName(QString("A%1").arg(ui->buttonGroup->checkedId()));
    return w;
}


void DisplaySelectDialog::update(int startMode, int endMode)
{
    QGridLayout *layout = new QGridLayout(m_widget);
    ModeRadioButton *btn = NULL;

    layout->setSpacing(10);

    for (int mode=startMode;
         mode<= endMode;
         ++mode) {
        btn = new ModeRadioButton(mode, m_widget);
        layout->addWidget(btn,
                          (mode-startMode)/4,
                          (mode-startMode)%4);
        m_radioBtnGrp->addButton(btn);
        if (mode == startMode) {
            btn->setChecked(true);
        }
    }
}
