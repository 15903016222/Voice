#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "firstsecondmenuwidget.h"
#include "commonmenuwidget.h"

#include <QMainWindow>
#include <QGst/Message>
#include <QScrollArea>

namespace Ui {
class MainWindow;
}

class MainWindowPrivate;
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

protected:
  MainWindowPrivate * const d_ptr;

private:
  Q_DECLARE_PRIVATE(MainWindow)

public:
  CommonMenuWidget * commonMenuWidget;
  FirstSecondMenuWidget *firstSecondMenu;

  void linkPluginsToConnectDevice();
  void resizeEvent(QResizeEvent *event);
  void arrowShowFlag();
  bool eventFilter(QObject *object, QEvent *event);
  bool hiddenSecondMenuFlag;
  bool hiddenThirdMenuFlag;

  int firstMenuNum;
  int secondMenuNum;

private:
  void initUI();

public slots:

private slots:
  void slot_setThirdMenuName(int index);
  void slot_secondMenuItemClicked(QModelIndex index);
  void onGstBusMessage(const QGst::MessagePtr & message);
  void slot_pushButton_top_Clicked();
  void slot_pushButton_bottom_Clicked();

};

#endif // MAINWINDOW_H
