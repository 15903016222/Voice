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
    LabelMenuItem *m_templateItem;
    LabelMenuItem *m_reportNameItem;
    LabelMenuItem *m_customerItem;
    LabelMenuItem *m_partNameItem;
    LabelMenuItem *m_partNumberItem;
    LabelMenuItem *m_createItem;

private slots:
    void show_input_dialog();

protected:
    void changeEvent(QEvent *e);
};

}
#endif // __REPORT_MENU_H__
