#include "tofd_menu.h"
#include "label_menu_item.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"

namespace DplMeasurementMenu {

TofdMenu::TofdMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Select menu item */
    QStringList selectList;
    selectList.append(tr("TOFD Settings"));
    selectList.append(tr("TOFD Analysis"));
    m_selectItem.set(tr("Select"), selectList);
    m_selectItem.set_dispay_mode(ComboMenuItem::SUFFIX);
    connect(&m_selectItem, SIGNAL(value_changed(int)), this, SLOT(do_select_changed(int)));

    /* Wedge Sep. menu item */
    m_wedgeItem.set(tr("Wedge Sep."), "mm", 0, 10000, 1);
    /* Layer Depth menu item */
    m_layerDepthItem.set(tr("Layer Depth"), "");
    /* TOFD Calculator menu item */
    m_tofdCalItem.set(tr("TOFD Calculator"), "");
    /* Start menu item */
    m_startItem.set(tr("Start"), "mm", 0, 16000, 2);
    /* Range menu item */
    m_rangeItem.set(tr("Range"), "mm", 0, 16000, 2);


    /* Straightening menu item */
    m_straighteningItem.set(tr("Straightening"), s_onOff);
    /* Remove Lateral menu item */
    m_removeLateralItem.set(tr("Remove Lateral"), s_onOff);
    /* Ref.Position menu item */
    m_refPositionItem.set(tr("Ref.Position"), "mm", 0, 2000, 2);
    /* Depth Calibration menu item */
    m_depthCalibrationItem.set(tr("Depth Calibration"), s_onOff);
}

TofdMenu::~TofdMenu()
{
}

void TofdMenu::show()
{
    if (m_selectItem.current_index() == 0) {
        show_setting();
    } else {
        show_analysis();
    }
}

void TofdMenu::hide()
{
    if (m_selectItem.current_index() == 0) {
        hide_setting();
    } else {
        hide_analysis();
    }
}

void TofdMenu::show_setting()
{
    ui->layout0->addWidget(&m_selectItem);
    ui->layout1->addWidget(&m_wedgeItem);
    ui->layout2->addWidget(&m_layerDepthItem);
    ui->layout3->addWidget(&m_tofdCalItem);
    ui->layout4->addWidget(&m_startItem);
    ui->layout5->addWidget(&m_rangeItem);
    m_selectItem.show();
    m_wedgeItem.show();
    m_layerDepthItem.show();
    m_tofdCalItem.show();
    m_startItem.show();
    m_rangeItem.show();
}

void TofdMenu::hide_setting()
{
    ui->layout0->removeWidget(&m_selectItem);
    ui->layout1->removeWidget(&m_wedgeItem);
    ui->layout2->removeWidget(&m_layerDepthItem);
    ui->layout3->removeWidget(&m_tofdCalItem);
    ui->layout4->removeWidget(&m_startItem);
    ui->layout5->removeWidget(&m_rangeItem);
    m_selectItem.hide();
    m_wedgeItem.hide();
    m_layerDepthItem.hide();
    m_tofdCalItem.hide();
    m_startItem.hide();
    m_rangeItem.hide();
}

void TofdMenu::show_analysis()
{
    ui->layout0->addWidget(&m_selectItem);
    ui->layout1->addWidget(&m_straighteningItem);
    ui->layout2->addWidget(&m_removeLateralItem);
    ui->layout3->addWidget(&m_refPositionItem);
    ui->layout4->addWidget(&m_depthCalibrationItem);
    m_selectItem.show();
    m_straighteningItem.show();
    m_removeLateralItem.show();
    m_refPositionItem.show();
    m_depthCalibrationItem.show();
}

void TofdMenu::hide_analysis()
{
    ui->layout0->removeWidget(&m_selectItem);
    ui->layout1->removeWidget(&m_straighteningItem);
    ui->layout2->removeWidget(&m_removeLateralItem);
    ui->layout3->removeWidget(&m_refPositionItem);
    ui->layout4->removeWidget(&m_depthCalibrationItem);
    m_selectItem.hide();
    m_straighteningItem.hide();
    m_removeLateralItem.hide();
    m_refPositionItem.hide();
    m_depthCalibrationItem.hide();
}

void TofdMenu::do_select_changed(int index)
{
    if (0 == index) {
        hide_analysis();
        show_setting();
    } else {
        hide_setting();
        show_analysis();
    }
}

}
