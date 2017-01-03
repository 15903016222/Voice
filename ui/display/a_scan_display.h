#ifndef __A_SCAN_DISPLAY_H__
#define __A_SCAN_DISPLAY_H__

#include <source/beam.h>

#include <QWidget>

namespace Ui {
class AscanDisplay;
}

class AscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanDisplay(QWidget *parent = 0);
    ~AscanDisplay();

    void show(DplSource::Beam &beam);

private:
    Ui::AscanDisplay *ui;
};

#endif // __A_SCAN_DISPLAY_H__
