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
        if(type == ScanGroupLayout::A_scan){

        }
        break;
    case 6:
        if(type == ScanGroupLayout::A_scan){

        }else if(type == ScanGroupLayout::S_TB){

        }
        break;
    case 5:
        if(type == ScanGroupLayout::A_scan){

        }else if(type == ScanGroupLayout::S_TB){

        }
        break;
    case 4:
        if(type == ScanGroupLayout::A_scan){

        }else if(type == ScanGroupLayout::C_scan){

        }else if(type == ScanGroupLayout::S_scan){

        }else if(type == ScanGroupLayout::A_Sscan){

        }else if(type == ScanGroupLayout::S_Cscan){

        }else if(type == ScanGroupLayout::C_TB){

        }else if(type == ScanGroupLayout::S_TA){

        }else if(type == ScanGroupLayout::S_TB){

        }else if(type == ScanGroupLayout::S_TA_C_TB){

        }
        break;
    case 3:
        if(type == ScanGroupLayout::A_scan){

        }else if(type == ScanGroupLayout::C_scan){

        }else if(type == ScanGroupLayout::S_scan){

        }else if(type == ScanGroupLayout::A_Sscan){

        }else if(type == ScanGroupLayout::S_Cscan){

        }else if(type == ScanGroupLayout::C_TB){

        }else if(type == ScanGroupLayout::S_TA){

        }else if(type == ScanGroupLayout::S_TB){

        }else if(type == ScanGroupLayout::S_TA_C_TB){

        }
        break;
    case 2:
        if(type == ScanGroupLayout::A_scan){

        }else if(type == ScanGroupLayout::C_scan){

        }else if(type == ScanGroupLayout::S_scan){

        }else if(type == ScanGroupLayout::A_Sscan){

        }else if(type == ScanGroupLayout::A_S_Cscan){

        }else if(type == ScanGroupLayout::A_B_Cscan){

        }else if(type == ScanGroupLayout::A_B_Sscan){

        }else if(type == ScanGroupLayout::S_TA_C_TB){

        }else if(type == ScanGroupLayout::S_Cscan){

        }else if(type == ScanGroupLayout::TA_TB){

        }
        break;
    case 1:
        if(type == ScanGroupLayout::A_scan){

        }else if(type == ScanGroupLayout::C_scan){

        }else if(type == ScanGroupLayout::S_scan){

        }else if(type == ScanGroupLayout::A_Sscan){

        }else if(type == ScanGroupLayout::A_S_Cscan){

        }else if(type == ScanGroupLayout::A_B_Cscan){

        }else if(type == ScanGroupLayout::A_B_Sscan){

        }else if(type == ScanGroupLayout::S_Cscan){

        }else if(type == ScanGroupLayout::TA_TB){

        }
        break;
    default:
        break;
    }
}
