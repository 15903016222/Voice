/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "ut_advanced_menu.h"
#include <QDebug>

namespace DplUtSettingMenu {

UtAdvancedMenu::UtAdvancedMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    DplDevice::Device *device = DplDevice::Device::instance();

    connect(device, SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));

    m_sample = DplDevice::Device::instance()->current_group()->sample();


    QStringList pointQtyList;

    pointQtyList.append(tr("Auto"));
    pointQtyList.append(tr("160"));
    pointQtyList.append(tr("320"));
    pointQtyList.append(tr("640"));
    pointQtyList.append(tr("UserDef"));

    m_eightPercentItem.set(tr("Set 80%"), "");

    m_dbRefItem.set(tr("dB Ref."), s_onOff);

    m_pointQtyItem.set(tr("Point Qty."), pointQtyList);

    m_scaleFactorItem.set(tr("Scale Factor"), "");
    connect(static_cast<DplUt::Sample *>(m_sample.data()),
            SIGNAL(scale_factor_changed(int)),
            this,
            SLOT(update_scale_factor_item()));

    m_sumGainItem.set(tr("Sum Gain"), "dB", 0, 100, 1);

    m_updateFlag = true;
}

UtAdvancedMenu::~UtAdvancedMenu()
{
}

void UtAdvancedMenu::show()
{
    if (m_updateFlag) {
        update();
    }
    ui->layout0->addWidget(&m_eightPercentItem);
    ui->layout1->addWidget(&m_dbRefItem);
    ui->layout2->addWidget(&m_pointQtyItem);
    ui->layout3->addWidget(&m_scaleFactorItem);
    ui->layout4->addWidget(&m_sumGainItem);
    m_eightPercentItem.show();
    m_dbRefItem.show();
    m_pointQtyItem.show();
    m_scaleFactorItem.show();
    m_sumGainItem.show();
}

void UtAdvancedMenu::hide()
{
    ui->layout0->removeWidget(&m_eightPercentItem);
    ui->layout1->removeWidget(&m_dbRefItem);
    ui->layout2->removeWidget(&m_pointQtyItem);
    ui->layout3->removeWidget(&m_scaleFactorItem);
    ui->layout4->removeWidget(&m_sumGainItem);
    m_eightPercentItem.hide();
    m_dbRefItem.hide();
    m_pointQtyItem.hide();
    m_scaleFactorItem.hide();
    m_sumGainItem.hide();
}

void UtAdvancedMenu::update()
{
    update_scale_factor_item();
    m_updateFlag = false;
}

void UtAdvancedMenu::do_current_group_changed(const DplDevice::GroupPointer &group)
{
    /* disconnect */
    disconnect(static_cast<DplUt::Sample *>(m_sample.data()),
               SIGNAL(scale_factor_changed(int)),
               this,
               SLOT(update_scale_factor_item()));

    m_sample = group->sample();
    connect(static_cast<DplUt::Sample *>(m_sample.data()),
            SIGNAL(scale_factor_changed(int)),
            this, SLOT(update_scale_factor_item()));

    if (m_eightPercentItem.isHidden()) {
        m_updateFlag = true;
    } else {
        update();
    }
}

void UtAdvancedMenu::update_scale_factor_item()
{
    m_scaleFactorItem.set_text(QString::number(m_sample->scale_factor()));
}

}
