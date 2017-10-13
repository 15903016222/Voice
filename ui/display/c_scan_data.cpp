#include "c_scan_data.h"

CScanData::CScanData(const DplDevice::GroupPointer &grp)
    : m_group(grp)
{

}

bool CScanData::get_peak_value(const DplSource::BeamsPointer &beamsPointer, int beamCount, double &gateValue)
{
    if(beamCount > beamsPointer->beam_qty()) {
        return false;
    }

   DplSource::BeamPointer beamPoint = beamsPointer->get(beamCount);

   if(beamPoint.isNull()) {
       return false;
   }

   switch (TestStub::instance()->get_source()) {
   /*  A%: 闸门 A 中测得的信号的峰值波幅  */
   case TestStub::SOURCE_A:
   {
       gateValue = beamPoint->gate_peak(DplSource::Beam::GATE_A);
       return true;
       break;
   }
    /*  B%: 闸门 B 中测得的信号的峰值波幅  */
   case TestStub::SOURCE_B:
   {
       gateValue = beamPoint->gate_peak(DplSource::Beam::GATE_B);
       return true;
       break;
   }
    /*  T(？): 厚度  */
   case TestStub::SOURCE_T:
   {
       return get_source_peak_value(beamsPointer, beamCount, gateValue);
       break;
   }
    /*  I/: 闸门 I 内信号的前沿位置  */
   case TestStub::SOURCE_I:
   {
        /* 闸门I內的信号前沿位置? */
       if (m_group->ut_unit() == DplDevice::Group::Time) {
           gateValue = beamsPointer->get(beamCount)->gate_peak_position(DplSource::Beam::GATE_I) / 1000.0;
       } else {
           gateValue = beamsPointer->get(beamCount)->gate_peak_position(DplSource::Beam::GATE_I) * m_group->focallawer()->specimen()->velocity() / 200000.0;
       }

       return true;
       break;
   }
   case TestStub::SOURCE_OFF:
   {
       return false;
       break;
   }
   default:
       return false;
       break;
   }
}


bool CScanData::get_source_peak_value(const DplSource::BeamsPointer &beamsPointer, int beamCount, double &gateValue)
{
    TestStub::THICKNESS_SOURCE thicknessSourceType = TestStub::instance()->get_thickness_source();

    switch (thicknessSourceType) {
    /*  T(A^): 厚度  */
    case TestStub::A_POSITION:                      /* A^ */
    {
        return get_gate_position(DplSource::Beam::GATE_A, beamsPointer, beamCount, gateValue);
        break;
    }
    /*  T(A^-I^)、T(A^-I/): 厚度  */
    case TestStub::A_POSITION_MINUS_I_POSITION:     /* A^ - I^ */
    case TestStub::A_POSITION_MINUS_I_AMPLITUDE:    /* A^ - I/ */
    {
        return get_gate_position_distance(DplSource::Beam::GATE_A,
                                   DplSource::Beam::GATE_I,
                                   beamsPointer,
                                   beamCount,
                                   gateValue);
        break;
    }
    /*  T(B^): 厚度  */
    case TestStub::B_POSITION:                       /* B^ */
    {
        return get_gate_position(DplSource::Beam::GATE_A,
                          beamsPointer,
                          beamCount,
                          gateValue);
        break;
    }
    /*  T(B^-I^)、T(B^-I/): 厚度  */
    case TestStub::B_POSITION_MINUS_I_POSITION:      /* B^ - I^*/
    case TestStub::B_POSITION_MINUS_I_AMPLITUDE:     /* B^ - I/ */
    {
        return get_gate_position_distance(DplSource::Beam::GATE_B,
                                   DplSource::Beam::GATE_I,
                                   beamsPointer,
                                   beamCount,
                                   gateValue);
        break;
    }
    /*  T(B^-A^): 厚度  */
    case TestStub::B_POSITION_MINUS_A_POSITION:      /* B^ - A^ */
    {
        return get_gate_position_distance(DplSource::Beam::GATE_B,
                                   DplSource::Beam::GATE_A,
                                   beamsPointer,
                                   beamCount,
                                   gateValue);
        break;
    }
    /*  T(I^): 厚度  */
    case TestStub::I_POSITION:            /* I^ */
    case TestStub::I_AMPLITUDE:           /* I/ */
    {
        return get_gate_position(DplSource::Beam::GATE_A, beamsPointer, beamCount, gateValue);
        break;
    }
    default:
        break;
    }

    return false;
}


bool CScanData::get_gate_position(DplSource::Beam::GateType type,
                                   const DplSource::BeamsPointer &beamsPointer,
                                   int beamCount,
                                   double &gateValue)
{
    double tmpValue;
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        tmpValue = beamsPointer->get(beamCount)->gate_peak_position(type) / 1000.0;
    } else {
        tmpValue = beamsPointer->get(beamCount)->gate_peak_position(type) * m_group->focallawer()->specimen()->velocity() / 200000.0;
    }

    if(tmpValue < TestStub::instance()->get_min_thickness())
        gateValue = 0 ;
    else if(tmpValue > TestStub::instance()->get_max_thickness())
        gateValue = 255 ;
    else
        gateValue = 255 * tmpValue / fabs(TestStub::instance()->get_max_thickness() - TestStub::instance()->get_min_thickness());
    return true;
}


bool CScanData::get_gate_position_distance(DplSource::Beam::GateType type1,
                                            DplSource::Beam::GateType type2,
                                            const DplSource::BeamsPointer &beamsPointer,
                                            int beamCount,
                                            double &gateValue)
{
    double tmpValue1;
    double tmpValue2;

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        tmpValue1= beamsPointer->get(beamCount)->gate_peak_position(type1) / 1000.0;
        tmpValue2= beamsPointer->get(beamCount)->gate_peak_position(type2) / 1000.0;
    } else {
        tmpValue1 = beamsPointer->get(beamCount)->gate_peak_position(type1) * m_group->focallawer()->specimen()->velocity() / 200000.0;
        tmpValue2 = beamsPointer->get(beamCount)->gate_peak_position(type2) * m_group->focallawer()->specimen()->velocity() / 200000.0;
    }

    double spaceValue = fabs(tmpValue1 - tmpValue2);

    if(spaceValue < TestStub::instance()->get_min_thickness())
        gateValue = 0;
    else if(spaceValue > TestStub::instance()->get_max_thickness())
        gateValue = 255;
    else
        gateValue = 255 * (tmpValue1 - TestStub::instance()->get_min_thickness()) / spaceValue;

    return true;
}

