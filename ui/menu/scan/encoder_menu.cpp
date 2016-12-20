#include "encoder_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"
#include "label_menu_item.h"

namespace DplScanMenu {

EncoderMenu::EncoderMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Encoder Menu Item */
    m_encoderItem = new ComboMenuItem;
    QStringList encoderList;
    encoderList.append(tr("Encoder 1"));
    encoderList.append(tr("Encoder 2"));
    m_encoderItem->set(tr("Encoder"), encoderList);

    /* Encoder Type menu item */
    m_encoderTypeItem = new ComboMenuItem;
    QStringList encoderTypeList;
    encoderTypeList.append(tr("Up"));
    encoderTypeList.append(tr("Down"));
    encoderTypeList.append(tr("Quad"));
    m_encoderTypeItem->set(tr("Encoder Type"), encoderTypeList);

    /* Resolution menu item */
    m_resolutionItem = new SpinMenuItem;
    m_resolutionItem->set(tr("Resolution"), "Step/mm", 0.01, 10000, 2);

    /* Polarity Menu Item */
    m_polarityItem = new ComboMenuItem;
    QStringList polarityList;
    polarityList.append(tr("Normal"));
    polarityList.append(tr("Reverse"));
    m_polarityItem->set(tr("Polarity"), polarityList);

    /* Origin Menu Item */
    m_originItem = new SpinMenuItem;
    m_originItem->set(tr("Origin"), "mm", 0, 1000, 2);

    /* Preset Menu Item */
    m_presetItem = new LabelMenuItem;
    m_presetItem->set(tr("Preset"), "");
}

EncoderMenu::~EncoderMenu()
{
    delete m_encoderItem;
    delete m_encoderTypeItem;
    delete m_resolutionItem;
    delete m_polarityItem;
    delete m_originItem;
    delete m_presetItem;
}

void EncoderMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_encoderItem);
    ui->menuItem1->layout()->addWidget(m_encoderTypeItem);
    ui->menuItem2->layout()->addWidget(m_resolutionItem);
    ui->menuItem3->layout()->addWidget(m_polarityItem);
    ui->menuItem4->layout()->addWidget(m_originItem);
    ui->menuItem5->layout()->addWidget(m_presetItem);
    m_encoderItem->show();
    m_encoderTypeItem->show();
    m_resolutionItem->show();
    m_polarityItem->show();
    m_originItem->show();
    m_presetItem->show();
}

void EncoderMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_encoderItem);
    ui->menuItem1->layout()->removeWidget(m_encoderTypeItem);
    ui->menuItem2->layout()->removeWidget(m_resolutionItem);
    ui->menuItem3->layout()->removeWidget(m_polarityItem);
    ui->menuItem4->layout()->removeWidget(m_originItem);
    ui->menuItem5->layout()->removeWidget(m_presetItem);
    m_encoderItem->hide();
    m_encoderTypeItem->hide();
    m_resolutionItem->hide();
    m_polarityItem->hide();
    m_originItem->hide();
    m_presetItem->hide();
}

}
