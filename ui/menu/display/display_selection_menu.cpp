/**
 * @file selection_menu.cpp
 * @brief selection menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "display_selection_menu.h"
#include "display_select_dialog.h"


#include <ui/display/test_stub.h>

namespace DplDisplayMenu {

SelectionMenu::SelectionMenu(QWidget *parent) :
    BaseMenu(parent),
    m_displayItem(new LabelMenuItem(this, tr("Display"), "A")),
    m_cSourceItem(new ComboMenuItem(this, tr("C Scan\nSource"))),
    m_thicknessSourceItem(new ComboMenuItem(this, tr("Thickness\nSource"))),
    m_minThicknessItem(new SpinMenuItem(this, tr("Min.Thickness"), "mm")),
    m_maxThicknessItem(new SpinMenuItem(this, tr("Max.Thickness"), "mm")),
    m_dataCompressionItem(new ComboMenuItem(this, tr("Data\nCompression")))
{
    m_layout0->addWidget(m_displayItem);
    m_layout1->addWidget(m_cSourceItem);
    m_layout2->addWidget(m_thicknessSourceItem);
    m_layout3->addWidget(m_minThicknessItem);
    m_layout4->addWidget(m_maxThicknessItem);
    m_layout5->addWidget(m_dataCompressionItem);

    QStringList cScanSourceList;

    cScanSourceList.append(tr("A%"));
    cScanSourceList.append(tr("B%"));
    cScanSourceList.append(tr("Thickness"));
    cScanSourceList.append(tr("I/"));

    QStringList thicknessSourceList;

    thicknessSourceList << tr("A^") << tr("A^-I^") << tr("A^-I/")
                      << tr("B^") << tr("B^-I^") << tr("B^-I/")
                      << tr("B^-A^") << tr("I^") << tr("I/");


    /* Display menu item */
    connect(m_displayItem, SIGNAL(clicked()),
            this, SLOT(do_displayItem_clicked()));
    connect(m_cSourceItem, SIGNAL(value_changed(int)),
            this, SLOT(do_cSourceItem_changed(int)));
    connect(m_thicknessSourceItem, SIGNAL(value_changed(int)),
            this, SLOT(do_thicknessSourceItem_changed(int)));
    connect(m_minThicknessItem, SIGNAL(value_changed(double)),
            this, SLOT(do_minThickness_value_changed(double)));
    connect(m_maxThicknessItem, SIGNAL(value_changed(double)),
            this, SLOT(do_maxThickness_value_changed(double)));

    connect(Mcu::instance(), SIGNAL(key_event(Mcu::KeyType)),
            this, SLOT(do_mcu_key_event(Mcu::KeyType)),
            Qt::DirectConnection);

    /* C-Scan Source menu item */
    m_cSourceItem->set(cScanSourceList);

    /* Thickness Type menu item */
    m_thicknessSourceItem->set(thicknessSourceList);

    /* Min.Thickness menu item */
    m_minThicknessItem->set(0.05, 20000, 2);

    /* Max.Thickness menu item */
    m_maxThicknessItem->set(0.06, 20000, 2);

    /* Data compression */
    m_dataCompressionItem->set(s_onOff);
}

SelectionMenu::~SelectionMenu()
{
}

void SelectionMenu::do_displayItem_clicked()
{
    DisplaySelectDialog dialog;
    dialog.exec();
}

void SelectionMenu::do_cSourceItem_changed(int index)
{
    TestStub::instance()->set_source(static_cast<TestStub::C_SCAN_SOURCE> (index));
}

void SelectionMenu::do_thicknessSourceItem_changed(int index)
{
    TestStub::instance()->set_thickness_source(static_cast<TestStub::THICKNESS_SOURCE> (index));
}

void SelectionMenu::do_minThickness_value_changed(double value)
{
    TestStub::instance()->set_min_thickness(value);
}

void SelectionMenu::do_maxThickness_value_changed(double value)
{
    TestStub::instance()->set_max_thickness(value);
}

void SelectionMenu::do_mcu_key_event(Mcu::KeyType type)
{
    if (type == Mcu::KEY_DISPLAY) {
        do_displayItem_clicked();
    }
}

void SelectionMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        m_displayItem->set_title(tr("Display"));
        m_cSourceItem->set_title(tr("C Scan\nSource"));
        m_thicknessSourceItem->set_title(tr("Thickness\nSource"));
        m_minThicknessItem->set_title(tr("Min.Thickness"));
        m_maxThicknessItem->set_title(tr("Max.Thickness"));
        m_dataCompressionItem->set_title(tr("Data\nCompression"));
        return;
    }
    BaseMenu::changeEvent(e);
}

}
