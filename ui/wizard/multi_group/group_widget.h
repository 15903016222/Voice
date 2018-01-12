#ifndef GROUP_WIDGET_H
#define GROUP_WIDGET_H

#include <QWidget>

namespace Ui {
class GroupWidget;
}

class GroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupWidget(int groupIndex, QWidget *parent = 0);
    ~GroupWidget();

    inline int index() { return m_groupIndex; }

    void set_focus();

signals:
    void setting_clicked(int model, int index);

private slots:
    void on_settingPushButton_clicked();

private:
    Ui::GroupWidget *ui;
    int m_groupIndex;
};

#endif // GROUP_WIDGET_H
