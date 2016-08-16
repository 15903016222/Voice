#ifndef FOURTHMENUWIDGET_H
#define FOURTHMENUWIDGET_H

#include "thirdmenuwidget.h"

#include <QWidget>
#include <QStandardItemModel>

#define FOURTH_MENU_NUMBER 8

static QString FOURTH_MENU_STRING[FOURTH_MENU_NUMBER] = {"A%\n(%)", "DA^\n(mm)", "PA^\n(mm)", "SA^\n(mm)",
                                                         "U(m-r)^\n(mm)", "I(m-r)^\n(mm)", "S(m-r)^\n(mm)", "TCG-SL\n(±dB)"};

namespace Ui {
  class FourthMenuWidget;
}

class FourthMenuWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FourthMenuWidget(QWidget *parent = 0);
  ~FourthMenuWidget();

private:
  Ui::FourthMenuWidget *ui;

private:


public:
  QStandardItemModel *model;
  void initGain_angle();
  void initStandardModel();
  void FourthMenuWidgetRetranslateUi();

signals:

public slots:

};

#endif // FOURTHMENUWIDGET_H
