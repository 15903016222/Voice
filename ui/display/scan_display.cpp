#include "scan_display.h"

#include "color_bar.h"
#include "ruler_widget.h"

#include <QLabel>
#include <ui/common/hbox_layout.h>
#include <ui/common/vbox_layout.h>

ScanDisplay::ScanDisplay(QWidget *parent) : QWidget(parent),
    m_titleLabel(new QLabel(this)),
    m_colorBar(new ColorBar(this)),
    m_leftRuler(new Ruler(this)),
    m_rightRuler(new Ruler(this)),
    m_bottomRuler(new Ruler(this)),
    m_scanLayout(new VBoxLayout)
{
    QVBoxLayout *l = new VBoxLayout(this);
    QHBoxLayout *hlayout1 = new HBoxLayout();
    QHBoxLayout *hlayout2 = new HBoxLayout();

    l->addWidget(m_titleLabel);
    l->addLayout(hlayout1, 1);
    l->addLayout(hlayout2);

    hlayout1->addWidget(m_leftRuler);
    hlayout1->addLayout(m_scanLayout, 1);
    hlayout1->addWidget(m_colorBar);
    hlayout1->addWidget(m_rightRuler);

    hlayout2->addWidget(new QWidget(this));

}
