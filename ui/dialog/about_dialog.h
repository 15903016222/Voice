#ifndef __ABOUT_DIALOG_H__
#define __ABOUT_DIALOG_H__

#include <QDialog>

namespace Ui {
namespace Dialog {

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);

    bool event(QEvent *event);

private slots:
};

} // namespace Dialog
} // namespace Ui
#endif // __ABOUT_DIALOG_H__
