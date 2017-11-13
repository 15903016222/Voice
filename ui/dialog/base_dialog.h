#ifndef BASE_DIALOG_H
#define BASE_DIALOG_H

#include <QDialog>

namespace Ui {
class BaseDialog;
}

class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = 0);
    ~BaseDialog();

    void set_background(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::BaseDialog *ui;
    QColor          m_bgColor;
};

#endif // BASE_DIALOG_H
