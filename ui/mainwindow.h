#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "firstsecondmenuwidget.h"
#include "commonmenuwidget.h"
#include "commonmenubutton.h"

#include <QMainWindow>
//#include <QGst/Message>
#include <QScrollArea>
#include <QMouseEvent>

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
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *moveEvent);

private:
  Q_DECLARE_PRIVATE(MainWindow)

public:
  CommonMenuWidget * commonMenuWidget;
  FirstSecondMenuWidget *firstSecondMenu;
  CommonMenuButton *commonMenuButton;

//  void linkPluginsToConnectDevice();
  void resizeEvent(QResizeEvent *event);
  void arrowShowFlag();

  bool eventFilter(QObject *object, QEvent *event);
  bool hiddenSecondMenuFlag;
  bool hiddenThirdMenuFlag;
  bool hiddenCommonMenuFlag;

  int firstMenuNum;
  int secondMenuNum;
  int mainMenuStartPos;
  int mainMenuEndPos;

private:
  void initUI();

public slots:

private slots:
  void slot_firstMenuToolBoxCurrentChanged(int index);
  void slot_secondMenuItemClicked(QModelIndex index);
// void onGstBusMessage(const QGst::MessagePtr & message);

  void on_pushButton_top_clicked();
  void on_pushButton_bottom_clicked();
  void slot_pushButton_commonMenuClicked();

};

#endif // MAINWINDOW_H
