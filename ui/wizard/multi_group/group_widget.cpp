#include "group_widget.h"
#include "ui_group_widget.h"
#include <ui/dialog/dpl_message_box.h>

static const QString SPILT_COLOR = "rgb(235, 231, 237)";

GroupWidget::GroupWidget(int groupIndex, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupWidget),
    m_groupIndex(groupIndex)
{
    ui->setupUi(this);
    ui->groupLabel->setText(tr("Gr") + QString::number(groupIndex + 1) + ":");
    if(groupIndex % 2 == 1) {
    QString qss = QString("QWidget{ \
                          background-color: %1; \
                          font-size: 15pt; \
                          } \
                          QLabel#stateLabel{ \
                          background-color: %2; \
                          color:rgb(0, 63, 111); \
                          } \
                          QLabel#groupLabel{ \
                          background-color: %3; \
                          color:rgb(0, 63, 111); \
                          } \
                          QComboBox{ \
                          color:rgb(0, 63, 111); \
                          border: 0px solid gray; \
                          } \
                          QPushButton#settingPushButton{ \
                          background-color: rgb(55, 170, 255); \
                          color: rgb(0, 63, 111); \
                          border: 10px solid %4; \
                          border-radius:5px; \
                          }").arg(SPILT_COLOR).arg(SPILT_COLOR).arg(SPILT_COLOR).arg(SPILT_COLOR);

    setStyleSheet(qss);
}
}

GroupWidget::~GroupWidget()
{
    delete ui;
}

void GroupWidget::set_focus()
{
    ui->comboBox->setFocusPolicy(Qt::WheelFocus);
    ui->comboBox->setFocus();
}

void GroupWidget::set_state(bool flag)
{
    if(flag) {
        ui->stateLabel->setText(tr("OK"));
    }
}

void GroupWidget::on_settingPushButton_clicked()
{
    if(ui->comboBox->currentIndex() == 0) {
        DplMessageBox megBox(QMessageBox::Warning, tr("Warning"), tr("Model is NA!"));
        megBox.exec();
        return;
    }

    emit setting_clicked(ui->comboBox->currentIndex(), m_groupIndex);
}