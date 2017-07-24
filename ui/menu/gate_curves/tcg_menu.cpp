/**
 * @file tcg_menu.cpp
 * @brief Gate/Curves tcg menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "tcg_menu.h"

#include "ui_base_menu.h"

namespace DplGateCurvesMenu {

TcgMenu::TcgMenu(QWidget *parent) :
    BaseMenu(parent),
    m_modeItem(new ComboMenuItem(this, tr("Mode"))),
    m_curveNoItem(new SpinMenuItem(this, tr("Curve No."))),
    m_curveXItem(new ComboMenuItem(this, tr("Curve X"))),
    m_dbOffsetItem(new SpinMenuItem(this, tr("dB Offset"), tr("dB"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_pointItem(new ComboMenuItem(this, tr("Point"))),
    m_positionItem(new SpinMenuItem(this, tr("Position"))),
    m_gainItem(new SpinMenuItem(this, tr("Gain"), tr("dB"))),
    m_addPointItem(new LabelMenuItem(this, tr("Add Point"))),
    m_deletePointItem(new LabelMenuItem(this, tr("Delete Point")))
{
    ui->layout0->addWidget(m_modeItem);

    /* Setting */
    ui->layout1->addWidget(m_curveNoItem);
    ui->layout2->addWidget(m_curveXItem);
    ui->layout3->addWidget(m_dbOffsetItem);
    ui->layout4->addWidget(m_switchItem);

    /* Edit */
    ui->layout1->addWidget(m_pointItem);
    ui->layout2->addWidget(m_positionItem);
    ui->layout3->addWidget(m_gainItem);
    ui->layout4->addWidget(m_addPointItem);
    ui->layout5->addWidget(m_deletePointItem);

    QStringList modeList;
    QStringList curveXList;
    QStringList pointList;

    modeList.append(tr("Settings"));
    modeList.append(tr("Edit"));

    curveXList.append("1");
    curveXList.append("2");
    curveXList.append("3");
    curveXList.append("4");
    curveXList.append("5");

    pointList.append("1");
    pointList.append("2");

    m_modeItem->set(modeList);
    connect(m_modeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_modeItem_changed(int)));

    /* Setting */
    m_curveNoItem->set(1, 5, 0);
    m_curveXItem->set(curveXList);
    m_dbOffsetItem->set(-40, 40, 1);
    m_switchItem->set(s_onOff);

    /* Edit */
    m_pointItem->set(pointList);
    m_positionItem->set(0, 10000, 2);
    m_gainItem->set(0, 100, 1);

    do_modeItem_changed(0);
}

TcgMenu::~TcgMenu()
{
}

void TcgMenu::do_modeItem_changed(int pos)
{
    m_curveNoItem->setVisible(!pos);
    m_curveXItem->setVisible(!pos);
    m_dbOffsetItem->setVisible(!pos);
    m_switchItem->setVisible(!pos);

    m_pointItem->setVisible(!!pos);
    m_positionItem->setVisible(!!pos);
    m_gainItem->setVisible(!!pos);
    m_addPointItem->setVisible(!!pos);
    m_deletePointItem->setVisible(!!pos);
}

}
