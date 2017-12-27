#include "report_applier.h"

#include <report/report.h>
#include <report/report_group.h>
#include <report/report_groups.h>
#include <QSharedPointer>
#include <device/group.h>
#include <device/device.h>
#include <source/scan.h>
#include <source/axis.h>
#include <gate/gate.h>
#include <ui/menu/file_report/enum_to_str.h>
#include <ui/menu/file_report/field_info.h>
#include <ui/display/fft/fft_result.h>
#include <ut/global_transceiver.h>
#include <ui/tool/tool.h>

namespace DplFileReportMenu {

static const int DEFAULT_PRECISION = 2;

ReportApplier::ReportApplier(DplReport::Report &report, QObject *parent)
    : QObject(parent),
      m_report(report),
      m_precision(DEFAULT_PRECISION)
{

}

void ReportApplier::fill(const QString &reportFile)
{
    fill_report_header(reportFile);

    fill_report_users();

    fill_report_groups();

    fill_report_defects();
}

void ReportApplier::fill_report_header(const QString &reportFile)
{
    DplReport::ReportHeaderPointer header = m_report.report_header();

    QString dateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd");

    header->set_device_type(tr("Phascan"));
    header->set_report_file(reportFile);
    header->set_setup_file(tr("default.cfg"));
    header->set_report_date_time(dateTime);
    header->set_inspection_date_time(dateTime);
    /*
     * Inspection Data
     * Inspection Table
     * Screen
     * Report
     * Setup
     */
    header->set_save_mode(tr("TODO"));
}

void ReportApplier::fill_report_users()
{
    DplReport::ReportUsersPointer users = m_report.report_users();
    DplReport::ReportUsers::S_USER user;
#if 0
    /* TODO */
    for (int i = 0; i < 10; ++i) {
        user.name       = tr("TODOname") + QString::number(i + 1);
        user.content    = tr("TODOcontent") + QString::number(i + 1);
        users->add_user(user);
    }
#endif
}

void ReportApplier::fill_report_groups()
{
    DplReport::ReportGroupsPointer reportGroups = m_report.report_groups();

    DplDevice::Device *device = DplDevice::Device::instance();
    const QVector<DplDevice::GroupPointer> &groups= device->groups();
    QVector<DplDevice::GroupPointer>::const_iterator it = groups.begin();

    while(it != groups.end()) {
        m_currentGroup = (*it).data();
        reportGroups->add_group((*it)->index());
        fill_report_group(reportGroups.data());
        ++it;
    }
}

void ReportApplier::fill_report_defects()
{

    DplReport::ReportDefectsPointer defects = m_report.report_defects();

    /* 从FieldInfo类获取1～8个域的名称 */
    QList<QString> list = FieldInfo::instance()->field_names(DplDevice::Device::instance()->current_group());
    for(int i = 0; i < list.count(); ++i) {
        defects->set_field_name(i, list.at(i));
    }

#if 0
    /* 从缺陷表获取缺陷信息； */
//    for(int i = 0; i < defectVect.size(); ++i) {
        DplReport::ReportDefects::S_ReportDefect reportDefect;
        reportDefect.channel        = tr("TODO");
        reportDefect.comments       = tr("TODO");
        reportDefect.fieldValues[0] = tr("TODO");
        reportDefect.fieldValues[1] = tr("TODO");
        reportDefect.fieldValues[2] = tr("TODO");
        reportDefect.fieldValues[3] = tr("TODO");
        reportDefect.fieldValues[4] = tr("TODO");
        reportDefect.fieldValues[5] = tr("TODO");
        reportDefect.fieldValues[6] = tr("TODO");
        reportDefect.fieldValues[7] = tr("TODO");
        reportDefect.group          = tr("TODO");
        reportDefect.image          = tr("TODO");
        reportDefect.index          = tr("TODO");
        reportDefect.scan           = tr("TODO");

        defects->add_defect(reportDefect);
//    }
#endif
}

void ReportApplier::fill_report_group(DplReport::ReportGroups *reportGroups)
{
    DplReport::ReportGroupPointer group = reportGroups->current_group();

    fill_report_group_probe(group.data());
    fill_report_group_wedge(group.data());
    fill_report_group_fft(group.data());
    fill_report_group_setup(group.data());

    if (m_currentGroup->mode() == DplDevice::Group::PA) {
        fill_report_group_law(group.data());
    }

    fill_report_group_part(group.data());
    fill_report_group_scan(group.data());
}

void ReportApplier::fill_report_group_probe(DplReport::ReportGroup *group)
{
    DplReport::ReportProbePointer probe = group->get_probe();

    const DplFocallaw::FocallawerPointer &focallawer = m_currentGroup->focallawer();
    const DplFocallaw::ProbePointer &probePointer = focallawer->probe();

    if(probePointer->is_pa()) {
        DplFocallaw::PaProbePointer paProbePointer = probePointer.staticCast<DplFocallaw::PaProbe>();
        probe->set_aperture(QString::number(paProbePointer->scan_configure()->aperture()));
    }

    probe->set_freq(QString::number(probePointer->freq(), 'f', m_precision));
    probe->set_model(probePointer->model());
    probe->set_serial(probePointer->serial());
}

void ReportApplier::fill_report_group_wedge(DplReport::ReportGroup *group)
{
    DplReport::ReportWedgePointer wedge = group->get_wedge();

    const DplFocallaw::FocallawerPointer &focallawer = m_currentGroup->focallawer();
    const DplFocallaw::WedgePointer &wedgePointer = focallawer->wedge();

    wedge->set_angle(QString::number(wedgePointer->angle(), 'f', m_precision));
    wedge->set_model(wedgePointer->model());
}

void ReportApplier::fill_report_group_fft(DplReport::ReportGroup *group)
{
    DplReport::ReportFFTPointer fft = group->get_fft();
    /* TODO: FFT需提供是否开启选项 */
    bool enable = false;
    if(enable) {
        const FFTCalculator::S_FFT_result &result = FFTResult::instance()->result();

        fft->set_peak_freq(QString::number(result.peakFrequency, 'f', m_precision));

        fft->set_band_width_6_dB(QString::number(result.bandWidth6db, 'f', m_precision));
        fft->set_band_width_percent_6_dB(QString::number(result.bandWidth6dbPercent, 'f', m_precision));
        fft->set_center_freq_6_dB(QString::number(result.centerFrequency6db, 'f', m_precision));
        fft->set_heigher_freq_6_dB(QString::number(result.max6dbFrequency, 'f', m_precision));
        fft->set_lower_freq_6_dB(QString::number(result.min6dbFrequency, 'f', m_precision));

        fft->set_band_width_20_dB(QString::number(result.bandWidth20db, 'f', m_precision));
        fft->set_band_width_percent_20_dB(QString::number(result.bandWidth20dbPercent, 'f', m_precision));
        fft->set_center_freq_20_dB(QString::number(result.centerFrequency20db, 'f', m_precision));
        fft->set_heigher_freq_20_dB(QString::number(result.max20dbFrequency, 'f', m_precision));
        fft->set_lower_freq_20_dB(QString::number(result.min20dbFrequency, 'f', m_precision));
    }
}

void ReportApplier::fill_report_group_setup(DplReport::ReportGroup *group)
{
    DplReport::ReportSetupPointer setup = group->get_setup();

    const DplUt::TransceiverPointer &transceiver = m_currentGroup->transceiver();

    setup->set_averaging_factor(QString::number(transceiver->averaging(), 'f', m_precision));
    setup->set_band_pass_filter(EnumToStr::band_pass_filter(transceiver->filter(), m_currentGroup->focallawer()->probe()->is_pa()));
    setup->set_pulse_width(QString::number(transceiver->pw(), 'f', m_precision));
    setup->set_rectification(EnumToStr::rectifier(transceiver->rectifier()));
    setup->set_video_filter(EnumToStr::video_filter(transceiver->video_filter()));
    setup->set_rx_tx_mode(EnumToStr::rx_tx_mode(transceiver->mode()));

    setup->set_gain(QString::number(m_currentGroup->sample()->gain(), 'f', m_precision));
    setup->set_half_path_range(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(),
                                                                    m_currentGroup->sample()->range()), 'f', m_precision));
    setup->set_half_path_start(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(),
                                                                    m_currentGroup->sample()->start()), 'f', m_precision));
    setup->set_scale_factor(QString::number(m_currentGroup->sample()->scale_factor()));

    setup->set_prf(QString::number(DplUt::GlobalTransceiver::instance()->prf()));
    if(m_currentGroup->focallawer()->probe()->is_pa()) {
        setup->set_voltage(EnumToStr::voltage(DplUt::GlobalTransceiver::instance()->pa_voltage()));
    } else {
        setup->set_voltage(EnumToStr::voltage(DplUt::GlobalTransceiver::instance()->ut_voltage()));
    }

    setup->set_sound_velocity(QString::number(m_currentGroup->focallawer()->specimen()->velocity()));
    setup->set_skew(QString::number(m_currentGroup->current_angle(), 'f', m_precision));

    setup->set_inspection_type(EnumToStr::inspection_type(m_currentGroup->mode()));
    /* LW/SW，未实现于probe类? */
    setup->set_wave_type(tr("TODO"));
    /* 在测量——光标，选择数据时，出现步进偏移、扫查偏移，但当前版本无数据扫查 */
    setup->set_scan_offset(tr("TODO"));
    setup->set_index_offset(tr("TODO"));
    /* Phascan具有Beam相关参数设置包括时延， 当前版本无此项 */
    setup->set_beam_delay(tr("TODO"));

    const DplGate::GatePointer &gateAPointer = m_currentGroup->gate_a();
    DplReport::ReportGatePointer gateA = setup->get_gate(DplReport::ReportGate::Gate_A);
    gateA->set_enable(gateAPointer->is_visible());
    gateA->set_start(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(), gateAPointer->start()),
                                     'f', m_precision));
    gateA->set_synchro(EnumToStr::gate_synchro_mode(gateAPointer->synchro_mode()));
    gateA->set_width(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(), gateAPointer->width()),
                                     'f', m_precision));
    gateA->set_threshold(QString::number(gateAPointer->height()));

    const DplGate::GatePointer &gateBPointer = m_currentGroup->gate_b();
    DplReport::ReportGatePointer gateB = setup->get_gate(DplReport::ReportGate::Gate_B);
    gateB->set_enable(gateBPointer->is_visible());
    gateB->set_start(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(), gateBPointer->start()),
                                     'f', m_precision));
    gateB->set_synchro(EnumToStr::gate_synchro_mode(gateBPointer->synchro_mode()));
    gateB->set_width(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(), gateBPointer->width()),
                                     'f', m_precision));
    gateB->set_threshold(QString::number(gateBPointer->height()));

    const DplGate::GatePointer &gateIPointer = m_currentGroup->gate_i();
    DplReport::ReportGatePointer gateI = setup->get_gate(DplReport::ReportGate::Gate_I);
    gateI->set_enable(gateIPointer->is_visible());
    gateI->set_start(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(), gateIPointer->start()),
                                     'f', m_precision));
    gateI->set_synchro(EnumToStr::gate_synchro_mode(gateIPointer->synchro_mode()));
    gateI->set_width(QString::number(Tool::cnf_to_display(DplDevice::Device::instance()->current_group(), gateIPointer->width()),
                                     'f', m_precision));
    gateI->set_threshold(QString::number(gateIPointer->height()));
}

