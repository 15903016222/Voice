#ifndef A_SCAN_DISPLAY_H
#define A_SCAN_DISPLAY_H

#include <QWidget>
#include "beam_source.h"

namespace Ui {
class AscanDisplay;
}

class AscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanDisplay(QWidget *parent = 0);
    ~AscanDisplay();

    void show(DplSource::BeamSource &beam);

private:
    Ui::AscanDisplay *ui;
};

#endif // A_SCAN_DISPLAY_H
