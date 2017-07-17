#include "encoder_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"
#include "label_menu_item.h"

namespace DplScanMenu {

EncoderMenu::EncoderMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Encoder Menu Item */
    QStringList encoderList;
    encoderList.append(tr("Encoder 1"));
    encoderList.append(tr("Encoder 2"));
    m_encoderItem.set(tr("Encoder"), encoderList);

    /* Encoder Type menu item */
    QStringList encoderTypeList;
    encoderTypeList.append(tr("Up"));
    encoderTypeList.append(tr("Down"));
    encoderTypeList.append(tr("Quad"));
    m_encoderTypeItem.set(tr("Encoder Type"), encoderTypeList);

    /* Resolution menu item */
    m_resolutionItem.set(tr("Resolution"), "Step/mm", 0.01, 10000, 2);

    /* Polarity Menu Item */
    QStringList polarityList;
    polarityList.append(tr("Normal"));
    polarityList.append(tr("Reverse"));
    m_polarityItem.set(tr("Polarity"), polarityList);

    /* Origin Menu Item */
    m_originItem.set(tr("Origin"), "mm", 0, 1000, 2);

    /* Preset Menu Item */
    m_presetItem.set(tr("Preset"), "");
}

EncoderMenu::~EncoderMenu()
{
}

void EncoderMenu::show()
{
    ui->layout0->addWidget(&m_encoderItem);
    ui->layout1->addWidget(&m_encoderTypeItem);
    ui->layout2->addWidget(&m_resolutionItem);
    ui->layout3->addWidget(&m_polarityItem);
    ui->layout4->addWidget(&m_originItem);
    ui->layout5->addWidget(&m_presetItem);
    m_encoderItem.show();
    m_encoderTypeItem.show();
    m_resolutionItem.show();
    m_polarityItem.show();
    m_originItem.show();
    m_presetItem.show();
}

void EncoderMenu::hide()
{
    ui->layout0->removeWidget(&m_encoderItem);
    ui->layout1->removeWidget(&m_encoderTypeItem);
    ui->layout2->removeWidget(&m_resolutionItem);
    ui->layout3->removeWidget(&m_polarityItem);
    ui->layout4->removeWidget(&m_originItem);
    ui->layout5->removeWidget(&m_presetItem);
    m_encoderItem.hide();
    m_encoderTypeItem.hide();
    m_resolutionItem.hide();
    m_polarityItem.hide();
    m_originItem.hide();
    m_presetItem.hide();
}

}
