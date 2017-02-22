#include "scan_layout.h"
#include <QLayout>

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
        a_layout();
        break;
    default:
        break;
    }
}

void ScanLayout::a_layout()
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);
    l->setObjectName(QString("A%1").arg(m_grpIds.first()));
}
