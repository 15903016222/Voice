/**
 * @file output_menu.cpp
 * @brief Gate/Curves ouput menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "output_menu.h"

#include "ui_base_menu.h"

namespace DplGateCurvesMenu {

OutputMenu::OutputMenu(QWidget *parent) :
    BaseMenu(parent),
    m_outputItem(new ComboMenuItem(this, tr("Output"))),
    m_soundItem(new ComboMenuItem(this, tr("Sound"))),
    m_delayItem(new SpinMenuItem(this, tr("Delay"), "mm")),
    m_holdTimeItem(new SpinMenuItem(this, tr("Hold Time"), "%")),
    m_groupItem(new LabelMenuItem(this, tr("Group"))),
    m_dataItem(new ComboMenuItem(this, tr("Data")))
{
    ui->layout0->addWidget(m_outputItem);
    ui->layout1->addWidget(m_soundItem);
    ui->layout2->addWidget(m_delayItem);
    ui->layout3->addWidget(m_holdTimeItem);
    ui->layout4->addWidget(m_groupItem);
    ui->layout5->addWidget(m_dataItem);

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

    m_outputItem->set(outputList);

    m_soundItem->set(soundList);
    m_soundItem->set_dispay_mode(ComboMenuItem::PREFIX);

    m_delayItem->set(0, 5000, 2);
    m_holdTimeItem->set(0, 5000, 2);
    m_dataItem->set(dataList);
}

OutputMenu::~OutputMenu()
{
}

}
