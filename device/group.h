/**
 * @file group_config.h
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#include <QObject>
#include "fpga/group.h"

namespace DplDevice {

class GroupPrivate;

class Group : public DplFpga::Group
{
public:
    explicit Group(int index);
    ~Group();

    enum UtUnitType {
        Time,
        SoundPath,
        TruePath
    };
    UtUnitType ut_unit();
    void set_ut_unit(UtUnitType type);

    /**
     * @brief velocity  获取声速
     * @return          返回声速大小，单位为(m/s)
     */
    quint32 velocity();

    /**
     * @brief set_velocity  设置声速
     * @param value         声速大小，单位为(m/s)
     */
    void set_velocity(quint32 value);

private:
    GroupPrivate *d;
};

}
