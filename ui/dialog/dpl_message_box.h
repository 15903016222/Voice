#ifndef __DPL_MESSAGE_BOX_H__
#define __DPL_MESSAGE_BOX_H__

#include <QDialog>
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class DplMessageBox;
}

class DplMessageBox : public QDialog
{
    Q_OBJECT

public:
    DplMessageBox(QMessageBox::Icon icon,
                  const QString &title,
                  const QString &info,
                  QWidget *parent = 0);

    ~DplMessageBox();

protected:
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);


private slots:
    void do_timer_timeout();
    void on_okPushButton_clicked();
    void on_cancelPushButton_clicked();

private:
    Ui::DplMessageBox   *ui;
    QTimer              *m_timer;
    QMessageBox::Icon   m_icon;

    void set_icon();

};

#endif // __DPL_MESSAGE_BOX_H__
