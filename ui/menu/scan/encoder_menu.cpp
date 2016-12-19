#include "encoder_menu.h"

namespace DplScanMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Label
};

EncoderMenu::EncoderMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Encoder Menu Item */
    QStringList encoderList;
    encoderList.append(tr("Encoder 1"));
    encoderList.append(tr("Encoder 2"));
    m_menuItem[0]->set(tr("Encoder"), encoderList);

    /* Encoder Type menu item */
    QStringList encoderTypeList;
    encoderTypeList.append(tr("Up"));
    encoderTypeList.append(tr("Down"));
    encoderTypeList.append(tr("Quad"));
    m_menuItem[1]->set(tr("Encoder Type"), encoderTypeList);

    /* Resolution menu item */
    m_menuItem[2]->set(tr("Resolution"), "Step/mm", 0.01, 10000, 2);

    /* Polarity Menu Item */
    QStringList polarityList;
    polarityList.append(tr("Normal"));
    polarityList.append(tr("Reverse"));
    m_menuItem[3]->set(tr("Polarity"), polarityList);

    /* Origin Menu Item */
    m_menuItem[4]->set(tr("Origin"), "mm", 0, 1000, 2);

    /* Preset Menu Item */
    m_menuItem[5]->set(tr("Preset"), "");
}

}
