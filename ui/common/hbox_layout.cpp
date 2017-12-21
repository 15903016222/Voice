#include "hbox_layout.h"

HBoxLayout::HBoxLayout() : QHBoxLayout()
{
    setContentsMargins(0, 0, 0, 0);
    setSpacing(0);
}

HBoxLayout::HBoxLayout(QWidget *parent) : QHBoxLayout(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setSpacing(0);
}

