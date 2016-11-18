#ifndef COMMONMENUWIDGET_H
#define COMMONMENUWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>

#define COMMON_MENU_NUMBER 7
static QString CHOICE_WIDGET_CHAR[COMMON_MENU_NUMBER] = {"1", "1", "1", "3", "3", "3", "1"}; // widget类型 1 是Spin Box, 2 是Combo Box, 3 是Label 4是on/off Label

namespace Ui {
class CommonMenuWidget;
}

class CommonMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommonMenuWidget(QWidget *parent = 0);
    ~CommonMenuWidget();

    void retranslate_common_menu_ui();
    void resizeEvent(QResizeEvent *event);

    int opendSpinBoxIndex;
    bool m_keyboardShowFlag;
    QStandardItemModel *model;
    QTableView *pTableView;

private:
    Ui::CommonMenuWidget *ui;

    void init_standard_model();
    void set_common_menu_name();
    void choose_widget_style(int k);
    void change_persistent_editor();

    int m_height;
    int m_width;

private slots:
    void onHeaderClicked(int index);
    void set_header_text_create(QStringList stringList) const;
    void set_header_text_close(QWidget *editor);
    void on_tableView_clicked(const QModelIndex &index);
};

#endif // COMMONMENUWIDGET_H
