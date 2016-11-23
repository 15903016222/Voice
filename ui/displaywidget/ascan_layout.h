#ifndef __ASCAN_LAYOUT_H__
#define __ASCAN_LAYOUT_H__

#include <QWidget>

namespace Ui {
class AScanLayout;
}

class AScanLayout : public QWidget
{
    Q_OBJECT

public:
    explicit AScanLayout(QWidget *parent = 0, int group = 8);
    ~AScanLayout();

    void set_display_group(int group);

private:
    Ui::AScanLayout *ui;
};

#endif // __ASCAN_LAYOUT_H__
