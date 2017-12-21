#include "vbox_layout.h"

VBoxLayout::VBoxLayout() : QVBoxLayout()
{
    setContentsMargins(0, 0, 0, 0);
    setSpacing(0);
}

VBoxLayout::VBoxLayout(QWidget *parent) : QVBoxLayout(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setSpacing(0);
}
