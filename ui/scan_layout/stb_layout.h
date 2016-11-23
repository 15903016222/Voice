#ifndef __STB_LAYOUT_H__
#define __STB_LAYOUT_H__

#include <QWidget>

namespace Ui {
class STBLayout;
}

class STBLayout : public QWidget
{
    Q_OBJECT

public:
    explicit STBLayout(QWidget *parent = 0, int group = 6);
    ~STBLayout();

    void set_display_group(int group);

private:
    Ui::STBLayout *ui;
};

#endif // __STB_LAYOUT_H__
