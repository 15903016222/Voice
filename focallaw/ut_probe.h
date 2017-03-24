/**
 * @file ut_probe.h
 * @brief 常规探头
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-24
 */
#ifndef __UT_PROBE_H__
#define __UT_PROBE_H__

#include "probe.h"

namespace DplFocallaw {

class UtProbePrivate;
class FOCALLAWSHARED_EXPORT UtProbe : public Probe
{
    Q_DECLARE_PRIVATE(UtProbe)
public:
    explicit UtProbe();
    explicit UtProbe(const UtProbe &p);

    ~UtProbe();

    bool is_pa() const { return false; }

    UtProbe &operator=(const UtProbe &p);

    /**
     * @brief load  加载探头文件
     * @param file  探头文件
     * @return      成功返回true， 否则false
     */
    bool load(const QString &fileName);

    /**
     * @brief save  保存探头数据
     * @param file  保存文件
     * @return      成功返回true，否则false
     */
    bool save(const QString &fileName);

private:
    UtProbePrivate *d_ptr;
};

typedef QSharedPointer<UtProbe> UtProbePointer;
}

#endif // __UT_PROBE_H__
