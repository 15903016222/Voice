#include "save_mode_menu.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"
#include "inputpanelcontext.h"

namespace DplFileReportMenu {

SaveModeMenu::SaveModeMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Storage Menu Item */   
    QStringList storageList;
    storageList.append(tr("SD"));
    storageList.append(tr("SSD"));
    storageList.append(tr("U Storage"));
    m_storageItem.set(tr("Storage"), storageList);

    /* Save Mode menu item */
    QStringList saveModeList;
    saveModeList.append(tr("Inspection Data"));
    saveModeList.append(tr("Inspection Table"));
    saveModeList.append(tr("Screen"));
    saveModeList.append(tr("Report"));
    m_saveModeItem.set(tr("Save Mode"), saveModeList);

    /* Save Data menu item */
    m_saveDataItem.set(tr("Save Data"), "");

    /* File Name menu item */
    m_fileNameItem.set(tr("File Name"), "");
    connect(&m_fileNameItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
}

SaveModeMenu::~SaveModeMenu()
{
}

void SaveModeMenu::show()
{
    ui->layout0->addWidget(&m_storageItem);
    ui->layout1->addWidget(&m_saveModeItem);
    ui->layout2->addWidget(&m_saveDataItem);
    ui->layout3->addWidget(&m_fileNameItem);
    m_storageItem.show();
    m_saveModeItem.show();
    m_saveDataItem.show();
    m_fileNameItem.show();
}

void SaveModeMenu::hide()
{
    ui->layout0->removeWidget(&m_storageItem);
    ui->layout1->removeWidget(&m_saveModeItem);
    ui->layout2->removeWidget(&m_saveDataItem);
    ui->layout3->removeWidget(&m_fileNameItem);
    m_storageItem.hide();
    m_saveModeItem.hide();
    m_saveDataItem.hide();
    m_fileNameItem.hide();
}

void SaveModeMenu::show_input_dialog()
{
    InputPanelContext *inputPanel = new InputPanelContext;
    LabelMenuItem *menu = qobject_cast<LabelMenuItem*>(sender());
    QString text = menu->get_text();

    inputPanel->set_item_current_text(text);
    if (inputPanel->exec() == InputPanelContext::Accepted) {
        menu->set_text(inputPanel->get_text());
    } else {
        menu->set_text(text);
    }
    delete inputPanel;
}

}
