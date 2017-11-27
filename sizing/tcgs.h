/**
 * @file tcgs.h
 * @brief Tcg组
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-11-20
 */
#ifndef __DPLSIZING_TCGS_H__
#define __DPLSIZING_TCGS_H__

#include "tcg.h"
#include <fpga/group.h>
#include <focallaw/focallawer.h>

namespace DplSizing {

class TcgsPrivate;
class Tcgs : public QObject
{
    Q_OBJECT
public:
    explicit Tcgs(const DplFpga::GroupPointer &fpgaGroup, const DplFocallaw::FocallawerPointer &focallawer);
    ~Tcgs();

    /**
     * @brief enable    获取Tcg使能状态
     * @return          开启返回true,关闭返回false
     */
    bool enable() const;

    /**
     * @brief set_enable    使能Tcg功能
     * @param flag          true为开启,false为关闭
     * @return              设置成功返回true,失败返回false
     */
    bool set_enable(bool flag);

    /**
     * @brief count 获取Tcg数量
     * @return      数量
     */
    int count() const;

    /**
     * @brief point_qty 获取点数
     * @return
     */
    int point_count() const;

    /**
     * @brief add_point 添加点
     * @return          添加成功返回true,失败返回false
     */
    bool add_point();

    /**
     * @brief delete_point  删除点
     * @return              删除成功返回true,失败返回false
     */
    bool delete_point();

    /**
     * @brief tcg   获取指定Tcg对象
     * @param index Tcg索引号(从0开始)
     * @return      Tcg对象
     */
    TcgPointer tcg(int index) const;

    /**
     * @brief current_tcg   获取当前Tcg对象
     * @return
     */
    TcgPointer current_tcg() const;

    /**
     * @brief set_current_tcg   设置当前Tcg对象
     * @param index             索引号(从0开始)
     * @return                  成功返回true,失败返回false
     */
    bool set_current_tcg(int index);

    /**
     * @brief current_point_index   获取当前Point索引号
     * @return                      索引号(从0开始)
     */
    int current_point_index() const;

    /**
     * @brief set_current_point 设置当前Point对象
     * @param index             索引号(从0开始)
     * @return                  成功返回true,失败返回false
     */
    bool set_current_point(int index);

    /**
     * @brief set_all   设置所有tcg
     * @param flag      true为设置所有tcg,false为设置当前tcg
     */
    void set_all(bool flag);

    /**
     * @brief position  获取Tcg的当前点位置
     * @return          位置(ns)
     */
    int position() const;

    /**
     * @brief set_position  设置点位置,如果设置了set_all,则设置所有tcg,否则设置当前tcg
     * @param val           点位置(ns)
     * @return              成功返回true,失败返回false
     */
    bool set_position(int val);

    /**
     * @brief gain  获取当前Tcg的当前点增益
     * @return      增益(dB)
     */
    float gain() const;

    /**
     * @brief set_gain  设置点增益,如果设置了set_all,则设置所有tcg,否则设置当前tcg
     * @param val       增益(dB)
     * @return          成功返回true,失败返回false
     */
    bool set_gain(float val);

    /**
     * @brief amplitude 获取当前Tcg的当前点幅度
     * @return          幅度
     */
    float amplitude() const;

signals:
    void changed();
    void current_point_changed();

private:
    TcgsPrivate *d;
};

typedef QSharedPointer<Tcgs> TcgsPointer;

}
#endif // __DPLSIZING_TCGS_H__