void ReportApplier::fill_report_group_law(DplReport::ReportGroup *group)
{
    DplReport::ReportLawPointer law = group->get_law();

    const DplFocallaw::FocallawerPointer &focallawer =  m_currentGroup->focallawer();

    DplFocallaw::PaProbePointer probe = focallawer->probe().staticCast<DplFocallaw::PaProbe>();
    const QList<DplFocallaw::BeamPointer> &beams = focallawer->beams();

    if(probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Sectorial) {
        DplFocallaw::SectorialScanCnfPointer sectorialScan =
                probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
        if(!sectorialScan.isNull()) {
            law->set_angle_resolution(QString::number(sectorialScan->angle_step(), 'f', m_precision));
            law->set_start_angle(QString::number(sectorialScan->first_angle(), 'f', m_precision));
            law->set_stop_angle(QString::number(sectorialScan->last_angle(), 'f', m_precision));
        }
    } else if(probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
        DplFocallaw::LinearScanCnfPointer linearScan =
                probe->scan_configure().staticCast<DplFocallaw::LinearScanCnf>();
        if(!linearScan.isNull()) {
            law->set_element_resolution(QString::number(linearScan->element_step()));
        }
    }

    law->set_enable(true);
    law->set_element_qty(QString::number(probe->element_qty()));
    law->set_first_rx_element(QString::number(beams.at(0)->first_rx_element()));
    law->set_first_tx_element(QString::number(beams.at(0)->first_tx_element()));

    law->set_last_rx_element(tr("TODO"));
    law->set_last_tx_element(tr("TODO"));

    /* focal type */
    law->set_focal_type(EnumToStr::focallawer_focal_type(
                            focallawer->focus_configure()->mode()));
    /* law type */
    law->set_type(EnumToStr::focallawer_law_type(probe->scan_configure()->mode()));

    fill_focal_field_names(law, focallawer->focus_configure()->mode());
}

