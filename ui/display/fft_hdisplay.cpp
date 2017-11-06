#include "fft_hdisplay.h"
#include "ui_fft_display.h"

FFTHDisplay::FFTHDisplay(const DplDevice::GroupPointer &group,
                         QWidget *parent)
    : FFTDisplay(group, Qt::Horizontal, parent)
{

    ui->leftRulerWidget->set_direction(RulerWidget::Down);
    ui->leftRulerWidget->set_range(0, 100);
    ui->leftRulerWidget->set_unit("(%)");
    ui->leftRulerWidget->set_backgroup_color(QColor("#ffff7f"));
    ui->leftRulerWidget->update();

    update_bottom_ruler();
}

void FFTHDisplay::update_bottom_ruler()
{
    ui->bottomRulerWidget->set_unit("(MHz)");
    ui->bottomRulerWidget->set_range(0.0, 50.0);
    ui->bottomRulerWidget->update();
}
