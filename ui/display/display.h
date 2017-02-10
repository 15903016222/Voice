#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <QWidget>
#include <QMap>

namespace DplDisplay {

class Display : public QWidget
{
    Q_OBJECT
public:
    enum Type {
        NONE_SCAN,
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

    explicit Display(QWidget *parent = 0);

    void set_type(Type type);
    void set_show_all(bool flag);

signals:

public slots:

protected:
    void show();
    void show_a_scan();
    void show_b_scan();
    void show_c_scan();
    void show_s_scan();
    void show_ab_scan();
    void show_abc_scan();
    void show_abs_scan();
    void show_ac_scan();
    void show_acc_scan();
    void show_as_scan();
    void show_asc_scan();

private slots:

private:
    Type m_type;
    bool m_showAllFlag;
    typedef void (Display::*ShowFun)();
    ShowFun m_showMap[ASC_SCAN];
//    QMap<Type, ShowFun> m_showMap;

    void init_show_map();
};

}

#endif // __DISPLAY_H__
