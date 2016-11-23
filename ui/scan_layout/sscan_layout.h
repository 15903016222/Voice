#ifndef __SSCAN_LAYOUT_H__
#define __SSCAN_LAYOUT_H__

#include <QWidget>

namespace Ui {
class SScanLayout;
}

class SScanLayout : public QWidget
{
    Q_OBJECT

public:
    explicit SScanLayout(QWidget *parent = 0, int group = 4);
    ~SScanLayout();

    void set_display_group(int group);

private:
    Ui::SScanLayout *ui;
};

#endif // __SSCAN_LAYOUT_H__
