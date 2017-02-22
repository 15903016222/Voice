#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <device/group.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QMutex>
#include <QMap>

#include "scan_layout.h"

namespace DplDisplay {

class Display : public QWidget
{
    Q_OBJECT
public:
    static Display *get_instance();

public slots:
    void set_layout(ScanLayout *scanlayout);

protected:
    explicit Display(QWidget *parent = 0);

    /**
     * @brief show_single_scan  显示单个模式Scan
     */
    template <typename T>
    void show_scan();

private:
    static Display *s_display;
    static QMutex s_mutex;

    ScanLayout *m_scanLayout;
    QVBoxLayout *m_vboxLayout;
};

}

#endif // __DISPLAY_H__
