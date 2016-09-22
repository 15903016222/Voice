#ifndef PROBEDIALOG_H
#define PROBEDIALOG_H

#include <QDialog>

namespace Ui {
class ProbeDialog;
}

class ProbeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProbeDialog(QWidget *parent = 0);
    ~ProbeDialog();

private:
    Ui::ProbeDialog *ui;
};

#endif // PROBEDIALOG_H
