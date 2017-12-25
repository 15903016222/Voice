#include "report_menu.h"

#include "inputpanelcontext.h"
#include <ui/dialog/dpl_message_box.h>
#include <report/report.h>
#include "report_applier.h"
#include <QDir>
#include "report_preview_dialog.h"

namespace DplFileReportMenu {

static const QString s_templateFilePath = "/opt/mercury/template/report/";
static const QString s_html = ".html";

ReportMenu::ReportMenu(QWidget *parent) :
    BaseMenu(parent),
    m_templateItem(new ComboMenuItem(this, tr("Template"))),
    m_reportNameItem(new LabelMenuItem(this, tr("Report Name"))),
    m_customerItem(new LabelMenuItem(this, tr("Customer"))),
    m_partNameItem(new LabelMenuItem(this, tr("Part Name"))),
    m_partNumberItem(new LabelMenuItem(this, tr("Part Number"))),
    m_previewItem(new LabelMenuItem(this, tr("Preview")))
{   
    m_layout0->addWidget(m_templateItem);
    m_layout1->addWidget(m_reportNameItem);
    m_layout2->addWidget(m_customerItem);
    m_layout3->addWidget(m_partNameItem);
    m_layout4->addWidget(m_partNumberItem);
    m_layout5->addWidget(m_previewItem);

    QDir dir(s_templateFilePath);
    QStringList stringList = dir.entryList(QStringList("*.html"));
    m_templateItem->add_items(stringList);

    /* Report Name menu item */
    connect(m_reportNameItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Customer menu item */
    connect(m_customerItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Part Name Menu Item */
    connect(m_partNameItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Part Number item */
    connect(m_partNumberItem, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

    /* Preview Item */
    connect(m_previewItem, SIGNAL(clicked()), this, SLOT(do_createItem_clicked()));

}

ReportMenu::~ReportMenu()
{
}

void ReportMenu::show_input_dialog()
{
    InputPanelContext inputPanel;
    LabelMenuItem *menu = qobject_cast<LabelMenuItem*>(sender());
    QString text = menu->text();

    inputPanel.set_item_current_text(text);
    if (inputPanel.exec() == InputPanelContext::Accepted) {
        menu->set_text(inputPanel.get_text());
    } else {
        menu->set_text(text);
    }
}

void ReportMenu::do_createItem_clicked()
{
    if(m_reportNameItem->text().isEmpty()) {
        DplMessageBox messageBox(QMessageBox::Warning, tr("Warning"), tr("Report Name Is Empty!"));
        messageBox.exec();
        return;
    }

    DplReport::Report report;
    report.set_template_file(s_templateFilePath + m_templateItem->current_text());

    ReportApplier *reportApplier = new ReportApplier(report, this);
    reportApplier->fill(s_templateFilePath + m_templateItem->current_text());

    if(report.save(m_reportNameItem->text() + s_html)) {
        ReportPreviewDialog preview(m_reportNameItem->text() + s_html);
        if(preview.preview()) {
            preview.exec();
        }
    } else {
        DplMessageBox messageBox(QMessageBox::Warning, tr("Warning"), tr("Create Preview Failed!"));
        messageBox.exec();
    }
    delete reportApplier;
    reportApplier = NULL;
}

}
