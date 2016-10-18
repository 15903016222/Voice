#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class NetworkDialog;
}

class NetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkDialog(QWidget *parent = 0);
    ~NetworkDialog();

private:
    Ui::NetworkDialog *ui;

public:
    void retranslate_dialog_ui();
    QString str_ip;

private:
    void init_ui();

signals:
    void currentIPChanged(QString IP);

public slots:
    void on_buttonBox_accepted();
    void set_dialog_title(QMap<QString, QString> map);
    void set_spinbox_value(QList<int> valueList);

};

#endif // NETWORKDIALOG_H
