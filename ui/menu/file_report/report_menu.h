#ifndef __REPORT_MENU_H__
#define __REPORT_MENU_H__

#include "../base_menu.h"

namespace DplFileReportMenu {

class ReportMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ReportMenu(QWidget *parent);
    ~ReportMenu();

private:

    ComboMenuItem *m_templateItem;
    LabelMenuItem *m_reportNameItem;
    LabelMenuItem *m_customerItem;
    LabelMenuItem *m_partNameItem;
    LabelMenuItem *m_partNumberItem;
    LabelMenuItem *m_previewItem;

private slots:
    void show_input_dialog();
    void do_createItem_clicked();

protected:
    void changeEvent(QEvent *e);

private:
    void set_template_items();
    bool copy_file_to_target_path(const QString &src, const QString &dest);
};

}
#endif // __REPORT_MENU_H__
