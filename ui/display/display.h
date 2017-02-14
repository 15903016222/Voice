#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <QWidget>
#include <QVBoxLayout>
#include <QMutex>
#include <QMap>

namespace DplDisplay {

class Display : public QWidget
{
    Q_OBJECT
public:
    enum Mode {
        A_SCAN,
        B_SCAN,
        C_SCAN,
        S_SCAN,
        AB_SCAN,
        ABC_SCAN,
        ABS_SCAN,
        AC_SCAN,
        ACC_SCAN,
        AS_SCAN,
        ASC_SCAN,
    };

    static Display *get_instance();

signals:

public slots:
    void set_mode(Mode mode);
    void set_show_all(bool flag);
    void reflesh() { show(); }

protected:
    explicit Display(QWidget *parent = 0);

    void show();

    /**
     * @brief show_single_scan  显示一个模式Scan
     */
    template <typename T>
    void show_single_scan();

    void show_ab_scan();
    void show_abc_scan();
    void show_abs_scan();
    void show_ac_scan();
    void show_acc_scan();
    void show_as_scan();
    void show_asc_scan();

private:
    static Display *s_display;
    static QMutex s_mutex;

    Mode m_type;
    bool m_showAllFlag;

    typedef void (Display::*ShowFun)();
    ShowFun m_showMap[ASC_SCAN];

    QWidget *m_widget;
    QVBoxLayout *m_vboxLayout;

    void init_show_map();
};

}

#endif // __DISPLAY_H__
