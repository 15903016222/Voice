/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "ut_advanced_menu.h"
#include "ui_base_menu.h"

#include <QDebug>

namespace DplUtSettingMenu {

UtAdvancedMenu::UtAdvancedMenu(QWidget *parent) :
    BaseMenu(parent),
    m_eightPercentItem(new LabelMenuItem(this, tr("Set 80%"))),
    m_dbRefItem(new ComboMenuItem(this, tr("dB Ref."))),
    m_scaleFactorItem(new LabelMenuItem(this, tr("Scale Factor"))),
    m_sumGainItem(new SpinMenuItem(this, tr("Sum Gain"), "dB")),
    m_pointQtyItem(new ComboMenuItem(this, tr("Point Qty."))),
    m_userDefItem(new SpinMenuItem(this, tr("User Def.")))
{
    ui->layout0->addWidget(m_eightPercentItem);
    ui->layout1->addWidget(m_dbRefItem);
    ui->layout2->addWidget(m_sumGainItem);
    ui->layout3->addWidget(m_scaleFactorItem);
    ui->layout4->addWidget(m_pointQtyItem);
    ui->layout5->addWidget(m_userDefItem);

    connect(m_eightPercentItem,
            SIGNAL(clicked()),
            this,
            SLOT(do_eightPercentItem_clicked()));

    m_dbRefItem->set(s_onOff);
    connect(m_dbRefItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_dbRefItem_changed(int)));

    m_pointQtyItem->add_item(tr("Auto"));
    m_pointQtyItem->add_item("160");
    m_pointQtyItem->add_item("320");
    m_pointQtyItem->add_item("640");
    m_pointQtyItem->add_item(tr("User Def."));
    connect(m_pointQtyItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_pointQtyItem(int)));

    m_sumGainItem->set(0, 100, 1);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void UtAdvancedMenu::update(const DplDevice::GroupPointer &group)
{
    if (!m_sample.isNull()) {
        /* disconnect */
        disconnect(static_cast<DplUt::Sample *>(m_sample.data()),
                   SIGNAL(scale_factor_changed(int)),
                   this,
                   SLOT(update_scaleFactorItem()));
    }

    m_sample = group->sample();

    connect(static_cast<DplUt::Sample *>(m_sample.data()),
            SIGNAL(scale_factor_changed(int)),
            this, SLOT(update_scaleFactorItem()));

    update_scaleFactorItem();
}

void UtAdvancedMenu::update_scaleFactorItem()
{
    m_scaleFactorItem->set_text(QString::number(m_sample->scale_factor()));
}

void UtAdvancedMenu::do_eightPercentItem_clicked()
{

}

void UtAdvancedMenu::do_dbRefItem_changed(int index)
{

}

void UtAdvancedMenu::do_pointQtyItem(int index)
{
    if (4 == index) {
        m_userDefItem->setFocus();
    } else {
        m_sample->set_point_qty(160*index, !index);
    }
}

}
