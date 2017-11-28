/**
 * @file display_widget.cpp
 * @brief A/B/C/S显示布局管理类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "display_widget.h"
#include "a_scan_vdisplay.h"
#include "a_scan_hdisplay.h"
#include "c_scan_vdisplay.h"
#include "s_scan_display.h"
#include "b_scan_vdisplay.h"
#include "b_scan_hdisplay.h"
#include "c_scan_hdisplay.h"
#include "c_scan_vdisplay.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

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
    explicit SingleLayout(int grp, QWidget *parent = 0) : VLayout (parent)
    {
        addWidget(new ScanT(DplDevice::Device::instance()->get_group(grp), parent));
    }
};

typedef SingleLayout<AscanHDisplay> ALayoutH;
typedef SingleLayout<AscanVDisplay> ALayoutV;
typedef SingleLayout<CscanVDisplay> CLayoutV;
typedef SingleLayout<CscanHDisplay> CLayoutH;
typedef SingleLayout<SscanDisplay>  SLayout;
typedef SingleLayout<BscanVDisplay> BLayoutV;
typedef SingleLayout<BscanHDisplay> BLayoutH;

class ASLayout : public HLayout
{
public:
    ASLayout(int grp, QWidget *parent = 0) : HLayout (parent)
    {
        addLayout(new ALayoutV(grp), 1);
        addLayout(new SLayout(grp), 2);
    }
};

class SCLayout : public HLayout
{
public:
    SCLayout(int grp, QWidget *parent) : HLayout(parent)
    {
        addLayout(new SLayout(grp), 1);
        addLayout(new CLayoutV(grp), 2);
    }
};

class ABLayout : public HLayout
{
public:
    ABLayout(int grp, QWidget *parent) : HLayout(parent)
    {
        addLayout(new ALayoutV(grp), 1);
        addLayout(new BLayoutV(grp), 2);
    }
};

class ABCLayout : public VLayout
{
public:
    ABCLayout(int grp, QWidget *parent) : VLayout(parent)
    {
        addLayout(new ALayoutH(grp), 1);
        addLayout(new BLayoutH(grp), 2);
        addLayout(new CLayoutH(grp), 3);
    }
};


class ASBLayout : public VLayout
{
public:
    ASBLayout(int grp, QWidget *parent) : VLayout(parent)
    {
        addLayout(new ASLayout(grp), 1);
        addLayout(new BLayoutV(grp), 1);
    }
};


class ASCLayout : public VLayout
{
public:
    ASCLayout(int grp, QWidget *parent) : VLayout(parent)
    {
        addLayout(new ASLayout(grp), 1);
        addLayout(new CLayoutV(grp), 1);
    }
};


DisplayWidget::DisplayWidget(const DplDisplay::DisplayPointer &display,
                             QWidget *parent) :
    QWidget(parent),
    m_display(display)
{
    setStyleSheet(QString("background-color: rgb(0, 0, 0)"));

    new VLayout(this);

    connect(static_cast<DplDisplay::Display *>(display.data()),
            SIGNAL(layout_changed(DplDisplay::Display::Layout,QVector<int>)),
            this,
            SLOT(set_layout(DplDisplay::Display::Layout,QVector<int>)));

    set_layout(display->layout(), display->grps());
}

void DisplayWidget::set_layout(DplDisplay::Display::Layout mode, const QVector<int> &grps)
{
    QWidget *w = this->findChild<QWidget*>("TopWidget");
    if (w != NULL) {
        delete w;
    }

    w = new QWidget();
    w->setObjectName("TopWidget");

    QLayout *l = NULL;
    switch (mode) {
    case DplDisplay::Display::A:
        l = new ALayoutH(grps.first(), w);
        break;
    case DplDisplay::Display::S:
        l = new SLayout(grps.first(), w);
        break;
    case DplDisplay::Display::C:
        l = new CLayoutV(grps.first(), w);
        break;
    case DplDisplay::Display::AS:
        l = new ASLayout(grps.first(), w);
        break;
    case DplDisplay::Display::SC:
        l = new SCLayout(grps.first(), w);
        break;
    case DplDisplay::Display::AB:
        l = new ABLayout(grps.first(), w);
        break;
    case DplDisplay::Display::ABC:
        l = new ABCLayout(grps.first(), w);
        break;
    case DplDisplay::Display::ASB:
        l = new ASBLayout(grps.first(), w);
        break;
    case DplDisplay::Display::ASC:
        l = new ASCLayout(grps.first(), w);
        break;
    default:
        break;
    }

    layout()->addWidget(w);
}



}
