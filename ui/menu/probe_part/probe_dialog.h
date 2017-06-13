#ifndef __PROBE_DIALOG_H__
#define __PROBE_DIALOG_H__

#include <focallaw/probe.h>

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ProbeDialog;
}

class ProbeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProbeDialog(QWidget *parent = 0);
    ~ProbeDialog();

    DplFocallaw::ProbePointer get_probe() const;

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::ProbeDialog *ui;
    DplFocallaw::ProbePointer m_probePtr;
    QString m_probePath;

    QString get_dir();

    void init_select_tab();
    void init_define_tab();

    void show_info() const;

private slots:
    void on_dirListWidget_currentTextChanged(const QString &currentText);
    void on_fileListWidget_currentTextChanged(const QString &currentText);
    void on_okPushButton_clicked();
    void on_cancelPushButton_clicked();
    void on_cancelDefinePushButton_clicked();
    void on_savePushButton_clicked();
    void on_saveApplyPushButton_clicked();
    void on_delPushButton_clicked();
    void on_modelLineEdit_textEdited(const QString &arg1);
    void on_serialLineEdit_textEdited(const QString &arg1);
    void on_typeComboBox_currentIndexChanged(int index);
    void on_freqDoubleSpinBox_valueChanged(double arg1);
    void on_priElemQtySpinBox_valueChanged(int arg1);
    void on_secElemQtySpinBox_valueChanged(int arg1);
    void on_priPitchDoubleSpinBox_valueChanged(double arg1);
    void on_secPitchDoubleSpinBox_valueChanged(double arg1);
};

inline DplFocallaw::ProbePointer ProbeDialog::get_probe() const
{
    return m_probePtr;
}

#endif // PROBEDIALOG_H
