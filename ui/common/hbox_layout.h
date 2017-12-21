#ifndef __HBOX_LAYOUT_H__
#define __HBOX_LAYOUT_H__

#include <QHBoxLayout>

class HBoxLayout : public QHBoxLayout
{
    Q_OBJECT
public:
    HBoxLayout();
    explicit HBoxLayout(QWidget *parent);
};

#endif // __HBOX_LAYOUT_H__
