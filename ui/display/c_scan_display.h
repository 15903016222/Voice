#ifndef __C_SCAN_DISPLAY_H__
#define __C_SCAN_DISPLAY_H__

#include <QWidget>
#include <device/group.h>

namespace Ui {
class ScanDisplay;
}

class ScanView;
class CscanScene;
class RulerWidget;

class CscanDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit CscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent = 0);
    ~CscanDisplay();

signals:


public slots:

protected:
    Ui::ScanDisplay *ui;
    DplDevice::GroupPointer m_group;
    ScanView    *m_view;
    CscanScene  *m_scene;

    Qt::Orientation m_orientation;

    RulerWidget *m_scanTypeRuler;       /* 时间扫查（s）/编码器扫擦（mm） */
    RulerWidget *m_lawTypeRuler;    /* 一维扫查：该标尺为度数（扫查类型：扇扫）或阵元数（扫查方式：线性）；
                                       二维扫查，该标尺为步进轴 */


    virtual void init_ruler();
    void update_scan_type_ruler(const QSize &size);
    void update_law_type_ruler();



};

#endif // __C_SCAN_DISPLAY_H__
