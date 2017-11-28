#include "c_scan_time_image_item.h"

#include <source/source.h>
#include <source/scan.h>

CscanTimeImageItem::CscanTimeImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QGraphicsObject *parent)
    : TimeImageItem(palette, grp, parent),
      m_source(TestStub::instance()->get_source()),
      m_cscanDataPointer(new CScanData(grp)),
      m_thicknessSource(TestStub::instance()->get_thickness_source())
{
    m_initFinished = true;
}


bool CscanTimeImageItem::need_refresh(const DplSource::BeamsPointer &beams)
{
    QWriteLocker lock(&m_rwLock);

    if(TimeImageItem::need_refresh(beams)) {
        return true;
    }

    /* 更改扫查方式后（时间/编码器），需要更新C扫 */
    if(m_driving != DplSource::Scan::instance()->scan_axis()->driving()) {
        return true;
    }

    /* C扫的源更改后，需要更新C扫 */
    if(m_source != TestStub::instance()->get_source()) {
        m_source = TestStub::instance()->get_source();
        return true;
    }

    if((!m_beamsPointer.isNull()) && (beams->beam_qty() != m_beamsPointer->beam_qty())) {
        return true;
    }

    /* TODO */
    /* 闸门开始值、宽度、幅度更改后，需更新C扫 */
    if(gate_info_changed()) {
        return true;
    }

    /* 聚焦类型更改后，需要更新C扫 */

    /* （VPA/角度/beamQty）更改后，需要更新C扫 */


    /* Thickness数据源：A^、A^ - I^、A^ - I/等 */
    if(m_thicknessSource != TestStub::instance()->get_thickness_source()) {
        m_thicknessSource = TestStub::instance()->get_thickness_source();
        return true;
    }

    return false;
}



void CscanTimeImageItem::set_vertical_image_data(int beamsShowedCount,
                                             const BaseImageItem::S_CommonProperties &commonProperties,
                                             BaseImageItem::E_BEAM_TYPE type,
                                             const DplSource::BeamsPointer &beamsPointer)
{
    double beamQty = beamsPointer->beam_qty();
    double perBeamSpace = m_image->height() / beamQty;

    int beginLine  = 0;
    int endLine    = 0;
    int targetLine = 0;

    for(int num = 0; num < beamQty; ++num) {

        beginLine = perBeamSpace * num + 0.5;
        endLine   = beginLine + perBeamSpace + 0.5;
        int drawLine = endLine - beginLine;

        double gateValue;
        if(!m_cscanDataPointer->get_peak_value(beamsPointer, num, gateValue))
        {
            continue;
        }

        double gateValueTmp;
        m_cscanDataPointer->get_peak_value(m_beamsPointer, num, gateValueTmp);

        if(type == LAST_BEAM) {
            for(int offset = 0; offset < drawLine; ++offset) {

                for(int j = 0; j < commonProperties.pixCount; ++j) {

                    targetLine = beginLine + offset;

                    if(targetLine >= m_image->height() || targetLine < 0) {
                        continue;
                    }

                    int pos;
                    pos = m_image->width() - 1 - j;

                    quint8 *line    = (quint8*) m_image->scanLine(targetLine);

                    if(pos >= m_image->width() || pos < 0) {
                        continue;
                    }

                    line[pos] = gateValue;
                }
            }
        } else {
            for(int offset = 0; offset < drawLine; ++offset) {

                for(int j = 0; j < commonProperties.pixCount; ++j) {

                    targetLine = beginLine + offset;

                    if(targetLine >= m_image->height() || targetLine < 0) {
                        continue;
                    }

                    quint8 *line    = (quint8*) m_image->scanLine(targetLine);

                    int pos = beamsShowedCount * commonProperties.pixCount + j;
                    if(pos >= m_image->width() || pos < 0) {
                        continue;
                    }

                    line[pos] = gateValue;
                }
            }
        }
    }
}


bool CscanTimeImageItem::gate_info_changed()
{
    bool ret = false;
    switch (TestStub::instance()->get_source()) {
    case TestStub::SOURCE_A:
    {
        break;
    }
    case TestStub::SOURCE_B:
    {
        break;
    }
    case TestStub::SOURCE_I:
    {
        break;
    }
    case TestStub::SOURCE_T:
    {
        break;
    }
    default:
        break;
    }

    return ret;
}

