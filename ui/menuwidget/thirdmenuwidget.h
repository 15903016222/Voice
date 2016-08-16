#ifndef THIRDMENUWIDGET_H
#define THIRDMENUWIDGET_H

#include "firstsecondmenuwidget.h"

#include <QWidget>
#include <QStandardItemModel>

#define THIRD_MENU_NUMBER 6

static QString THIRD_MENU_STRING[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER][THIRD_MENU_NUMBER] = {
  {
    {"Gain\n(dB)", "Start\n(mm)", "Range\n(mm)", "Velocity\n(m/s)", "Wedge Delay\n(μs)", "UT Unit"},
    {"Tx/Rx mode", "Pulser\n(1 to 128)", "Voltage\n(V)", "PW\n(ns)", "PRF", ""},
    {"Receiver\n(1 to 128)", "Filter", "Rectifier", "Video Filter", "Averaging", ""},
    {"Set 80%", "dB Ref.", "Points Qty.", "Scale Factor", "Sum Gain", ""}
  }, //1
  {
    {"Gate", "Start\n(mm)", "Width\n(mm)", "Threshold\n(%)", "Synchro", "Measure Mode"},
    {"Alarm", "Switch", "Group A", "Condition1", "Operator", "Condition2"},
    {"Output", "Sound", "Delay\n(m/s)", "Hold Time\n(m/s)", "Group", "Data"},
    {"Mode", "", "", "", "", ""},
    {"Mode", "", "", "", "", ""}
  }, //2
  {
    {"Group", "Display", "C-Scan Source", "Min Thickness\n(mm)", "Max Thickness\n(mm)", ""},
    {"Amplitude", "Depth", "TOFD", "", "", ""},
    {"Scan", "A", "B", "C", "", ""}
  }, //3
  {
    {"Group", "Group Mode", "Probe", "Wedge", "Define", "Auto Detect"},
    {"Scan Offset\n(mm)", "Index Offset\n(mm)", "Skew\n(°)", "", "", ""},
    {"Gain\n(dB)", "Start\n(mm)", "Width\n(mm)", "Switch", "", ""},
    {"Geometry", "Thickness\n(mm)", "Diameter", "Material", "Overlay", ""},
    {"Load Part", "Clear Part", "", "", "", ""}
  }, //4
  {
    {"Law Type", "Pulse Connection", "Receiver Connection", "Wave Type", "", ""},
    {"Min. Angle\n(°)", "Max. Angle\n(°)", "Angle Step\n(°)", "", "", ""},
    {"Aperture", "First Element", "Last Element", "Element Step", "", ""},
    {"Type.", "", "", "", "", ""}
  }, //5
  {
    {"Scan", "Type", "Type", "Max Scan Speed", "Max Scan Speed(rpm)", ""},
    {"Encoder", "Encoder Type", "Resolution", "Polarity", "Origin", "Preset"},
    {"Scan Start\n(mm)", "Scan End\n(mm)", "Scan Resolution\n(mm)", "Index Start\n(mm)", "Index End\n(mm)", "Index Resolution\n(mm)"},
    {"Start", "Pause", "", "", "", ""}
  }, //6
  {
    {"Reading Group", "Field1", "Field2", "Field3", "Field4", ""},
    {"Selection", "", "", "", "", ""},
    {"Select", "TOFD Settings", "TOFD Analysis", "", "", ""},
    {"Add/Delete", "Flaw Image", "Comment", "Display Table", "Export Table", ""}
  }, //7
  {
    {"Save Setup As", "Open", "File Manager", "", "", ""},
    {"Storage", "Save Mode", "Save Data", "File Name", "", ""},
    {"Template", "Report Name", "Customer", "Part Name", "Part Number", "Create"},
    {"Probe/Wedge Info", "Inspection Info", "Scan Info", "Encoder Info", "DAC/TCG Info", "Flaw Record Table"},
    {"Select", "Enable", "Label", "Content", "Edit Note", "Print"}
  }, //8
  {
    {"Units", "Bright\n(%)", "Opacity", "", "", ""},
    {"Clock Set\n(HH:MM:SS)", "Date Set", "Language", "", "", ""},
    {"IP Address", "Subnet Mask", "", "", "", ""},
    {"System Infomation", "Cert Import", "SW Update", "HW Update", "Reset Configuration", "About"}
  } //9
};

static QString WIDGET_CHOICE_CHAR[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER][THIRD_MENU_NUMBER]={
  {{"1","1","1","1","1"},{"1","2","3","2","2","2"},{"3","2","2","3","2","1"},{"3","3","3","3","1","1"},{"3","3","3","2","3","2"}},
  {{"2","2","1","1","1","3"},{"2","2","2","3","2"},{"2","3","1","2","1","1"},{"2","2","1","3","3","3"}},
  {{"2","3","2","2","2","2"},{"2","1","1","1","1","1"},{"3","3","3","3","3","2"},{"2","1","1","1"},{"3","3","3","1","3","1"}},
  {{"2","2"},{"2","2","3","3","3","3"},{"2","3","3","3"},{"2","2","2","2","2"}},
  {{"2","2","3","3","3"},{"1","1","2"},{"3","1","1","1"},{"2","1","3","2"},{"3","3"}},
  {{"2","1","3"},{"1","3","3"},{"2","1","3","3"},{"1","1","1","1","2"}},
  {{"3","2","2","1","1","3"},{"3","2","3","1"},{"1","1","1","3","3","3"},{"2","3","3"}},
  {{"2","3","3","3","2","3"},{"2","3","2","3"},{"3","3","3","3","2"},{"2","3","3","3"},{"3","3"}},
  {{"2","1"},{"3","3","2"},{"3","3"},{"3","3"},{"3","3","3","3"}}
}; // widget类型 1 是Spin Box, 2 是Combo Box, 3 是Label 4是on/off Label

namespace Ui {
  class ThirdMenuWidget;
}

class ThirdMenuWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ThirdMenuWidget(QWidget *parent = 0);
  ~ThirdMenuWidget();

private:
  Ui::ThirdMenuWidget *ui;


public:
  void initStandardModel(int i, int j);
  void setThirdMenuName(int i, int j);
  QStandardItemModel *model;
  void widgetStyleChoice(int i, int j, int k);

private:

public slots:

};

#endif // THIRDMENUWIDGET_H
