#ifndef __A_SCAN_WIDGET_H__
#define __A_SCAN_WIDGET_H__

#include <QWidget>

class AscanWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AscanWidget(QWidget *parent = 0);
    void show(const QByteArray &b);

protected:
    void paintEvent(QPaintEvent *e);

signals:

public slots:

private:
    QByteArray m_beam;
};

#endif // __A_SCAN_WIDGET_H__
