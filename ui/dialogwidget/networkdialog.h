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

    void retranslate_dialog_ui();
    void set_dialog_title(QMap<QString, QString> map);
    void set_spinbox_value(QList<int> valueList);

    QString str_ip;
    QString str_subNet;

private:
    Ui::NetworkDialog *ui;

    QMap<QString, QString> titleMap;

signals:
    void currentIP_subNetChanged(QString value);

public slots:
    void on_buttonBox_accepted();


};

#endif // NETWORKDIALOG_H
