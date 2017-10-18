#ifndef __C_SCAN_DATA_H__
#define __C_SCAN_DATA_H__

#include <source/source.h>
#include <device/group.h>
#include "test_stub.h"

class CScanData
{
public:
    explicit CScanData(const DplDevice::GroupPointer &grp);

    /**
     * @brief get_peak_value    获取指定beam在闸门內最大值
     * @param beamPointer       正在处理的帧
     * @param beamCount         第beamIndex条beam
     * @param gateValue         存储闸门最大数值
     * @return  true 获取成功； false 获取失败
     */
    bool get_peak_value(const DplSource::BeamsPointer &beamsPointer, int beamIndex, double &gateValue);

    /**
     * @brief get_source_peak_value C扫源数据为Thickness，再根据不同的源机型C扫结果。
     * @param beamsPointer
     * @param beamCount
     * @param gateValue
     * @return
     */
    bool get_source_peak_value(const DplSource::BeamPointer &beamPointer,
                               double &gateValue);


    bool get_gate_position(DplSource::Beam::GateType type,
                           const DplSource::BeamPointer &beamPointer,
                           double &gateValue);

    bool get_gate_position_distance(DplSource::Beam::GateType type1,
                                    DplSource::Beam::GateType type2,
                                    const DplSource::BeamPointer &beamPointer,
                                    double &gateValue);

private:
    DplDevice::GroupPointer m_group;

};

typedef QSharedPointer<CScanData> CScanDataPointer;

#endif // __C_SCAN_DATA_H__
