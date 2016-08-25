#ifndef MEASUREMENTDIALOG_H
#define MEASUREMENTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QListView>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QStandardItemModel>

#define MEASUREMENT_NUMBER 51

static QString MEASUREMENT_STRING[MEASUREMENT_NUMBER] =
{
    "A% Peak amplitude in gate A",
    "AdBA Signal in gate minus gate level for gate A",
    "AdBr Difference between signal and reference in gate A",
    "B% Peak amplitude in gate B",
    "BdBB Signal in gate minus gate level for gate B",
    "BdBr Difference between signal and reference in gate B",
    "A^ Position in gate A",
    "B^ Position in gate B",
    "I/ Position in gate I",
    "I(W)/ Position in gate I in water",
    "T(A^) Thickness",
    "ML Percentage of Material loss",
    "%(r) Amplitude value for reference cursor",
    "%(m) Amplitude value of the measurement cursor",
    "%(m-r) Amplitude (measurement cursor - reference cursor)",
    "U(r) Ultrasonic position of the reference cursor",
    "U(m) Ultrasonic position of the measurement cursor",
    "U(m-r) Ultrasonic axix(measurement cursor - reference cursor)",
    "P(r) Probe position of the reference cursor",
    "P(m) Probe position of the measurement cursor",
    "P(m-r) Probe (measurement cursor - reference cursor)",
    "S(r)  Scan position of the reference cursor",
    "S(m)  Scan position of the measurment cursor",
    "S(m-r)  Scan (measurement cursor - reference cursor)",
    "I(r) Index position of the reference cursor",
    "I(m) Index position of the measurement cursor",
    "I(m-r) Index axis(measurement cursor - reference cursor)",
    "RA^ Reference point to the indication in gate A",
    "RB^ Reference point to the indication in gate B",
    "PA^ Probe front face to the indication in gate A",
    "PB^ Probe front face to the indication in gate B",
    "DA^ Depth of the indication in gate A",
    "DB^ Depth of the indication in gate B",
    "SA^ Sound path of the indication in gate A",
    "SB^ Sound path of the indication in gate B",
    "ViA^ Volumetric position in gate A on the index axis",
    "ViB^ Volumetric position in gate B on the index axis",
    "VsA^ Volumetric position in gate A on the scan axis",
    "VsB^ Volumetric position in gate B on the scan axis",
    "LA^ Leg(skip)of the indication in gate A",
    "LB^ Leg(skip)of the indication in gate B",
    "E% Peak amplitude of the envelop in gate A",
    "AWS-DA Indication level for AWS-D1.5A",
    "AWS-DB Zero reference  level for AWS-D1.5B",
    "AWS-DC Attenuation factor for AWS-D1.5 C",
    "AWS-DD Indication rating for AWS-D1.5D",
    "AWS-D45 Discontinuity severity class for AWS-D1.5 45",
    "AWS-D60 Discontinuity severity class for AWS-D1.5 60",
    "AWS-D70 Discontinuity severity class for AWS-D1.5 70",
    "AWS-D CL Discontinuity severity class for AWS-D1.5",
    "DA-DI"
};

namespace Ui {
class MeasurementDialog;
}

class MeasurementDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MeasurementDialog(QWidget *parent = 0);
  ~MeasurementDialog();

private:
  Ui::MeasurementDialog *ui;

public:
  QList<QPushButton *> buttonList;
  QListView *listView;
  QStringList measurementList;
  QStandardItemModel *measurementModel;
  QMap<QString, QString> labelMap;
  QString changedString;

  bool changedFlag;

private:
  void initUI();

signals:
  void labelTextChanged(QString);

private slots:
  void on_pushButton_cancel_clicked();
  void on_pushButton_ok_clicked();
  void slot_listViewItemClicked(QModelIndex index);

};

#endif // MEASUREMENTDIALOG_H
