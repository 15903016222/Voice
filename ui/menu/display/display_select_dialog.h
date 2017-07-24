#ifndef __DISPLAY_SELECT_DIALOG_H__
#define __DISPLAY_SELECT_DIALOG_H__

#include <QDialog>
#include <QButtonGroup>
#include <QSharedPointer>

namespace Ui {
class DisplaySelectDialog;
}

class DisplaySelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DisplaySelectDialog(QWidget *parent = 0);
    ~DisplaySelectDialog();

private slots:
    void on_checkBox_all_clicked(bool checked);

    void update_widget();

    void on_buttonBox_accepted();


private:
    Ui::DisplaySelectDialog *ui;
    QButtonGroup *m_radioBtnGrp;
    QList<int> m_grpIds;

    void update(int startMode, int endMode);
};

#endif // __DISPLAY_SELECT_DIALOG_H__
