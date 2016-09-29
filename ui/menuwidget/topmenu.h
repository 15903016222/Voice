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

    void retranslate_top_menu_ui();
    void init_ui();
    void set_top_menu_font();
    void init_gain_angle();

    bool eventFilter(QObject *object, QEvent *event);

signals:
    void currentDialogIndex(QString);

private slots:
    void changeLabelText(QString str);

};

#endif // TOPMENU

