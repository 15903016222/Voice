
#include "enum_to_str.h"


EnumToStr::EnumToStr(QObject *parent)
    : QObject(parent)
{

}

QString EnumToStr::gate_synchro_mode(DplFpga::Group::SynchroMode mode)
{
    switch(mode) {
        case DplFpga::Group::SYNCHRO_PULSER:
        {
            return tr("Pulser");
            break;
        }
        case DplFpga::Group::SYNCHRO_I:
        {
            return tr("I");
            break;
        }
        case DplFpga::Group::SYNCHRO_A:
        {
            return tr("A");
            break;
        }
        case DplFpga::Group::SYNCHRO_B:
        {
            return tr("B");
            break;
        }
        default:
            break;
    }

    return QString();
}

QString EnumToStr::encoder_polarity(DplSource::Encoder::Polarity polarity)
{
    switch(polarity) {
        case DplSource::Encoder::NORMAL:
        {
            return tr("Normal");
            break;
        }
        case DplSource::Encoder::INVERSE:
        {
            return tr("Inverse");
            break;
        }
        default:
            break;
    }

    return QString();
}

QString EnumToStr::encoder_name(DplSource::Axis::Driving driving)
{
    switch(driving) {
        case DplSource::Axis::ENCODER_X:
        {
            return tr("Encoder_X");
            break;
        }
        case DplSource::Axis::ENCODER_Y:
        {
            return tr("Encoder_Y");
            break;
        }
        case DplSource::Axis::TIMER:
        {
            return tr("Timer");
            break;
        }
        default:
            break;
    }

    return QString();
}

QString EnumToStr::encoder_mode(DplSource::Encoder::Mode mode)
{
    switch(mode) {
        case DplSource::Encoder::DOWN:
        {
            return tr("Down");
            break;
        }
        case DplSource::Encoder::UP:
        {
            return tr("Up");
            break;
        }
        case DplSource::Encoder::QUAD:
        {
            return tr("Quad");
            break;
        }
        default:
            break;
    }

    return QString();
}

QString EnumToStr::focallawer_focal_type(DplFocallaw::FocusCnf::Mode mode)
{
    switch(mode) {
        case DplFocallaw::FocusCnf::HALF_PATH:
        {
            return tr("Half_Path");
            break;
        }
        case DplFocallaw::FocusCnf::TRUE_DEPTH:
        {
            return tr("True_Depth");
            break;
        }
        case DplFocallaw::FocusCnf::PROJECTION:
        {
            return tr("Projection");
            break;
        }
        case DplFocallaw::FocusCnf::FOCAL_PLANE:
        {
            return tr("Focal_Plane");
            break;
        }
        case DplFocallaw::FocusCnf::DDF:
        {
            return tr("DDF");
            break;
        }
        default:
            break;
    }

    return QString();
}

QString EnumToStr::focallawer_law_type(DplFocallaw::ScanCnf::Mode mode)
{
    switch(mode) {
        case DplFocallaw::ScanCnf::Linear:
        {
            return tr("Linear");
            break;
        }
        case DplFocallaw::ScanCnf::Sectorial:
        {
            return tr("Sectorial");
            break;
        }
        default:
            break;
    }

    return QString();
}

QString EnumToStr::video_filter(bool enable)
{
    if(enable) {
        return tr("On");
    }
    return tr("Off");
}

QString EnumToStr::voltage(DplUt::GlobalTransceiver::Voltage voltage)
{
    switch (voltage) {
        case DplUt::GlobalTransceiver::V50:
        {
            return tr("50");
            break;
        }
        case DplUt::GlobalTransceiver::V100:
        {
            return tr("100");
            break;
        }
        case DplUt::GlobalTransceiver::V200:
        {
            return tr("200");
            break;
        }
        case DplUt::GlobalTransceiver::V400:
        {
            return tr("400");
            break;
        }
        default:
        break;
    }
    return QString();
}

QString EnumToStr::rectifier(DplFpga::Group::Rectifier rectifier)
{
    switch (rectifier) {
        case DplFpga::Group::RF:
        {
            return tr("RF");
            break;
        }
        case DplFpga::Group::POSITIVE_HW:
        {
            return tr("Positive_HW");
            break;
        }
        case DplFpga::Group::NEGATIVE_HW:
        {
            return tr("Negative_HW");
            break;
        }
        case DplFpga::Group::FULL_WAVE:
        {
            return tr("Full_Wave");
            break;
        }
        default:
        break;
    }
    return QString();
}

QString EnumToStr::rx_tx_mode(DplUt::Transceiver::Mode mode)
{
    switch (mode) {
        case DplUt::Transceiver::PE:
        {
            return tr("PE");
            break;
        }
        case DplUt::Transceiver::PC:
        {
            return tr("PC");
            break;
        }
        case DplUt::Transceiver::TT:
        {
            return tr("TT");
            break;
        }
        case DplUt::Transceiver::TOFD:
        {
            return tr("TOFD");
            break;
        }
        default:
        break;
    }
    return QString();
}

QString EnumToStr::band_pass_filter(int index, bool isPa)
{
    switch (index) {
        case 0:
        {
            return tr("none");
            break;
        }
        case 1000:
        {
            if(isPa) {
                return tr("1M");
            }
            return tr("1-2M");
            break;
        }
        case 2500:
        {
            if(isPa) {
                return tr("1.5M-2.5M");
            }
            return tr("2-3M");
            break;
        }
        case 5000:
        {
            if(isPa) {
                return tr("3-5M");
            }
            return tr("3-6M");
            break;
        }
        case 7500:
        {
            if(isPa) {
                return tr("7.5M");
            }
            return tr("6-10M");
            break;
        }
        case 20000:
        {
            return tr("10M");
            break;
        }
        default:
            return tr("Auto");
        break;
    }
    return QString();
}

QString EnumToStr::inspection_type(DplDevice::Group::Mode mode)
{
    switch (mode) {
        case DplDevice::Group::UT:
        {
            return tr("UT");
            break;
        }
        case DplDevice::Group::PA:
        {
            return tr("PA");
            break;
        }
        case DplDevice::Group::UT1:
        {
            return tr("UT1");
            break;
        }
        case DplDevice::Group::UT2:
        {
            return tr("UT2");
            break;
        }
        default:
        break;
    }
    return QString();
}

QString EnumToStr::part_geometry(DplFocallaw::Specimen::Type type)
{
    switch (type) {
        case DplFocallaw::Specimen::FLAT:
        {
            return tr("FLAT");
            break;
        }
        case DplFocallaw::Specimen::CYLINDER:
        {
            return tr("CYLINDER");
            break;
        }
        default:
            break;
    }
    return QString();
}





