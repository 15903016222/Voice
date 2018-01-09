/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "ut_advanced_menu.h"


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
    m_layout0->addWidget(m_eightPercentItem);
    m_layout1->addWidget(m_dbRefItem);
    m_layout2->addWidget(m_sumGainItem);
    m_layout3->addWidget(m_scaleFactorItem);
    m_layout4->addWidget(m_pointQtyItem);
    m_layout5->addWidget(m_userDefItem);
    m_userDefItem->hide();

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
    switch (index) {
    case 0:
        m_sample->set_point_qty(0, true);
        break;
    case 1:
        m_sample->set_point_qty(160);
        break;
    case 2:
        m_sample->set_point_qty(320);
        break;
    case 3:
        m_sample->set_point_qty(640);
        break;
    case 4:
        m_userDefItem->show();
    default:
        break;
    }
}

void UtAdvancedMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_eightPercentItem->set_title(tr("Set 80%"));
        m_dbRefItem->set_title(tr("dB Ref."));
        m_scaleFactorItem->set_title(tr("Scale Factor"));
        m_sumGainItem->set_title(tr("Sum Gain"));
        m_pointQtyItem->set_title(tr("Point Qty."));
        m_userDefItem->set_title(tr("User Def."));
        return;
    }
    BaseMenu::changeEvent(e);
}

}
