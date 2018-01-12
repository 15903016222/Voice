#ifndef __STATIC_WELD_WIDGET_H__
#define __STATIC_WELD_WIDGET_H__

#include <QWidget>

namespace Ui {
class StaticWeldWidget;
}

class StaticWeldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StaticWeldWidget(QWidget *parent = 0);
    ~StaticWeldWidget();

public slots:
    void slot_weld_type_changed(const QString &path);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::StaticWeldWidget    *ui;
    QString                 m_picPath;
};

#endif // __STATIC_WELD_WIDGET_H__
