#ifndef SHOWINFOWIDGET_H
#define SHOWINFOWIDGET_H

#include "timesetdialog.h"

#include <QWidget>

namespace Ui {
class ShowInfoWidget;
}

class ShowInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShowInfoWidget(QWidget *parent = 0);
    ~ShowInfoWidget();

private:
    Ui::ShowInfoWidget *ui;
    TimeSetDialog *setTimeDlg;
    QTimer *timer;

public:
    void init_show_time();
    bool eventFilter(QObject *object, QEvent *event);
    bool showDlg;
    QString str_date;
    QString str_time;
    int count;

signals:
    void currentDateTime(QString);

public slots:
    void slotUpdateTime();
    void slotPushButton_ok();

};

#endif // SHOWINFOWIDGET_H
