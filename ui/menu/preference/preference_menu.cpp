/**
 * @file preference_menu.cpp
 * @brief Preference Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "preference_menu.h"

#include <device/device.h>
#include <QDebug>
#include <QSettings>
#include <QTranslator>
#include <ui/menu/preference/translator.h>

namespace DplPreferenceMenu {

PreferenceMenu::PreferenceMenu(QWidget *parent) :
    BaseMenu(parent),
    m_brightItem(new SpinMenuItem(this, tr("Bright"), "%")),
    m_opacityItem(new SpinMenuItem(this, tr("Opacity"), "%")),
    m_languageItem(new ComboMenuItem(this, tr("Language"))),
    m_startingPageItem(new ComboMenuItem(this, tr("Starting Page"))),
    m_gatemodeItem(new ComboMenuItem(this, tr("Gate Mode"))),
    m_deployItem(new LabelMenuItem(this, tr("Deploy")))
{
    m_layout0->addWidget(m_brightItem);
    m_layout1->addWidget(m_opacityItem);
    m_layout2->addWidget(m_languageItem);
    m_layout3->addWidget(m_startingPageItem);
    m_layout4->addWidget(m_gatemodeItem);
    m_layout5->addWidget(m_deployItem);

    m_mcu = Mcu::instance();

    /* Bright menu item */
    m_brightItem->set(1, 100, 0);
    connect(m_brightItem, SIGNAL(value_changed(double)),
            this, SLOT(set_brightness(double)));
    m_brightItem->set_value(100);

    /* Opacity menu item */
    m_opacityItem->set(20, 100, 0);
    m_opacityItem->set_value(85);
    connect(m_opacityItem, SIGNAL(value_changed(double)),
            this, SIGNAL(opacity_changed(double)));

    /* Language menu item */
    m_languageItem->add_item(tr("English"));
    m_languageItem->add_item(tr("Chinese"));

    connect(m_languageItem, SIGNAL(value_changed(int)), DplTranslator::Translator::instance(), SLOT(do_value_changed(int)));

    /* Starting Page Menu Item */
    m_startingPageItem->set(s_onOff);

    /* Gate Mode */
    m_gatemodeItem->set(s_onOff);

    connect(m_gatemodeItem, SIGNAL(value_changed(int)), this, SLOT(do_gatemodeItem_value_changed(int)));

    /* Deploy */
    connect(m_deployItem,
            SIGNAL(clicked()),
            this, SLOT(do_deployItem_changed()));
}

PreferenceMenu::~PreferenceMenu()
{
}

void PreferenceMenu::set_brightness(double value)
{
    m_mcu->set_brightness((char)value);
}

void PreferenceMenu::do_deployItem_changed()
{
    DplDevice::Device::instance()->deploy();
}

void PreferenceMenu::do_gatemodeItem_value_changed(int val)
{
    bool flag = true;
    if(val) {
        flag = false;
    }

    const QVector<DplDevice::GroupPointer>  &groupVect = DplDevice::Device::instance()->groups();
    DplDevice::GroupPointer groupPointer;
    DplGate::GatePointer gateA;
    DplGate::GatePointer gateB;
    DplGate::GatePointer gateI;
    for(int i = 0; i < groupVect.size(); ++i) {
        groupPointer = groupVect.at(i);
        if(groupPointer.isNull()) {
            continue;
        }

        gateA = groupPointer->gate_a();
        gateB = groupPointer->gate_b();
        gateI = groupPointer->gate_i();

        gateA->set_visible(flag);
        gateB->set_visible(flag);
        gateI->set_visible(flag);
    }
}

void PreferenceMenu::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange) {
        retranslate_ui();
        return;
    }
    BaseMenu::changeEvent(event);
}

void PreferenceMenu::retranslate_ui()
{
    m_brightItem->set_title(tr("Bright"));
    m_opacityItem->set_title(tr("Opacity"));
    m_languageItem->set_title(tr("Language"));
    m_startingPageItem->set_title(tr("Starting Page"));
    m_gatemodeItem->set_title(tr("Gate Mode"));
    m_deployItem->set_title(tr("Deploy"));

    QStringList list;
    list << tr("English") << tr("Chinese");
    m_languageItem->retranslate_items(list);

    s_onOff.clear();
    s_onOff << tr("On") << tr("Off");
    m_startingPageItem->retranslate_items(s_onOff);
    m_gatemodeItem->retranslate_items(s_onOff);
}

}
