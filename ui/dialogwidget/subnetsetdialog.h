#ifndef SUBNETSETDIALOG_H
#define SUBNETSETDIALOG_H

#include <QDialog>

namespace Ui {
class SubNetSetDialog;
}

class SubNetSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubNetSetDialog(QWidget *parent = 0);
    ~SubNetSetDialog();

private:
    Ui::SubNetSetDialog *ui;

public:
    QString str_subNet;

private:

signals:
    void currentSubNetChanged(QString subNet);

public slots:
    void on_buttonBox_accepted();

};

#endif // SUBNETSETDIALOG_H
