#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <QWidget>

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

    bool set_type(Type type);
    void set_show_all(bool flag);

signals:

public slots:

private slots:
    void do_source_data_event();

private:
    Type m_type;
    bool m_showAll;

    QWidget *m_scanDisplay;
};

}

#endif // __DISPLAY_H__
