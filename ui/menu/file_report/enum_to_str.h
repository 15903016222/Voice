#ifndef __ENUM_TO_STR_H__
#define __ENUM_TO_STR_H__

#include <QObject>

#include <source/axis.h>
#include <source/encoder.h>
#include <fpga/group.h>
#include <focallaw/focus_cnf.h>
#include <focallaw/scan_cnf.h>
#include <ut/global_transceiver.h>

class EnumToStr : public QObject
{
    Q_OBJECT
public:
    explicit EnumToStr(QObject *parent = 0);

    static QString gate_synchro_mode(DplFpga::Group::SynchroMode mode);
    static QString encoder_polarity(DplSource::Encoder::Polarity polarity);
    static QString encoder_name(DplSource::Axis::Driving driving);
    static QString encoder_mode(DplSource::Encoder::Mode mode);

    static QString focallawer_focal_type(DplFocallaw::FocusCnf::Mode mode);
    static QString focallawer_law_type(DplFocallaw::ScanCnf::Mode mode);

    static QString video_filter(bool enable);
    static QString voltage(DplUt::GlobalTransceiver::Voltage voltage);
    static QString rectifier(DplFpga::Group::Rectifier rectifier);
    static QString rx_tx_mode(DplUt::Transceiver::Mode mode);

    static QString band_pass_filter(int index, bool isPa);

};


#endif // __ENUM_TO_STR_H__
