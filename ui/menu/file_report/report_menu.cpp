#include "report_menu.h"
#include "label_menu_item.h"
#include "inputpanelcontext.h"

namespace DplFileReportMenu {

ReportMenu::ReportMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{   
    /* Template Menu Item */
    m_templateItem.set(tr("Template"), "");

    /* Report Name menu item */
    m_reportNameItem.set(tr("Report Name"), "");
    connect(&m_reportNameItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Customer menu item */
    m_customerItem.set(tr("Customer"), "");
    connect(&m_customerItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Part Name Menu Item */
    m_partNameItem.set(tr("Part Name"), "");
    connect(&m_partNameItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Part Number item */
    m_partNumberItem.set(tr("Part Number"), "");
    connect(&m_partNumberItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Create menu item */
    m_createItem.set(tr("Create"), "");
}

ReportMenu::~ReportMenu()
{
}

void ReportMenu::show()
{
    ui->layout0->addWidget(&m_templateItem);
    ui->layout1->addWidget(&m_reportNameItem);
    ui->layout2->addWidget(&m_customerItem);
    ui->layout3->addWidget(&m_partNameItem);
    ui->layout4->addWidget(&m_partNumberItem);
    ui->layout5->addWidget(&m_createItem);
    m_templateItem.show();
    m_reportNameItem.show();
    m_customerItem.show();
    m_partNameItem.show();
    m_partNumberItem.show();
    m_createItem.show();
}

void ReportMenu::hide()
{
    ui->layout0->removeWidget(&m_templateItem);
    ui->layout1->removeWidget(&m_reportNameItem);
    ui->layout2->removeWidget(&m_customerItem);
    ui->layout3->removeWidget(&m_partNameItem);
    ui->layout4->removeWidget(&m_partNumberItem);
    ui->layout5->removeWidget(&m_createItem);
    m_templateItem.hide();
    m_reportNameItem.hide();
    m_customerItem.hide();
    m_partNameItem.hide();
    m_partNumberItem.hide();
    m_createItem.hide();
}

void ReportMenu::show_input_dialog()
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
