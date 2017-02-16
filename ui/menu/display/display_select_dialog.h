#ifndef DISPLAY_SELECT_DIALOG_H
#define DISPLAY_SELECT_DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QListWidget>

namespace Ui {
class DisplaySelectDialog;
}

class DisplaySelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DisplaySelectDialog(QWidget *parent = 0);
    ~DisplaySelectDialog();

private slots:
    void update_list_widget();

    void on_buttonBox_accepted();

private:
    Ui::DisplaySelectDialog *ui;
    QListWidget *m_listWidget;

    void update1();
    void update2();
    void update3();
    void update4();
    void update5();
    void update6();
    void update7();
    void update8();
};

#endif // DISPLAY_SELECT_DIALOG_H
