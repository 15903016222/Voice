#include "scan_display.h"

#include "color_bar.h"
#include "ruler/ruler.h"
#include <QLabel>
#include <ui/common/hbox_layout.h>
#include <ui/common/vbox_layout.h>

ScanDisplay::ScanDisplay(QWidget *parent) : QWidget(parent),
    m_titleLabel(new QLabel(this)),
    m_colorBar(new ColorBar(this)),
    m_leftRuler(new Ruler(Ruler::RIGHT, "", this)),
    m_rightRuler(new Ruler(Ruler::LEFT, "", this)),
    m_bottomRuler(new Ruler(Ruler::TOP, "", this)),
    m_scanLayout(new VBoxLayout())
{
    m_titleLabel->setStyleSheet("QLabel{background-color:rgb(0, 90, 130);\ncolor:white;}");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_leftRuler->setMinimumWidth(20);
    m_rightRuler->setMinimumWidth(20);
    m_bottomRuler->setMinimumHeight(20);
    m_bottomRuler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
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

    vlayout1->addWidget(m_leftRuler, 1);
    vlayout1->addItem(new QSpacerItem(0, 20, QSizePolicy::Ignored, QSizePolicy::Fixed));

    vlayout2->addLayout(m_scanLayout, 1);
    vlayout2->addWidget(m_bottomRuler);

    vlayout3->addWidget(m_colorBar, 1);
    vlayout3->addItem(new QSpacerItem(0, 20, QSizePolicy::Ignored, QSizePolicy::Fixed));

    vlayout4->addWidget(m_rightRuler, 1);
    vlayout4->addItem(new QSpacerItem(0, 20, QSizePolicy::Ignored, QSizePolicy::Fixed));
}
