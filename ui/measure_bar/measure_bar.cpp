#include "measure_bar.h"
#include "ui_measure_bar.h"

#include "measure_dialog.h"

#include "device/device.h"
#include "source/source.h"
#include "source/beams.h"

#include <QThread>
#include <QDebug>

MeasureBar :: MeasureBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureBar)
{
    ui->setupUi(this);

    DplDevice::Device *device = DplDevice::Device::instance();
    connect(device, SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));
    do_current_group_changed(device->current_group());

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

    connect(this, SIGNAL(calculated(MeasureWidget*,QString)),
            this, SLOT(do_calculated(MeasureWidget*,QString)), Qt::QueuedConnection);
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
    }
}

void MeasureBar::do_current_group_changed(const DplDevice::GroupPointer &group)
{
    disconnect(static_cast<DplDevice::Group *>(m_group.data()),
               SIGNAL(data_event(DplSource::BeamsPointer)),
               this,
               SLOT(do_beamgroup_data_event()));
    m_group = group;
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_beamgroup_data_event()),
            Qt::DirectConnection);
}

void MeasureBar::do_beamgroup_data_event()
{
    QList<MeasureWidget *> lst = findChildren<MeasureWidget *>(QRegExp("measureWidget[1-8]"));
    foreach (MeasureWidget *w, lst) {
        emit calculated( w, Measure::instance()->calculate_str(m_group, static_cast<Measure::Type>(w->property("Type").toInt()) ) );
    }
}

void MeasureBar::do_calculated(MeasureWidget *w, const QString &str)
{
    w->set_value(str);
}

void MeasureBar::set_measure_widget(MeasureWidget *w, Measure::Type type)
{
    MeasureDialog dlg(this, type);
    set_measure_widget(w, dlg);
}

void MeasureBar::set_measure_widget(MeasureWidget *w, MeasureDialog &dlg)
{
    w->setProperty("Type", dlg.get_type());
    w->set_title(dlg.get_type_string());
    w->set_unit(dlg.get_unit());
}
