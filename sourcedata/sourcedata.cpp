#include "sourcedata.h"

#ifdef PHASCAN_I
#include "phascanidata.h"
#endif

QMutex SourceData::m_mutex;
SourceData *SourceData::m_sourceData = NULL;

SourceData *SourceData::get_source_data()
{
    QMutexLocker locker(&m_mutex);
    if(m_sourceData == NULL) {
        m_sourceData= new PhascanIDate();
        m_sourceData->m_isFreeze = false;
        m_sourceData->m_delayTime = 20;
        m_sourceData->m_isDataRecalling = false;
    }
    return m_sourceData;
}

void SourceData::destroyed()
{
    QMutexLocker locker(&m_mutex);
    if(m_sourceData != NULL) {
        delete m_sourceData;
        m_sourceData = NULL;
    }
}
