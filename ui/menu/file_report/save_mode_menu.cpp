#include "save_mode_menu.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"
#include "inputpanelcontext.h"

namespace DplFileReportMenu {

SaveModeMenu::SaveModeMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Storage Menu Item */
    m_storageItem = new ComboMenuItem;
    QStringList storageList;
    storageList.append(tr("SD"));
    storageList.append(tr("SSD"));
    storageList.append(tr("U Storage"));
    m_storageItem->set(tr("Storage"), storageList);

    /* Save Mode menu item */
    m_saveModeItem = new ComboMenuItem;
    QStringList saveModeList;
    saveModeList.append(tr("Inspection Data"));
    saveModeList.append(tr("Inspection Table"));
    saveModeList.append(tr("Screen"));
    saveModeList.append(tr("Report"));
    m_saveModeItem->set(tr("Save Mode"), saveModeList);

    /* Save Data menu item */
    m_saveDataItem = new LabelMenuItem;
    m_saveDataItem->set(tr("Save Data"), "");

    /* File Name menu item */
    m_fileName = new LabelMenuItem;
    m_fileName->set(tr("File Name"), "");
    connect(m_fileName, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
}

SaveModeMenu::~SaveModeMenu()
{
    delete m_storageItem;
    delete m_saveModeItem;
    delete m_saveDataItem;
    delete m_fileName;
}

void SaveModeMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_storageItem);
    ui->menuItem1->layout()->addWidget(m_saveModeItem);
    ui->menuItem2->layout()->addWidget(m_saveDataItem);
    ui->menuItem3->layout()->addWidget(m_fileName);
    m_storageItem->show();
    m_saveModeItem->show();
    m_saveDataItem->show();
    m_fileName->show();
}

void SaveModeMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_storageItem);
    ui->menuItem1->layout()->removeWidget(m_saveModeItem);
    ui->menuItem2->layout()->removeWidget(m_saveDataItem);
    ui->menuItem3->layout()->removeWidget(m_fileName);
    m_storageItem->hide();
    m_saveModeItem->hide();
    m_saveDataItem->hide();
    m_fileName->hide();
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
