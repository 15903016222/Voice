#include "report_menu.h"

#include "inputpanelcontext.h"
#include <ui/dialog/dpl_message_box.h>
#include <report/report.h>
#include "report_applier.h"
#include <QDir>
#include <QTime>
#include "report_preview_dialog.h"

namespace DplFileReportMenu {

static const QString s_templateFilePath = "/opt/mercury/template/report/";
static const QString s_userRportFilePath = "/opt/mercury/usr/report/";
static const QString s_html = ".html";
static const QString s_tmpReportFile = "/tmp/report.tmp.html";

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

    m_reportNameItem->set_text(tr("Report"));

    set_template_items();

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

    QString dateTime = QDateTime::currentDateTime().toString("_yyyy-MM-dd_hh.mm.ss");

    DplReport::Report report;
    report.set_template_file(s_templateFilePath + m_templateItem->current_text() + s_html);

    ReportApplier reportApplier(report);
    reportApplier.fill(s_userRportFilePath + m_reportNameItem->text() + dateTime + s_html);
    ReportPreviewDialog preview(s_tmpReportFile);

    if(report.save(s_tmpReportFile) && preview.preview()) {

        if((preview.exec() == QMessageBox::Accepted)) {
            if(copy_file_to_target_path(s_tmpReportFile,
                                        s_userRportFilePath + m_reportNameItem->text() + dateTime + s_html)) {
                DplMessageBox messageBox(QMessageBox::Information, tr("Info"), tr("Create Success!"));
                messageBox.exec();
            }
        }

        return;
    }

    DplMessageBox messageBox(QMessageBox::Warning, tr("Warning"), tr("Create Preview Failed!"));
    messageBox.exec();
}

void ReportMenu::set_template_items()
{
    QDir dir(s_templateFilePath);
    QStringList stringList = dir.entryList(QStringList("*.html"));
    for(int i = 0; i < stringList.size(); ++i) {
        m_templateItem->add_item(stringList[i].remove(s_html));
    }
}

bool ReportMenu::copy_file_to_target_path(const QString &src, const QString &dest)
{
    QFile file(dest);
    if(file.exists()) {
        if(!file.remove()) {
            return false;
        }
    }

    if(QFile::copy(src, dest)) {
        return true;
    }

    return false;
}

}
