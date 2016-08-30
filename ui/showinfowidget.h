#ifndef SHOWINFOWIDGET_H
#define SHOWINFOWIDGET_H

#include <QWidget>

namespace Ui {
  class ShowInfoWidget;
}

class ShowInfoWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ShowInfoWidget(QWidget *parent = 0);
  ~ShowInfoWidget();

private:
  Ui::ShowInfoWidget *ui;

public:
  void updateTranslatorUi();
  void displayTime();
  void initShowTime();

signals:

public slots:
  void slotUpdateTime();

};

#endif // SHOWINFOWIDGET_H
