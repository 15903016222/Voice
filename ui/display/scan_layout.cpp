#include "scan_layout.h"
#include <QLayout>

#include <QDebug>

ScanLayout::ScanLayout(QWidget *parent) : QWidget(parent)
{

}

void ScanLayout::set_mode(ScanLayout::Mode mode, const QList<int> &grpIds)
{
    if (mode == m_mode
            && grpIds == m_grpIds) {
        return;
    }

    m_mode = mode;
    m_grpIds = grpIds;

    QObjectList objs = children();
    while (!objs.isEmpty()) {
        delete objs.takeFirst();
    }

    switch (mode) {
    case A:
        a_layout(m_grpIds.first());
        break;
    case S:
        s_layout(m_grpIds.first());
        break;
    case C:
        c_layout(m_grpIds.first());
        break;
    case AS:
        as_layout(m_grpIds.first());
        break;
    case SC:
        sc_layout(m_grpIds.first());
        break;
    case AB:
        ab_layout(m_grpIds.first());
        break;
    case ABC:
        abc_layout(m_grpIds.first());
        break;
    case ASB:
        asb_layout(m_grpIds.first());
        break;
    case ASC:
        asc_layout(m_grpIds.first());
        break;
    default:
        break;
    }
}

template <typename T>
T *ScanLayout::new_layout(char mode, int id)
{
    T *l = NULL;
    if (layout()) {
        l = new T();
    } else {
        l = new T(this);
    }
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);
    l->setObjectName(QString("%1%2").arg(mode).arg(id));
    return l;
}

QLayout *ScanLayout::as_layout(int id)
{
    QHBoxLayout *l = new_layout<QHBoxLayout>();
    l->addLayout(a_layout(id), 1);
    l->addLayout(s_layout(id), 2);
    return l;
}

QLayout *ScanLayout::sc_layout(int id)
{
    QHBoxLayout *l = new_layout<QHBoxLayout>();
    l->addLayout(s_layout(id), 1);
    l->addLayout(c_layout(id), 2);
    return l;
}

QLayout *ScanLayout::ab_layout(int id)
{
    QHBoxLayout *l = new_layout<QHBoxLayout>();
    l->addLayout(a_layout(id), 1);
    l->addLayout(b_layout(id), 2);
    return l;
}

QLayout *ScanLayout::abc_layout(int id)
{
    QVBoxLayout *l = new_layout<QVBoxLayout>();
    l->addLayout(a_layout(id));
    l->addLayout(b_layout(id));
    l->addLayout(c_layout(id));
    return l;
}

QLayout *ScanLayout::asb_layout(int id)
{
    QVBoxLayout *l = new_layout<QVBoxLayout>();

    l->addLayout(as_layout(id));
    l->addLayout(b_layout(id));

    return l;
}

QLayout *ScanLayout::asc_layout(int id)
{
    QVBoxLayout *l = new_layout<QVBoxLayout>();

    l->addLayout(as_layout(id));
    l->addLayout(c_layout(id));

    return l;
}