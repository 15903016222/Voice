#ifndef FIRSTSECONDMENUWIDGET_H
#define FIRSTSECONDMENUWIDGET_H

#include <QWidget>
#include <QToolBox>
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>

#define FIRST_MENU_NUMBER 9
#define SECOND_MENU_NUMBER 5

static QString SECOND_MENU_STRING[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER] = {
  {"General", "Pulser", "Receiver", "Advanced", ""},
  {"Gate", "Alarm", "Output", "DAC", "TCG"},
  {"Selection", "Color Setting", "Properties", "", ""},
  {"Select", "Position", "FFT", "Part", "Advanced"},
  {"Law Config", "Angle", "Aperture", "Focal Point", ""},
  {"Inspection", "Encoder", "Area", "Start", ""},
  {"Reading", "Cursors", "TOFD", "Flaw Record", ""},
  {"File", "Save Mode", "Report", "Format", "User Field"},
  {"Preference", "System", "Network", "Service", ""}
};

namespace Ui{
class FirstSecondMenuWidget;
}

class FirstSecondMenuWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FirstSecondMenuWidget(QWidget *parent = 0);
  ~FirstSecondMenuWidget();

private:
  Ui::FirstSecondMenuWidget *ui;

public:
  QList<QToolBox*> toolBox;
  QList<QListView*> menuList;
  QList<QStandardItemModel*> modelList;

  void hideFirstMenuPage();

private:
  void initUI();

private slots:

public slots:
//   void slot_getFirstMenuNum(int index);
};

#endif // FIRSTSECONDMENUWIDGET_H
