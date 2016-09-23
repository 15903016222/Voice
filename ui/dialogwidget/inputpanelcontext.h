#ifndef INPUTPANELCONTEXT_H
#define INPUTPANELCONTEXT_H

#include <QWidget>

namespace Ui {
class InputPanelContext;
}

class InputPanelContext : public QWidget
{
    Q_OBJECT

public:
    explicit InputPanelContext(QWidget *parent = 0);
    ~InputPanelContext();

private:
    Ui::InputPanelContext *ui;
};

#endif // INPUTPANELCONTEXT_H
