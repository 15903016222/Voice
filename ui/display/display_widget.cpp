/**
 * @file display_widget.cpp
 * @brief A/B/C/S显示布局管理类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "display_widget.h"
#include "a_scan_vdisplay.h"
#include "a_scan_hdisplay.h"
#include "s_scan_display.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <source/source.h>

#include <QDebug>

namespace DplUi {

class VLayout : public QVBoxLayout
{
public:
    VLayout(QWidget *parent) : QVBoxLayout(parent)
    {
        setContentsMargins(0, 0, 0, 0);
        setSpacing(0);
    }
};

class HLayout : public QHBoxLayout
{
public:
    HLayout(QWidget *parent) : QHBoxLayout(parent)
    {
        setContentsMargins(0, 0, 0, 0);
        setSpacing(0);
    }
};

template <typename ScanT>
class SingleLayout : public VLayout
{
public:
    explicit SingleLayout(int grp, QWidget *parent) : VLayout (parent)
    {
        addWidget(new ScanT(DplDevice::Device::instance()->get_group(grp), parent));
    }
};

typedef SingleLayout<AscanHDisplay> ALayoutH;
typedef SingleLayout<AscanVDisplay> ALayoutV;

class ASLayout : public HLayout
{
public:
    ASLayout(int grp, QWidget *parent) : HLayout (parent)
    {
        addLayout(new SingleLayout<AscanVDisplay>(grp, parent), 1);
//        addLayout(new SingleLayout<Scan);
    }
};

DisplayWidget::DisplayWidget(const DplDisplay::DisplayPointer &display,
                             QWidget *parent) :
    QWidget(parent),
    m_display(display)
{
    DplSource::Source *source = DplSource::Source::instance();

    new VLayout(this);

    connect(static_cast<DplDisplay::Display *>(display.data()),
            SIGNAL(layout_changed(DplDisplay::Display::Layout,QVector<int>)),
            this,
            SLOT(set_layout(DplDisplay::Display::Layout,QVector<int>)));

    set_layout(display->layout(), display->grps());

    source->start();
}

void DisplayWidget::set_layout(DplDisplay::Display::Layout mode, const QVector<int> &grps)
{
    QWidget *w = this->findChild<QWidget*>("TopWidget");
    if (w != NULL) {
        delete w;
    }

    w = new QWidget(this);
    w->setObjectName("TopWidget");

    QLayout *l = NULL;
    switch (mode) {
    case DplDisplay::Display::A:
        l = new ALayoutH(grps.first(), w);
        break;
    case DplDisplay::Display::S:
        l = new ALayoutH(grps.first(), w);
        break;
    case DplDisplay::Display::C:
        l = new ALayoutH(grps.first(), w);
        break;
    case DplDisplay::Display::AS:
        l = new ASLayout(grps.first(), w);
        break;
    case DplDisplay::Display::SC:
        break;
    case DplDisplay::Display::AB:
        break;
    case DplDisplay::Display::ABC:
        break;
    case DplDisplay::Display::ASB:
        break;
    case DplDisplay::Display::ASC:
        break;
    default:
        break;
    }

    layout()->addWidget(w);
}



}
