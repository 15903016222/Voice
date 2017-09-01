#ifndef __INSPECTION_MENU_H__
#define __INSPECTION_MENU_H__

#include "../base_menu.h"

#include <source/scan.h>

namespace DplScanMenu {

class InspectionMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit InspectionMenu(QWidget *parent);

protected slots:
    void do_typeItem_changed(int pos);
    void do_scanItem_changed(int pos);
    void do_indexItem_changed(int pos);

    void do_scanAxis_driving_changed(DplSource::Axis::Driving driving);
    void do_indexAxis_driving_changed(DplSource::Axis::Driving driving);

private:
    ComboMenuItem *m_typeItem;
    ComboMenuItem *m_scanItem;
    ComboMenuItem *m_indexItem;
    SpinMenuItem *m_maxScanSpeedItem;
    SpinMenuItem *m_maxScanSpeedRPMItem;

    DplSource::Scan *m_scan;
    DplSource::AxisPointer m_scanAxis;
    DplSource::AxisPointer m_indexAxis;
    DplSource::EncoderPointer m_encX;
    DplSource::EncoderPointer m_encY;
};

}
#endif // __INSPECTION_MENU_H__
