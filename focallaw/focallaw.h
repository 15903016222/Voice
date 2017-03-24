#ifndef __FOCALLAW_H__
#define __FOCALLAW_H__

#include "point.h"
#include "pa_probe.h"
#include "wedge.h"

#include "flat.h"
#include "cylinder.h"

#include "beam.h"

#include <QObject>

namespace Dpl {

class FocallawPrivate;
class FOCALLAWSHARED_EXPORT Focallaw : public QObject
{
    Q_DECLARE_PRIVATE(Focallaw)
    Q_OBJECT
public:
    explicit Focallaw(QObject *parent = 0);
    ~Focallaw();

    enum ScanMode {
        Linear,     /* 线形扫描 */
        Sectorial   /* 扇形扫描 */
    };

    /**
     * @brief scan_mode 获取声束扫描模式
     * @return          扫描模式
     */
    ScanMode scan_mode() const;

    /**
     * @brief set_scan_mode 设置声束扫描模式
     * @param mode          扫描模式
     */
    void set_scan_mode(ScanMode mode);

    enum FocusMode {
        HALF_PATH,  /* 半声程 */
        TRUE_DEPTH, /* 真实深度 */
        PROJECTION, /* 投影 */
        FOCAL_PLANE,/* 任意面 */
        DDF         /* 动态聚焦 */
    };

    /**
     * @brief focus_mode    获取聚焦模式
     * @return              聚焦模式
     */
    FocusMode focus_mode() const;

    /**
     * @brief set_focus_mode    设置聚焦模式
     * @param mode              聚焦模式
     */
    void set_focus_mode(FocusMode mode);

    /**
     * @brief refract_angle 获取折射角度
     * @return
     */
    float refract_angle();
    bool set_refract_angle(float angle);

    /**
     * @brief probe 获取探头
     * @return      探头对象
     */
    const PaProbe &probe() const;

    /**
     * @brief set_probe 设置探头
     * @param p         探头对象
     */
    void set_probe(const PaProbe &p);

    /**
     * @brief wedge 获取锲块
     * @return      锲块对象
     */
    const Wedge &wedge() const;

    /**
     * @brief set_wedge 设置锲块
     * @param w         锲块对象
     */
    void set_wedge(const Wedge &w);

    /**
     * @brief specimen  获取工件
     * @return          工件对象
     */
    const SpecimenPointer &specimen() const;

    /**
     * @brief set_specimen  设置工件
     * @param s             工件对象
     */
    void set_specimen(const SpecimenPointer &s);

    const QList<BeamPointer> &beams() const;

    void update();

signals:

public slots:

private:
    FocallawPrivate *d_ptr;
};

}

#endif // __FOCALLAW_H__
