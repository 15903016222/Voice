#ifndef __A_SCAN_DISPLAY_H__
#define __A_SCAN_DISPLAY_H__

#include <device/device.h>

#include <source/beam.h>

#include <QWidget>

namespace Ui {
class AscanDisplay;
}

class AscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanDisplay(DplDevice::GroupPointer &group, QWidget *parent = 0);
    ~AscanDisplay();

    void show(DplSource::Beam &beam);

private:
    Ui::AscanDisplay *ui;

    DplDevice::GroupPointer m_group;

private slots:
    void do_ut_unit_changed(DplDevice::Group::UtUnit unit);
};

#endif // __A_SCAN_DISPLAY_H__
