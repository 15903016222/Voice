#ifndef __WEDGE_DIALOG_H__
#define __WEDGE_DIALOG_H__

#include <focallaw/wedge.h>

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class WedgeDialog;
}

class WedgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WedgeDialog(QWidget *parent = 0);
    ~WedgeDialog();
    const QString get_path() const;

signals:
    void wedge_changed(QString);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::WedgeDialog *ui;
    DplFocallaw::WedgePointer m_wedgePtr;
    QString m_path;

    QString get_dir();

    void init_select_tab();
    void init_define_tab();

    void show_pa() const;
    void show_ut() const;

private slots:
    void on_dirListWidget_currentTextChanged(const QString &currentText);
    void on_fileListWidget_currentTextChanged(const QString &currentText);
    void on_okPushButton_clicked();
    void on_cancelPushButton_clicked();
    void on_cancelDefinePushButton_clicked();
    void on_savePushButton_clicked();
    void on_saveApplyPushButton_clicked();
    void on_delPushButton_clicked();
};

inline const QString WedgeDialog::get_path() const
{
    return m_path;
}

#endif // __WEDGE_DIALOG_H__
