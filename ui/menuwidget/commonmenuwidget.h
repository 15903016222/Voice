#ifndef COMMONMENUWIDGET_H
#define COMMONMENUWIDGET_H

#include <QWidget>
#include <QStandardItemModel>

#define COMMON_MENU_NUMBER 7
static QString CHOICE_WIDGET_CHAR[COMMON_MENU_NUMBER] = {"3", "3", "3", "3", "1", "3", "1"}; // widget类型 1 是Spin Box, 2 是Combo Box, 3 是Label 4是on/off Label

namespace Ui {
class CommonMenuWidget;
}

class CommonMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommonMenuWidget(QWidget *parent = 0);
    ~CommonMenuWidget();

private:
    Ui::CommonMenuWidget *ui;

public:
    void reTranslatorCommonMenuUi();
    void initStandardModel();
    void setCommonMenuName();
    QStandardItemModel *model;
    void widgetStyleChoice(int k);
    void resizeEvent(QResizeEvent *event);

    int height;
    int width;

private:

public slots:
    void onHeaderClicked(int index);
    void set_header_text_create(QStringList stringList) const ;
    void set_header_text_close(QWidget *editor) ;
};

#endif // COMMONMENUWIDGET_H
