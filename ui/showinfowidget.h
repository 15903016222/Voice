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
    TimeSetDialog setTimeDlg;
    QTimer *timer;

public:
    void initShowTime();
    bool eventFilter(QObject *object, QEvent *event);
    bool showDlg;
    QString str_date;
    QString str_time;

signals:

public slots:
    void slotUpdateTime();
    void slotPushButton_ok();
    void slotEditTime();
    void slot_dateEdit_dateChanged(QDate date);
    void slot_timeEdit_timeChanged(QTime time);

};

#endif // SHOWINFOWIDGET_H
