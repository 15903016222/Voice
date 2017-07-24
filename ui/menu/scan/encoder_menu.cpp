#include "encoder_menu.h"
#include "ui_base_menu.h"

namespace DplScanMenu {

EncoderMenu::EncoderMenu(QWidget *parent) :
    BaseMenu(parent),
    m_encoderItem(new ComboMenuItem(this, tr("Encoder"))),
    m_encoderTypeItem(new ComboMenuItem(this, tr("Type"))),
    m_resolutionItem(new SpinMenuItem(this, tr("Resolution"), tr("Step/mm"))),
    m_polarityItem(new ComboMenuItem(this, tr("Polarity"))),
    m_originItem(new SpinMenuItem(this, tr("Origin"), tr("mm"))),
    m_presetItem(new LabelMenuItem(this, tr("Preset")))
{
    ui->layout0->addWidget(m_encoderItem);
    ui->layout1->addWidget(m_encoderTypeItem);
    ui->layout2->addWidget(m_resolutionItem);
    ui->layout3->addWidget(m_polarityItem);
    ui->layout4->addWidget(m_originItem);
    ui->layout5->addWidget(m_presetItem);

    /* Encoder Menu Item */
    QStringList encoderList;
    encoderList.append(tr("Encoder 1"));
    encoderList.append(tr("Encoder 2"));
    m_encoderItem->set(encoderList);

    /* Encoder Type menu item */
    QStringList encoderTypeList;
    encoderTypeList.append(tr("Up"));
    encoderTypeList.append(tr("Down"));
    encoderTypeList.append(tr("Quad"));
    m_encoderTypeItem->set(encoderTypeList);

    /* Resolution menu item */
    m_resolutionItem->set(0.01, 10000, 2);

    /* Polarity Menu Item */
    QStringList polarityList;
    polarityList.append(tr("Normal"));
    polarityList.append(tr("Reverse"));
    m_polarityItem->set(polarityList);

    /* Origin Menu Item */
    m_originItem->set(0, 1000, 2);
}

EncoderMenu::~EncoderMenu()
{
}

}
