#include "tofd_menu.h"


namespace DplMeasurementMenu {

TofdMenu::TofdMenu(QWidget *parent) :
    BaseMenu(parent),
    m_selectItem(new ComboMenuItem(this, tr("Select"))),
    m_wedgeItem(new SpinMenuItem(this, tr("Wedge Sep."), "mm")),
    m_layerDepthItem(new LabelMenuItem(this, tr("Layer Depth"))),
    m_tofdCalItem(new LabelMenuItem(this, tr("TOFD Calculator"))),
    m_startItem(new SpinMenuItem(this, tr("Start"), "mm")),
    m_rangeItem(new SpinMenuItem(this, tr("Range"), "mm")),
    m_straighteningItem(new ComboMenuItem(this, tr("Straightening"))),
    m_removeLateralItem(new ComboMenuItem(this, tr("Remove Lateral"))),
    m_refPositionItem(new SpinMenuItem(this, tr("Ref.Position"), "mm")),
    m_depthCalibrationItem(new ComboMenuItem(this, tr("Depth\nCalibration")))
{
    m_layout0->addWidget(m_selectItem);

    /* Setting */
    m_layout1->addWidget(m_wedgeItem);
    m_layout2->addWidget(m_layerDepthItem);
    m_layout3->addWidget(m_tofdCalItem);
    m_layout4->addWidget(m_startItem);
    m_layout5->addWidget(m_rangeItem);

    /* Analysis */
    m_layout1->addWidget(m_straighteningItem);
    m_layout2->addWidget(m_removeLateralItem);
    m_layout3->addWidget(m_refPositionItem);
    m_layout4->addWidget(m_depthCalibrationItem);

    /* Select menu item */
    m_selectItem->add_item(tr("Settings"));
    m_selectItem->add_item(tr("Analysis"));
    connect(m_selectItem, SIGNAL(value_changed(int)),
            this, SLOT(do_selectItem_changed(int)));

    /* Wedge Sep. menu item */
    m_wedgeItem->set(0, 10000, 1);

    /* Start menu item */
    m_startItem->set(0, 16000, 2);

    /* Range menu item */
    m_rangeItem->set(0, 16000, 2);

    /* Straightening menu item */
    m_straighteningItem->set(s_onOff);

    /* Remove Lateral menu item */
    m_removeLateralItem->set(s_onOff);

    /* Ref.Position menu item */
    m_refPositionItem->set(0, 2000, 2);

    /* Depth Calibration menu item */
    m_depthCalibrationItem->set(s_onOff);

    do_selectItem_changed(0);
}

TofdMenu::~TofdMenu()
{
}

void TofdMenu::do_selectItem_changed(int index)
{
    m_wedgeItem->setVisible(!index);
    m_layerDepthItem->setVisible(!index);
    m_tofdCalItem->setVisible(!index);
    m_startItem->setVisible(!index);
    m_rangeItem->setVisible(!index);

    m_straighteningItem->setVisible(!!index);
    m_removeLateralItem->setVisible(!!index);
    m_refPositionItem->setVisible(!!index);
    m_depthCalibrationItem->setVisible(!!index);
}

void TofdMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_selectItem->set_title(tr("Select"));
        m_wedgeItem->set_title(tr("Wedge Sep."));
        m_layerDepthItem->set_title(tr("Layer Depth"));
        m_tofdCalItem->set_title(tr("TOFD Calculator"));
        m_startItem->set_title(tr("Start"));
        m_rangeItem->set_title(tr("Range"));
        m_straighteningItem->set_title(tr("Straightening"));
        m_removeLateralItem->set_title(tr("Remove Lateral"));
        m_refPositionItem->set_title(tr("Ref.Position"));
        m_depthCalibrationItem->set_title(tr("Depth\nCalibration"));
        return;
    }
    BaseMenu::changeEvent(e);
}

}
