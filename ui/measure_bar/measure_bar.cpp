/**
 * @file measure_bar.cpp
 * @brief 测量显示栏
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-19
 */
#include "measure_bar.h"
#include "ui_measure_bar.h"

#include "measure_dialog.h"
#include <ui/menu/file_report/field_info.h>
#include <device/device.h>

MeasureBar :: MeasureBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureBar)
{
    ui->setupUi(this);

    connect(ui->measureWidget1, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));
    connect(ui->measureWidget2, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));
    connect(ui->measureWidget3, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));
    connect(ui->measureWidget4, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));
    connect(ui->measureWidget5, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));
    connect(ui->measureWidget6, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));
    connect(ui->measureWidget7, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));
    connect(ui->measureWidget8, SIGNAL(clicked(MeasureWidget*)), this, SLOT(do_measureWidget_clicked(MeasureWidget*)));

    set_measure_widget(ui->measureWidget1, Measure::Gate_A_Peak);
    set_measure_widget(ui->measureWidget2, Measure::Gate_AdBA);
    set_measure_widget(ui->measureWidget3, Measure::Gate_B_Peak);
    set_measure_widget(ui->measureWidget4, Measure::Gate_BdBB);
    set_measure_widget(ui->measureWidget5, Measure::Measurement_Cursor_UT_Position);
    set_measure_widget(ui->measureWidget6, Measure::Measurement_Cursor_Index_Position);
    set_measure_widget(ui->measureWidget7, Measure::Measurement_Cursor_Scan_Position);
    set_measure_widget(ui->measureWidget8, Measure::Gate_A_Position);

    DplFileReportMenu::FieldNameMap nameMap;
    nameMap.insert(ui->measureWidget1, QString(ui->measureWidget1->title() + "\n(" + ui->measureWidget1->unit() + ")"));
    nameMap.insert(ui->measureWidget2, QString(ui->measureWidget2->title() + "\n(" + ui->measureWidget2->unit() + ")"));
    nameMap.insert(ui->measureWidget3, QString(ui->measureWidget3->title() + "\n(" + ui->measureWidget3->unit() + ")"));
    nameMap.insert(ui->measureWidget4, QString(ui->measureWidget4->title() + "\n(" + ui->measureWidget4->unit() + ")"));
    nameMap.insert(ui->measureWidget5, QString(ui->measureWidget5->title() + "\n(" + ui->measureWidget5->unit() + ")"));
    nameMap.insert(ui->measureWidget6, QString(ui->measureWidget6->title() + "\n(" + ui->measureWidget6->unit() + ")"));
    nameMap.insert(ui->measureWidget7, QString(ui->measureWidget7->title() + "\n(" + ui->measureWidget7->unit() + ")"));
    nameMap.insert(ui->measureWidget8, QString(ui->measureWidget8->title() + "\n(" + ui->measureWidget8->unit() + ")"));
    DplFileReportMenu::FieldInfo::instance()->add_field_names(DplDevice::Device::instance()->current_group(), nameMap);
}

MeasureBar::~MeasureBar()
{
    delete(ui);
}

void MeasureBar::do_measureWidget_clicked(MeasureWidget *w)
{
    MeasureDialog dialog(this, static_cast<Measure::Type>(w->property("Type").toInt()));
    if (dialog.exec() == MeasureDialog::Accepted) {
        set_measure_widget(w, dialog);
        DplFileReportMenu::FieldInfo *fieldInfo = DplFileReportMenu::FieldInfo::instance();
        fieldInfo->set_field_name(DplDevice::Device::instance()->current_group(),
                                  w,
                                  w->title() + "\n(" + w->unit() + ")");
    }
}

void MeasureBar::set_measure_widget(MeasureWidget *w, Measure::Type type)
{
    MeasureDialog dlg(this, type);
    set_measure_widget(w, dlg);
}

void MeasureBar::set_measure_widget(MeasureWidget *w, MeasureDialog &dlg)
{
    w->set_type(dlg.get_type());
    w->set_title(dlg.get_type_string());
    w->set_unit(dlg.get_unit());
}