void ReportApplier::fill_report_group_part(DplReport::ReportGroup *group)
{
    DplReport::ReportPartPointer part = group->get_part();
    const DplFocallaw::SpecimenPointer &speciment =  m_currentGroup->focallawer()->specimen();
    if(speciment->type() == DplFocallaw::Specimen::CYLINDER) {
        part->set_geometry(tr("TODO"));
        part->set_material(tr("TODO"));
        part->set_thickness(tr("TODO"));
    } else if(speciment->type() == DplFocallaw::Specimen::FLAT) {
        part->set_geometry(tr("TODO"));
        part->set_material(tr("TODO"));
        part->set_thickness(tr("TODO"));
    }
}

void ReportApplier::fill_report_group_scan(DplReport::ReportGroup *group)
{
    DplReport::ReportScanPointer scan = group->get_scan();

    const DplSource::AxisPointer &scanAxis = DplSource::Scan::instance()->scan_axis();
    const DplSource::AxisPointer &indexAxis = DplSource::Scan::instance()->index_axis();

    scan->set_index_resolution(QString::number(indexAxis->resolution(), 'f', m_precision));
    scan->set_index_start(QString::number(indexAxis->start(), 'f', m_precision));
    scan->set_index_stop(QString::number(indexAxis->end(), 'f', m_precision));

    scan->set_scan_resolution(QString::number(scanAxis->resolution(), 'f', m_precision));
    scan->set_scan_speed(QString::number(DplSource::Scan::instance()->speed(), 'f', m_precision));
    scan->set_scan_start(QString::number(scanAxis->start(), 'f', m_precision));
    scan->set_scan_stop(QString::number(scanAxis->end(), 'f', m_precision));
    scan->set_scan_synchro(EnumToStr::encoder_name(scanAxis->driving()));

    fill_encoder(scan, DplReport::ReportEncoder::ScanEncoder);
    fill_encoder(scan, DplReport::ReportEncoder::IndexEncoder);
}

