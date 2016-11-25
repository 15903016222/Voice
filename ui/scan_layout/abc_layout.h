#ifndef __ABC_LAYOUT_H__
#define __ABC_LAYOUT_H__

#include <QWidget>

namespace Ui {
class ABCLayout;
}

class ABCLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ABCLayout(QWidget *parent = 0, int group = 3);
    ~ABCLayout();

    void set_display_group(int group);

private:
    Ui::ABCLayout *ui;
};

#endif // __ABC_LAYOUT_H__
