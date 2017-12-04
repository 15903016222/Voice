#include "area_menu.h"


namespace DplScanMenu {

AreaMenu::AreaMenu(QWidget *parent) :
    BaseMenu(parent),
    m_scanStartItem(new SpinMenuItem(this, tr("Scan Start"), tr("mm"))),
    m_scanEndItem(new SpinMenuItem(this, tr("Scan End"), tr("mm"))),
    m_scanResolutionItem(new SpinMenuItem(this, tr("Scan Res."), tr("mm"))),
    m_indexStartItem(new SpinMenuItem(this, tr("Index Start"), tr("mm"))),
    m_indexEndItem(new SpinMenuItem(this, tr("Index End"), tr("mm"))),
    m_indexResolutionItem(new SpinMenuItem(this, tr("Index Res."), tr("mm"))),
    m_scanAxis(DplSource::Scan::instance()->scan_axis()),
    m_indexAxis(DplSource::Scan::instance()->index_axis())
{
    m_layout0->addWidget(m_scanStartItem);
    m_layout1->addWidget(m_scanEndItem);
    m_layout2->addWidget(m_scanResolutionItem);
    m_layout3->addWidget(m_indexStartItem);
    m_layout4->addWidget(m_indexEndItem);
    m_layout5->addWidget(m_indexResolutionItem);

    /* Scan Start Menu Item */
    m_scanStartItem->set(0, 10000, 2, 0.01);
    m_scanStartItem->set_value(m_scanAxis->start());
    connect(m_scanStartItem, SIGNAL(value_changed(double)),
            this, SLOT(do_scanStartItem_changed(double)));

    /* Scan End menu item */
    m_scanEndItem->set(0, 10000, 2, 0.01);
    m_scanEndItem->set_value(m_scanAxis->end());
    connect(m_scanEndItem, SIGNAL(value_changed(double)),
            this, SLOT(do_scanEndItem_changed(double)));

    /* Scan Resolution menu item */
    m_scanResolutionItem->set(0, 100, 2, 0.01);
    m_scanResolutionItem->set_value(m_scanAxis->resolution());
    connect(m_scanResolutionItem, SIGNAL(value_changed(double)),
            this, SLOT(do_scanResolutionItem_changed(double)));

    /* Index Start Menu Item */
    m_indexStartItem->set(0, 10000, 2, 0.01);
    m_indexStartItem->set_value(m_indexAxis->start());
    connect(m_indexStartItem, SIGNAL(value_changed(double)),
            this, SLOT(do_indexStartItem_changed(double)));

    /* Index End Menu Item */
    m_indexEndItem->set(0, 10000, 2, 0.01);
    m_indexEndItem->set_value((m_indexAxis->end()));
    connect(m_indexEndItem, SIGNAL(value_changed(double)),
            this, SLOT(do_indexEndItem_changed(double)));

    /* Index Resolution Menu Item */
    m_indexResolutionItem->set(0, 100, 2, 0.01);
    m_indexResolutionItem->set_value((m_indexAxis->resolution()));
    connect(m_indexResolutionItem, SIGNAL(value_changed(double)),
            this, SLOT(do_indexResolutionItem_changed(double)));
}

AreaMenu::~AreaMenu()
{
}

void AreaMenu::do_scanStartItem_changed(double val)
{
    m_scanAxis->set_start(val);
}

void AreaMenu::do_scanEndItem_changed(double val)
{
    m_scanAxis->set_end(val);
}

void AreaMenu::do_scanResolutionItem_changed(double val)
{
    m_scanAxis->set_resolution(val);
}

void AreaMenu::do_indexStartItem_changed(double val)
{
    m_indexAxis->set_start(val);
}

void AreaMenu::do_indexEndItem_changed(double val)
{
    m_indexAxis->set_end(val);
}

void AreaMenu::do_indexResolutionItem_changed(double val)
{
    m_indexAxis->set_resolution(val);
}

}