void ReportApplier::fill_encoder(DplReport::ReportScanPointer &scan, int type)
{
    DplSource::AxisPointer axis;
    if((DplReport::ReportEncoder::E_EncoderType)type == DplReport::ReportEncoder::ScanEncoder) {
        axis = DplSource::Scan::instance()->scan_axis();
    } else if((DplReport::ReportEncoder::E_EncoderType)type == DplReport::ReportEncoder::IndexEncoder) {
        axis = DplSource::Scan::instance()->index_axis();
    } else {
        return;
    }

    DplReport::ReportEncoderPointer reportEncoder = scan->get_encoder((DplReport::ReportEncoder::E_EncoderType)type);

    DplSource::EncoderPointer encoder;
    if(axis->driving() == DplSource::Axis::ENCODER_X) {
        encoder = DplSource::Scan::instance()->encoder_x();
    } else if(axis->driving() == DplSource::Axis::ENCODER_Y) {
        encoder = DplSource::Scan::instance()->encoder_y();
    } else if(axis->driving() == DplSource::Axis::TIMER) {
        reportEncoder->set_enable(true);
        reportEncoder->set_name(EnumToStr::encoder_name(axis->driving()));
        return;
    } else {
        reportEncoder->set_enable(false);
        return;
    }

    reportEncoder->set_enable(encoder->is_enabled());
    reportEncoder->set_name(EnumToStr::encoder_name(axis->driving()));
    reportEncoder->set_polarity(EnumToStr::encoder_polarity(encoder->polarity()));
    reportEncoder->set_resolution(QString::number(encoder->resolution(), 'f', m_precision));
    reportEncoder->set_type(EnumToStr::encoder_mode(encoder->mode()));
}

