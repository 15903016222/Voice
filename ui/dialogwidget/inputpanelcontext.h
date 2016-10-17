#ifndef INPUTPANELCONTEXT_H
#define INPUTPANELCONTEXT_H

#include <QDialog>

namespace Ui {
class InputPanelContext;
}

class InputPanelContext : public QDialog
{
    Q_OBJECT

public:
    explicit InputPanelContext(QWidget *parent = 0);
    ~InputPanelContext();

private:
    Ui::InputPanelContext *ui;

public:
    bool capsLock;
    void set_item_current_text(QString string);

signals:
    void textEditFinished(QString);

private slots:
    void edit_text();
    void edit_lowerText();
    void on_pushButton_capsLock_clicked();
    void on_pushButton_Space_clicked();
    void on_pushButton_BackSpace_clicked();
    void on_pushButton_ok_clicked();
};

#endif // INPUTPANELCONTEXT_H
