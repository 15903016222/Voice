/**
 * @file display_widget.cpp
 * @brief A/B/C/S显示布局管理类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "display_widget.h"
#include "a_scan/a_scan_vdisplay.h"
#include "a_scan/a_scan_hdisplay.h"
#include "s_scan/s_scan_display.h"
#include "b_scan/b_scan_vdisplay.h"
#include "b_scan/b_scan_hdisplay.h"
#include "c_scan/c_scan_hdisplay.h"
#include "c_scan/c_scan_vdisplay.h"
#include "fft/fft_hdisplay.h"
#include "line/line.h"

#include <ui/common/hbox_layout.h>
#include <ui/common/vbox_layout.h>

namespace DplUi {

template <typename ScanT>
class SingleLayout : public VBoxLayout
{
public:
    explicit SingleLayout(int grp, QWidget *parent=0) : VBoxLayout (parent)
    {
        addWidget(new ScanT(DplDevice::Device::instance()->get_group(grp)));
    }
};

typedef SingleLayout<AscanHDisplay> ALayoutH;
typedef SingleLayout<AscanVDisplay> ALayoutV;
typedef SingleLayout<CscanVDisplay> CLayoutV;
typedef SingleLayout<CscanHDisplay> CLayoutH;
typedef SingleLayout<SscanDisplay>  SLayout;
typedef SingleLayout<BscanVDisplay> BLayoutV;
typedef SingleLayout<BscanHDisplay> BLayoutH;
typedef SingleLayout<FFTHDisplay>   FFTLayoutH;

class ASLayout : public HBoxLayout
{
public:
    ASLayout(int grp, QWidget *parent = 0) : HBoxLayout (parent)
    {
        addLayout(new ALayoutV(grp), 1);

        addWidget(new Line(), 1);

        SscanDisplay *s = new SscanDisplay(DplDevice::Device::instance()->get_group(grp));
        s->hide_left_ruler();
        addWidget(s, 2);
    }
};

class SCLayout : public HBoxLayout
{
public:
    SCLayout(int grp, QWidget *parent) : HBoxLayout(parent)
    {
        SscanDisplay *s = new SscanDisplay(DplDevice::Device::instance()->get_group(grp));
        s->hide_color_ruler();
        addWidget(s, 1);

        addLayout(new CLayoutV(grp), 2);
    }
};

class ABLayout : public HBoxLayout
{
public:
    ABLayout(int grp, QWidget *parent) : HBoxLayout(parent)
    {
        addLayout(new ALayoutV(grp), 1);

        addWidget(new Line(Qt::Vertical), 1);

        BscanVDisplay *b = new BscanVDisplay(DplDevice::Device::instance()->get_group(grp));
        b->hide_left_ruler();
        addWidget(b, 2);
    }
};

class ABCLayout : public VBoxLayout
{
public:
    ABCLayout(int grp, QWidget *parent) : VBoxLayout(parent)
    {
        AscanHDisplay *a = new AscanHDisplay(DplDevice::Device::instance()->get_group(grp));
        a->hide_bottom_ruler();
        a->show_color_ruler();
        addWidget(a, 3);

        addLayout(new BLayoutH(grp), 4);

        addLayout(new CLayoutV(grp), 5);
    }
};


class ASBLayout : public VBoxLayout
{
public:
    ASBLayout(int grp, QWidget *parent) : VBoxLayout(parent)
    {
        addLayout(new ASLayout(grp), 1);
        addLayout(new BLayoutV(grp), 1);
    }
};


class ASCLayout : public VBoxLayout
{
public:
    ASCLayout(int grp, QWidget *parent) : VBoxLayout(parent)
    {
        addLayout(new ASLayout(grp), 1);
        addLayout(new CLayoutV(grp), 1);
    }
};


class AFFTLayout : public VBoxLayout
{
public:
    AFFTLayout(int grp, QWidget *parent) : VBoxLayout(parent)
    {
        addLayout(new ALayoutH(grp), 1);
        addLayout(new FFTLayoutH(grp), 1);
    }
};


DisplayWidget::DisplayWidget(const DplDisplay::DisplayPointer &display,
                             QWidget *parent) :
    QWidget(parent),
    m_display(display)
{
    new VBoxLayout(this);

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
    case DplDisplay::Display::AFFT:
        l = new AFFTLayout(grps.first(), w);
        break;
    default:
        break;
    }

    layout()->addWidget(w);
}



}
