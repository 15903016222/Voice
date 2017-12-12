#ifndef __VBOX_LAYOUT_H__
#define __VBOX_LAYOUT_H__

#include <QVBoxLayout>

class VBoxLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    VBoxLayout();
    VBoxLayout(QWidget *parent);
};

#endif // __VBOX_LAYOUT_H__
