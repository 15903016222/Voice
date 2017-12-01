#include "save_mode_menu.h"

#include "inputpanelcontext.h"

namespace DplFileReportMenu {

SaveModeMenu::SaveModeMenu(QWidget *parent) :
    BaseMenu(parent),
    m_storageItem(new ComboMenuItem(this, tr("Storage"))),
    m_saveModeItem(new ComboMenuItem(this, tr("Save Mode"))),
    m_saveDataItem(new LabelMenuItem(this, tr("Save Data"))),
    m_fileNameItem(new LabelMenuItem(this, tr("File Name")))
{
    m_layout0->addWidget(m_storageItem);
    m_layout1->addWidget(m_saveModeItem);
    m_layout2->addWidget(m_saveDataItem);
    m_layout3->addWidget(m_fileNameItem);

    /* Storage Menu Item */   
    QStringList storageList;
    storageList.append(tr("SD"));
    storageList.append(tr("SSD"));
    storageList.append(tr("U Storage"));
    m_storageItem->set(storageList);

    /* Save Mode menu item */
    QStringList saveModeList;
    saveModeList.append(tr("Inspection Data"));
    saveModeList.append(tr("Inspection Table"));
    saveModeList.append(tr("Screen"));
    saveModeList.append(tr("Report"));
    m_saveModeItem->set(saveModeList);

    connect(m_fileNameItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
}

SaveModeMenu::~SaveModeMenu()
{
}

void SaveModeMenu::show_input_dialog()
{
    InputPanelContext *inputPanel = new InputPanelContext;
    LabelMenuItem *menu = qobject_cast<LabelMenuItem*>(sender());
    QString text = menu->text();

    inputPanel->set_item_current_text(text);
    if (inputPanel->exec() == InputPanelContext::Accepted) {
        menu->set_text(inputPanel->get_text());
    } else {
        menu->set_text(text);
    }
    delete inputPanel;
}

}
