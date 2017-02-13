/**
 * @file output_menu.cpp
 * @brief Gate/Curves ouput menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "output_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"
#include "label_menu_item.h"

namespace DplGateCurvesMenu {

OutputMenu::OutputMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    QStringList outputList;
    QStringList soundList;
    QStringList dataList;

    outputList.append(tr("Alarm 1"));
    outputList.append(tr("Alarm 2"));
    outputList.append(tr("Alarm 3"));
    outputList.append(tr("Analog 1"));
    outputList.append(tr("Analog 2"));

    soundList.append(tr("Off No Sound"));
    soundList.append(tr("300Hz Audio Output at 300Hz"));
    soundList.append(tr("600Hz Audio Output at 600Hz"));
    soundList.append(tr("1000Hz Audio Output at 1000Hz"));
    soundList.append(tr("5000Hz Audio Output at 5000Hz"));

    dataList.append(tr("A%"));
    dataList.append(tr("B%"));
    dataList.append(tr("None"));

    m_outputItem = new ComboMenuItem;
    m_soundItem = new ComboMenuItem;
    m_delayItem = new SpinMenuItem;
    m_holdTimeItem = new SpinMenuItem;
    m_groupItem = new LabelMenuItem;
    m_dataItem = new ComboMenuItem;

    m_outputItem->set(tr("Output"), outputList);

    m_soundItem->set(tr("Sound"), soundList);
    m_soundItem->set_dispay_mode(ComboMenuItem::PREFIX);

    m_delayItem->set(tr("Delay"), "mm", 0, 5000, 2);
    m_holdTimeItem->set(tr("Hold Time"), "%", 0, 5000, 2);
    m_groupItem->set(tr("Group"), "");
    m_dataItem->set(tr("Data"), dataList);
}

OutputMenu::~OutputMenu()
{
    delete m_outputItem;
    delete m_soundItem;
    delete m_delayItem;
    delete m_holdTimeItem;
    delete m_groupItem;
    delete m_dataItem;
}

void OutputMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_outputItem);
    ui->menuItem1->layout()->addWidget(m_soundItem);
    ui->menuItem2->layout()->addWidget(m_delayItem);
    ui->menuItem3->layout()->addWidget(m_holdTimeItem);
    ui->menuItem4->layout()->addWidget(m_groupItem);
    ui->menuItem5->layout()->addWidget(m_dataItem);
    m_outputItem->show();
    m_soundItem->show();
    m_delayItem->show();
    m_holdTimeItem->show();
    m_groupItem->show();
    m_dataItem->show();
}

void OutputMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_outputItem);
    ui->menuItem1->layout()->removeWidget(m_soundItem);
    ui->menuItem2->layout()->removeWidget(m_delayItem);
    ui->menuItem3->layout()->removeWidget(m_holdTimeItem);
    ui->menuItem4->layout()->removeWidget(m_groupItem);
    ui->menuItem5->layout()->removeWidget(m_dataItem);
    m_outputItem->hide();
    m_soundItem->hide();
    m_delayItem->hide();
    m_holdTimeItem->hide();
    m_groupItem->hide();
    m_dataItem->hide();
}

}
