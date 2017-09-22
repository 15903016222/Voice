#include "c_scan_display.h"
#include "ui_scan_display.h"

#include "scan_view.h"
#include "c_scan_scene.h"

#include <device/device.h>
#include <source/axis.h>
#include <source/scan.h>
#include <source/source.h>

CscanDisplay::CscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanDisplay),
    m_group(grp),
    m_view(new ScanView),
    m_scene(new CscanScene(DplDevice::Device::instance()->display()->palette())),
    m_orientation(orientation)
{
    ui->setupUi(this);

    ui->scanLayout->addWidget(m_view);

    connect(m_view, SIGNAL(size_changed(QSize)),
            m_scene, SLOT(set_size(QSize)));

    m_view->setScene(m_scene);

    init_ruler();

    ui->colorBarWidget->set_palette(DplDevice::Device::instance()->display()->palette());
    ui->titleLabel->setText(QString("C-Scan|Grp%1").arg(m_group->index()+1));

}

CscanDisplay::~CscanDisplay()
{
    delete ui;
    delete m_view;
    delete m_scene;
}

void CscanDisplay::init_ruler()
{
    if(m_orientation == Qt::Vertical) {
        m_scanTypeRuler = ui->bottomRulerWidget;
        m_lawTypeRuler  = ui->leftRulerWidget;
    } else {
        m_scanTypeRuler = ui->leftRulerWidget;
        m_lawTypeRuler  = ui->bottomRulerWidget;
    }

    ui->rightRulerWidget->set_type(RulerWidget::RIGHT);
    ui->rightRulerWidget->set_direction(RulerWidget::Down);
    ui->rightRulerWidget->set_range(0, 100);
    ui->rightRulerWidget->set_unit("(%)");
    ui->rightRulerWidget->update();

    update_scan_type_ruler(m_view->size());

    update_law_type_ruler();

}

void CscanDisplay::update_scan_type_ruler(const QSize &size)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    if(m_scene->driving() == DplSource::Axis::ENCODER_X
           || m_scene->driving() == DplSource::Axis::ENCODER_Y) {

        /* 扫查轴 */
        /* 根据scan start/end 及resolution（扫查分辨率）计算待显示的总beam数 */

        double scanStart        = DplSource::Scan::instance()->scan_axis()->start();
        double scanEnd          = DplSource::Scan::instance()->scan_axis()->end();
        double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();

        double beamCount = (scanEnd - scanStart) / scanResolution;
        int width;
        if(m_orientation == Qt::Horizontal) {
            width = size.height();
        } else {
            width = size.width();
        }

        if(width >= beamCount) {
            /* 若显示区域大于beam数，则计算每条beam占多少pix */
            double pixCount = width / beamCount;
            m_scanTypeRuler->set_range(scanStart, scanEnd);
            m_scanTypeRuler->set_max_end(scanEnd);
            m_scene->set_pix_per_beam(pixCount);
            m_scene->set_scroll_window(false);
            m_scanTypeRuler->set_show_range(scanStart, scanEnd);

        } else {
            /* 若显示区域小于beam数，则计算每条beam占一个pix */
            m_scanTypeRuler->set_range(scanStart, scanStart + width);
            m_scanTypeRuler->set_max_end(scanEnd);
            m_scene->set_pix_per_beam(DEFAULT_PIX_PER_BEAM);
            m_scene->set_scroll_window(true);
            m_scanTypeRuler->set_show_range(scanStart, scanStart + width);
        }

        m_scanTypeRuler->set_unit("(mm)");

    } else {

        double scanTypeRulerEnd;

        double beamQtyPerSecond = SECOND / (double)DplSource::Source::instance()->interval();

        if(m_orientation == Qt::Horizontal) {
            scanTypeRulerEnd = size.height() / beamQtyPerSecond;
        } else {
            scanTypeRulerEnd = size.width() / beamQtyPerSecond;
        }

        m_scanTypeRuler->set_range(0.0, scanTypeRulerEnd);
        m_scanTypeRuler->set_unit("(s)");
    }

    m_scanTypeRuler->update();
}

void CscanDisplay::update_law_type_ruler()
{

}
