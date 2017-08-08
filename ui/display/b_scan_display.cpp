#include "b_scan_display.h"
#include "ui_b_scan_display.h"

#include "source/beams.h"
#include "scan_view.h"
#include "b_scan_scene.h"
#include "b_wave_item.h"

BscanDisplay::BscanDisplay(DplDevice::GroupPointer &group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BscanDisplay),
    m_group(group),
    m_bscanView(new ScanView),
    m_bscanScene(new BscanScene)
{
    ui->setupUi(this);

    m_bWaveItem = new BWaveItem(ui->colorBar);

    ui->leftRuler->set_type(RulerWidget::LEFT);
    ui->leftRuler->set_direction(RulerWidget::Down);
    ui->leftRuler->set_range(0, 100);
    ui->leftRuler->set_backgroup_color(QColor("#ffff7f"));
    ui->leftRuler->update();


    ui->rightRuler->set_type(RulerWidget::RIGHT);
    ui->rightRuler->set_direction(RulerWidget::Down);
    ui->rightRuler->set_range(0, 100);
    ui->rightRuler->set_unit("(%)");
    ui->rightRuler->update();

    /* source setting */
    DplSource::BeamsPointer beams = m_group->beams();
    connect(static_cast<DplSource::Beams *>(beams.data()),
            SIGNAL(data_event()),
            this,
            SLOT(do_data_event()));

    ui->titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));

    connect(m_bscanView, SIGNAL(size_changed(QSize)), m_bscanScene, SLOT(set_size(QSize)));

    ui->bScanWidgetVerticalLayout->addWidget(m_bscanView);
    m_bscanView->setScene(m_bscanScene);

}

BscanDisplay::~BscanDisplay()
{
    delete ui;

    delete m_bscanScene;
    delete m_bscanView;
}


void BscanDisplay::do_data_event()
{
    m_bscanScene->set_size(m_bscanView->size());
    m_bscanScene->show_wave(m_group->beams());
}
