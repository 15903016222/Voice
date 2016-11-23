#include "scan_group_layout.h"
#include "ui_scan_group_layout.h"

ScanGroupLayout::ScanGroupLayout(QWidget *parent, ScanType type, int group) :
    QWidget(parent),
    ui(new Ui::ScanGroupLayout)
{
    ui->setupUi(this);

    set_display_group(type, group);
}

ScanGroupLayout::~ScanGroupLayout()
{
    delete ui;
}

void ScanGroupLayout::set_display_group(ScanType type, int group)
{
    switch (group) {
    case 8:
        if(type == ScanGroupLayout::A_scan){
          //  pAscan = new AScan(this);
            for(int i = 1; i <= 8; i++)
            {
                QWidget* widget = findChild<QWidget*>("widget_" + QString::number(i));
                QGridLayout *displayLayout = new QGridLayout(widget);
             //   displayLayout->addWidget(pAscan);
                widget->setLayout(displayLayout);
            }

            ui->widget_9->hide();
            ui->widget_10->hide();
            ui->widget_11->hide();
        }
        break;
    case 7:

        break;
    case 6:

        break;
    case 5:

        break;
    case 4:

        break;
    case 3:

        break;
    case 2:

        break;
    case 1:

        break;
    default:
        break;
    }
}
