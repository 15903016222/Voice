#ifndef __SAMPLE_P_H__
#define __SAMPLE_P_H__

#include <fpga/fpga.h>

namespace DplUt {

class SamplePrivate : public QObject
{
    Q_OBJECT
public:
    explicit SamplePrivate(const DplFpga::GroupPointer &fpgaGrp);

    /**
     * @brief auto_point_qty    获取自动采样点数
     * @param maxPointQty       最大采样点数
     * @return                  采样点数
     */
    int auto_point_qty(int maxPointQty) const;

public slots:
    void do_prf_changed();

public:
    /* attributions */
    DplFpga::GroupPointer m_fpgaGrp;
    bool m_dBRefFlag;
    float m_dBRef;
    bool m_autoset;                     // 自动设置采样点标志
};

}
#endif // __SAMPLE_P_H__
