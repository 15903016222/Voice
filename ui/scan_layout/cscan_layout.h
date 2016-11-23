#ifndef __CSCAN_LAYOUT_H__
#define __CSCAN_LAYOUT_H__

#include <QWidget>

namespace Ui {
class CScanLayout;
}

class CScanLayout : public QWidget
{
    Q_OBJECT

public:
    explicit CScanLayout(QWidget *parent = 0, int group = 4);
    ~CScanLayout();

    void set_display_group(int group);

private:
    Ui::CScanLayout *ui;
};

#endif // __CSCAN_LAYOUT_H__
