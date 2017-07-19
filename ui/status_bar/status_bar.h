#ifndef __STATUS_BAR__
#define __STATUS_BAR__

#include <QWidget>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = 0);
    ~StatusBar();

protected slots:
    void do_timeout();

private:
    Ui::StatusBar *ui;
    QTimer *m_timer;
};

#endif // __STATUS_BAR__
