#ifndef VERTICALSLIDERDIALOG_H
#define VERTICALSLIDERDIALOG_H

#include <QDialog>
#include <QSlider>

namespace Ui {
class VerticalSliderDialog;
}

class VerticalSliderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerticalSliderDialog(QWidget *parent = 0);
    ~VerticalSliderDialog();

private:
    Ui::VerticalSliderDialog *ui;

public:
    QList<QSlider*> slider;
    void setBrightValue(QString string);

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_decrease_clicked();

};

#endif // VERTICALSLIDERDIALOG_H
