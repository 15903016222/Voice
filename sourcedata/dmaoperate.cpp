#include "dmaoperate.h"
#include <stdio.h>
QMutex DmaOperate::m_mutex;
DmaOperate *DmaOperate::m_dmaOperate = NULL;

DmaOperate *DmaOperate::get_dma_operate()
{
    QMutexLocker locker(&m_mutex);
    if(m_dmaOperate == NULL) {
        m_dmaOperate = new DmaOperate;

        if ((m_dmaOperate->m_fd = open(MEM_DEVICE, O_RDWR | O_SYNC)) == -1) {
            printf("error\n");
            exit(-1);
        }
        m_dmaOperate->m_dmaDataAddr = (unsigned int)mmap (0,  16 * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, m_dmaOperate->m_fd, 0x8f000000);
        m_dmaOperate->m_storeBufferAddr = (unsigned int)mmap (0, 256 * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, m_dmaOperate->m_fd, 0x90000000);
        m_dmaOperate->m_dmaParameter = (struct DmaParameter *)(m_dmaOperate->m_dmaDataAddr + CONFIG_OFFSET);
        m_dmaOperate->m_scanDataMark = (unsigned char *)(m_dmaOperate->m_dmaDataAddr + SCAN_DATA_MARK_OFFSET);

    }
    return m_dmaOperate;
}

void DmaOperate::destroyed()
{
    QMutexLocker locker(&m_mutex);
    if(m_dmaOperate != NULL) {
        munmap((void *)m_dmaOperate->m_dmaDataAddr,16 * 1024 * 1024);
        munmap((void *)m_dmaOperate->m_storeBufferAddr,256 * 1024 * 1024);
        close(m_dmaOperate->m_fd);
        delete m_dmaOperate;
        m_dmaOperate = NULL;
    }
}
