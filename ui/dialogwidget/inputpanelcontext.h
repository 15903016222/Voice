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

signals:
    void textEditFinished(QString);

private slots:
    void edit_text();
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();
    void set_item_current_text(QString string);
};

#endif // INPUTPANELCONTEXT_H
