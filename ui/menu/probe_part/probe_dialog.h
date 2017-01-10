#ifndef __PROBE_DIALOG_H__
#define __PROBE_DIALOG_H__

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

    const QString &get_path() const;

signals:
    void probe_changed(QString);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::ProbeDialog *ui;
    QString m_probePath;

    QString get_path();

private slots:
    void on_dirListWidget_currentTextChanged(const QString &currentText);
    void on_fileListWidget_currentTextChanged(const QString &currentText);
    void on_okPushButton_clicked();
    void on_cancelPushButton_clicked();
};

inline const QString &ProbeDialog::get_path() const
{
    return m_probePath;
}

#endif // PROBEDIALOG_H