void ReportApplier::fill_focal_field_names(DplReport::ReportLawPointer &law, DplFocallaw::FocusCnf::Mode mode)
{
    const DplFocallaw::FocusCnfPointer &focusCnf =  m_currentGroup->focallawer()->focus_configure();

    switch(mode){
        case DplFocallaw::FocusCnf::HALF_PATH:
        {
            law->set_focal_field_names(0, tr("Radius"));
            DplFocallaw::HalfPathFocusPointer halfPath = focusCnf.staticCast<DplFocallaw::HalfPathFocus>();
            if(!halfPath.isNull()) {
                law->set_focal_field_values(0, QString::number(halfPath->radius(), 'f', m_precision));
            }
            break;
        }
        case DplFocallaw::FocusCnf::TRUE_DEPTH:
        {
            law->set_focal_field_names(0, tr("BeginDepth"));
            DplFocallaw::TrueDepthFocusPointer trueDepth = focusCnf.staticCast<DplFocallaw::TrueDepthFocus>();
            if(!trueDepth.isNull()) {
                law->set_focal_field_values(0, QString::number(trueDepth->depth(), 'f', m_precision));
            }
            break;
        }
        case DplFocallaw::FocusCnf::PROJECTION:
        {
            law->set_focal_field_names(0, tr("BeginOffset"));
            DplFocallaw::ProjectionFocusPointer projection = focusCnf.staticCast<DplFocallaw::ProjectionFocus>();
            if(!projection.isNull()) {
                law->set_focal_field_values(0, QString::number(projection->offset(), 'f', m_precision));
            }
            break;
        }
        case DplFocallaw::FocusCnf::FOCAL_PLANE:
        {
            law->set_focal_field_names(0, tr("BeginOffset"));
            law->set_focal_field_names(1, tr("EndOffset"));
            law->set_focal_field_names(2, tr("BeginDepth"));
            law->set_focal_field_names(3, tr("EndDepth"));

            DplFocallaw::FocalPlaneFocusPointer focalPlane = focusCnf.staticCast<DplFocallaw::FocalPlaneFocus>();
            if(!focalPlane.isNull()) {
                law->set_focal_field_values(0, QString::number(focalPlane->begin_offset(), 'f', m_precision));
                law->set_focal_field_values(0, QString::number(focalPlane->end_offset(), 'f', m_precision));
                law->set_focal_field_values(0, QString::number(focalPlane->begin_depth(), 'f', m_precision));
                law->set_focal_field_values(0, QString::number(focalPlane->end_depth(), 'f', m_precision));
            }
            break;
        }
        case DplFocallaw::FocusCnf::DDF:
        {
            /* TODO */
            break;
        }
        default:
            break;
    }
}

}
