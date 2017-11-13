#ifndef RESETCONFIGDIALOG_H
#define RESETCONFIGDIALOG_H

#include <QDialog>
#include <ui/dialog/base_dialog.h>

namespace Ui {
class ResetConfigDialog;
}

class ResetConfigDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit ResetConfigDialog(QWidget *parent = 0);
    ~ResetConfigDialog();

    void retranslate_dialog_ui();

private:
    Ui::ResetConfigDialog *ui;

};

#endif // RESETCONFIGDIALOG_H
