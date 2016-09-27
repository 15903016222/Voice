#ifndef TOPMENU
#define TOPMENU

#include "measurementdialog.h"
#include "thirdmenuwidget.h"

#include <QLabel>

#define TOP_MENU_NUMBER 10

namespace Ui {
class TopMenu;
}

class TopMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TopMenu(QWidget *parent = 0);
    ~TopMenu();

private:
    Ui::TopMenu *ui;

public:
    QList<QLabel* > measurementLabelList;
    QStandardItemModel *model;
    MeasurementDialog *mDialog;
    QString objectName;
    ThirdMenuWidget *thirdMenuWidget;

    void reTranslatorTopMenuUi();
    void initUI();
    void setTopMenuFont();
    void initGain_angle();
    void initStandardModel();

    bool eventFilter(QObject *object, QEvent *event);

signals:
    void currentDialogIndex(QString);

private slots:
    void changeLabelText(QString str);

};

#endif // TOPMENU

