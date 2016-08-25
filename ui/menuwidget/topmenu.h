#ifndef TOPMENU
#define TOPMENU

#include "measurementdialog.h"

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QStandardItemModel>

namespace Ui {
class TopMenu;
}

class TopMenu : public QWidget
{
  Q_OBJECT

public:
  explicit TopMenu(QWidget *parent = 0);
  ~TopMenu();
  QList<QLabel* > measurementLabelList;
  QStandardItemModel *model;
  MeasurementDialog *mDialog;
  QString objectName;

  void initUI();
  void initGain_angle();
  void initStandardModel();

  bool eventFilter(QObject *object, QEvent *event);

private:
  Ui::TopMenu *ui;

private slots:
  void changedLabelText(QString str);

};

#endif // TOPMENU

