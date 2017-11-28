#ifndef SYSTEMINFODIALOG_H
#define SYSTEMINFODIALOG_H

#include <QDialog>

#include <ui/dialog/base_dialog.h>

//namespace Ui {
//namespace Dialog {

class SysInfoDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit SysInfoDialog(QWidget *parent = 0);
};

//}   // namespace Dialog
//}   // namespace Ui
#endif // SYSTEMINFODIALOG_H
