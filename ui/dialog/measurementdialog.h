#ifndef MEASUREMENTDIALOG_H
#define MEASUREMENTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QListView>

namespace Ui {
class MeasurementDialog;
}

class MeasurementDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MeasurementDialog(QWidget *parent = 0);
  ~MeasurementDialog();
  QList<QPushButton *> buttonList;
  QListView *listView;

  void initUI();

private:
    Ui::MeasurementDialog *ui;

private slots:
  void on_pushButton_cancel_clicked();
  void on_pushButton_ok_clicked();
};

#endif // MEASUREMENTDIALOG_H
