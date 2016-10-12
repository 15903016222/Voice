#ifndef CLOCKSETDIALOG_H
#define CLOCKSETDIALOG_H

#include <QDialog>

namespace Ui {
class ClockSetDialog;
}

class ClockSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClockSetDialog(QWidget *parent = 0);
    ~ClockSetDialog();

private:
    Ui::ClockSetDialog *ui;

public:

private:
    void init_ui();

signals:

public slots:

};

#endif // CLOCKSETDIALOG_H
