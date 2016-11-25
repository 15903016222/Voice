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

    void init_show_time();
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::ShowInfoWidget *ui;
    TimeSetDialog *setTimeDlg;
    QTimer *timer;

    bool m_showDlg;
    QString m_strDate;
    QString m_strTime;
    int m_count;

signals:
    void currentDateTime(QString);

protected slots:
    void slotUpdateTime();
    void slotPushButton_ok();

};

#endif // SHOWINFOWIDGET_H
