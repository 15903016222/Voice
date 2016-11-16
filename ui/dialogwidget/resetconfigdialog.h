#ifndef RESETCONFIGDIALOG_H
#define RESETCONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ResetConfigDialog;
}

class ResetConfigDialog : public QDialog
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
