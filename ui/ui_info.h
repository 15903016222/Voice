#ifndef __UI_INFO_H__
#define __UI_INFO_H__

#include <QObject>
#include <QReadWriteLock>

namespace DplUi {

class UiInfo : public QObject
{
    Q_OBJECT
public:
    static UiInfo *get_instance();

    int current_group() const { QReadLocker l(&m_rwlock); return m_currentGrp; }
    void set_current_group(int id) { QWriteLocker l(&m_rwlock); m_currentGrp = id; }

signals:

public slots:

protected:
    explicit UiInfo(QObject *parent = 0) : QObject(parent) {m_currentGrp = 0;}

private:
    static UiInfo *s_uiInfo;
    QReadWriteLock m_rwlock;
    int m_currentGrp;
};

inline UiInfo *UiInfo::get_instance()
{
    if (s_uiInfo == NULL) {
        s_uiInfo = new UiInfo();
    }
    return s_uiInfo;
}

}
#endif // __UI_INFO_H__
