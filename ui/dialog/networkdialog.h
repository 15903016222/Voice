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
    void set_dialog_title(QString &string);
    void set_spinbox_value(QString &string);

    QString get_text();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::NetworkDialog *ui;
    QMap<QString, QString> m_titleMap;
    QString m_str;

    QList<int> get_value_list(QString &text, QString &str);  

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();
};

#endif // NETWORKDIALOG_H
