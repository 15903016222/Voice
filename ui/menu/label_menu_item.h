#ifndef __LABEL_MENU_ITEM_H__
#define __LABEL_MENU_ITEM_H__

#include <QWidget>

namespace Ui {
class LabelMenuItem;
}

class LabelMenuItem : public QWidget
{
    Q_OBJECT

public:
    explicit LabelMenuItem(QWidget *parent = 0);
    ~LabelMenuItem();

    void set_title(const QString &title);

    void set_text(const QString &text);

    void set(const QString &title, const QString &text);

    QString get_text();

signals:
    void clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::LabelMenuItem *ui;
};

#endif // __LABEL_MENU_ITEM_H__
