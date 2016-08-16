#ifndef ICONSWIDGETS_H
#define ICONSWIDGETS_H

#include "myinputpanel.h"

#include <QWidget>

namespace Ui {
  class IconsWidget;
}

class IconsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit IconsWidget(QWidget *parent = 0);
  ~IconsWidget();

private:
  Ui::IconsWidget *ui;
  MyInputPanel *myInputPanel;

public:
  void iconsWidgetRetranslateUi();

signals:

public slots:
  void on_pushButton_keyboard_clicked();

};

#endif // ICONSWIDGETS_H
