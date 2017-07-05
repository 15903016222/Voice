#ifndef __DPLFPGA_GROUPS_H__
#define __DPLFPGA_GROUPS_H__

#include "group.h"
#include <QVector>

namespace DplFpga {

class FPGASHARED_EXPORT Groups
{
public:
    static const int MAX_GROUPS;

    static Groups *instance();

    const GroupPointer &at(int i) const;

    const GroupPointer &operator[](int i) const;

protected:
    Groups();

private:
    Q_DISABLE_COPY(Groups)
    QVector<GroupPointer> m_groups;
};

inline const GroupPointer &Groups::at(int i) const
{
    Q_ASSERT( i >= 0 && i < MAX_GROUPS );
    return m_groups[i];
}

inline const GroupPointer &Groups::operator[](int i) const
{
    return at(i);
}

}
#endif // __DPLFPGA_GROUPS_H__
