#ifndef DISPLAY_SELECT_DIALOG_H
#define DISPLAY_SELECT_DIALOG_H

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

    enum LayoutMode {
        /* One Group */
        A,
        S,
        C,
        AS,
        SC,
        AB,
        ABC,
        ASB,
        ASC,
        /* Two Group */
        A2,
        S2,
        C2,
        AS2,
        ASC2,
        SC_AB,
        AB2,
        SC2,
        ABC2,
        ASB2,
        /* Three Group */
        A3,
        S3,
        C3,

        ASC3,
        AS3,
        MAX_MODE
    };

private slots:
    void update_widget();

    void on_buttonBox_accepted();

protected:
    QWidget *a_layout();

private:
    Ui::DisplaySelectDialog *ui;
    QWidget *m_widget;
    QButtonGroup *m_radioBtnGrp;

    void update(int startMode, int endMode);
};

#endif // DISPLAY_SELECT_DIALOG_H
