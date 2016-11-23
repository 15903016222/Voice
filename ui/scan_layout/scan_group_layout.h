#ifndef __SCANGROUP_LAYOUT_H__
#define __SCANGROUP_LAYOUT_H__

#include <QWidget>

namespace Ui {
class ScanGroupLayout;
}

class ScanGroupLayout : public QWidget
{
    Q_OBJECT

public:
    enum ScanType {
        A_scan,
        B_scan,
        C_scan,
        S_scan,
        A_Sscan,
        A_B_Cscan,
        A_B_Sscan,
        A_S_Cscan,
        S_Cscan,
        C_TB,
        S_TB,
        S_TA,
        S_TA_C_TB,
        TA_TB
    };
    explicit ScanGroupLayout(QWidget *parent = 0, ScanGroupLayout::ScanType type = ScanGroupLayout::A_scan, int group = 1);
    ~ScanGroupLayout();

    void set_display_group(ScanType type, int group);

private:
    Ui::ScanGroupLayout *ui;
};

#endif // __SCANGROUP_LAYOUT_H__
