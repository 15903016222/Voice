#ifndef SYSTEMINFODIALOG_H
#define SYSTEMINFODIALOG_H

#include <QDialog>

namespace Ui {
namespace Dialog {

class SysInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SysInfoDialog(QWidget *parent = 0);
};

}   // namespace Dialog
}   // namespace Ui
#endif // SYSTEMINFODIALOG_H
