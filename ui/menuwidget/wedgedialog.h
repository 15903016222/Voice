#ifndef WEDGEDIALOG_H
#define WEDGEDIALOG_H

#include <QDialog>

namespace Ui {
class WedgeDialog;
}

class WedgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WedgeDialog(QWidget *parent = 0);
    ~WedgeDialog();

private:
    Ui::WedgeDialog *ui;
};

#endif // WEDGEDIALOG_H
