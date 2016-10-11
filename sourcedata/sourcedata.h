#ifndef SOURCEDATA_H
#define SOURCEDATA_H

#include <QObject>
#include <QMutex>
#include <QTimer>

class SourceData : public QObject
{
    Q_OBJECT
protected:
    explicit SourceData(){}
    virtual ~SourceData(){}
public:
    void set_delay_time(unsigned int delaytime){m_delayTime = delaytime;}
    unsigned int get_delay_time(){return m_delayTime;}
    void set_is_freeze(bool value){m_isFreeze = value;}
    bool get_is_freeze(){return m_isFreeze;}
    void set_data_recalling(bool value){m_isDataRecalling = value;}
    int get_data_recalling(){return m_isDataRecalling;}
    virtual void start_timer() = 0;

    virtual void adjust_scan_or_index_address(int dimension,int  scan,int index,int dataSize) = 0;
    static SourceData *get_source_data();
    static void destroyed();
signals:
    void data_address_event(unsigned int address);
    void freeze_address_event(unsigned int address);
    void recall_address_event(unsigned int address);
public slots:

private:
    static QMutex m_mutex;
    static SourceData *m_sourceData;
    unsigned int m_delayTime;
    bool m_isDataRecalling;
    bool m_isFreeze;
};

#endif // BASESOURCEDATA_H
