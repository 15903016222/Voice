#include "scan_display.h"
#include "scan_view.h"
#include "scan_scene.h"

#include "../color_bar/color_bar.h"
#include "../ruler/ruler.h"

#include <ui/common/hbox_layout.h>
#include <ui/common/vbox_layout.h>

#include <QLabel>

ScanDisplay::ScanDisplay(QWidget *parent) : QWidget(parent),
    m_titleLabel(new QLabel(this)),
    m_colorRuler(new Ruler(Ruler::LEFT, "", this)),
    m_colorBar(new ColorBar(this)),
    m_leftLayout(new VBoxLayout()),
    m_bottomLayout(new VBoxLayout()),
    m_view(new ScanView(this)),
    m_scene(new ScanScene(this))
{
    clearFocus();
    setFocusPolicy(Qt::NoFocus);
    m_view->setFocusPolicy(Qt::NoFocus);
    m_view->clearFocus();

    m_titleLabel->setStyleSheet("QLabel{background-color:rgb(0, 90, 130);\ncolor:white;}");
    m_titleLabel->setAlignment(Qt::AlignCenter);

    m_colorRuler->setMinimumWidth(20);
    m_colorRuler->set_unit("(%)");
    m_colorRuler->set_prec(0);

    m_colorBar->setMinimumWidth(5);

    VBoxLayout *l = new VBoxLayout(this);
    HBoxLayout *hlayout = new HBoxLayout();

    VBoxLayout *vlayout1 = new VBoxLayout();
    VBoxLayout *vlayout2 = new VBoxLayout();
    VBoxLayout *vlayout3 = new VBoxLayout();
    VBoxLayout *vlayout4 = new VBoxLayout();

    l->addWidget(m_titleLabel);
    l->addLayout(hlayout, 1);

    hlayout->addLayout(vlayout1);
    hlayout->addLayout(vlayout2, 1);
    hlayout->addLayout(vlayout3);
    hlayout->addLayout(vlayout4);

    vlayout1->addLayout(m_leftLayout, 1);
    vlayout1->addItem(new QSpacerItem(0, 20, QSizePolicy::Ignored, QSizePolicy::Fixed));

    vlayout2->addWidget(m_view, 1);
    vlayout2->addLayout(m_bottomLayout);

    vlayout3->addWidget(m_colorBar, 1);
    vlayout3->addItem(new QSpacerItem(0, 20, QSizePolicy::Ignored, QSizePolicy::Fixed));

    vlayout4->addWidget(m_colorRuler, 1);
    vlayout4->addItem(new QSpacerItem(0, 20, QSizePolicy::Ignored, QSizePolicy::Fixed));

    m_view->setScene(m_scene);
    connect(m_view, SIGNAL(size_changed(QSize)),
            this, SLOT(resize_event(QSize)));
}
