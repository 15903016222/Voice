#ifndef DMAOPERATE_H
#define DMAOPERATE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <QMutex>

#define MEM_DEVICE "/dev/mem"
#define CONFIG_OFFSET              0x00100000
#define SCAN_DATA_MARK_OFFSET      0x00200000
#define REGION_SIZE                0x00040000
#define DMA_DATA_OFFSET                     2

struct DmaParameter{
    int dmaFramerBuffer;
    int dataDmaCounter;
    int bufferInUse;
    int scanSource;
    int storeFrameCount;
    int encoderCounterOffset;
    int stepsPerResolution;
    int scanZeroIndexOffset;
    int maxStoreIndex;
    int scanTimmerCounter;
    int scanTimmerCircled;
};


class DmaOperate
{
private:
    DmaOperate(){};
public:

    unsigned int get_dma_framer_buffer(){return m_dmaParameter->dmaFramerBuffer;}
    void set_dma_framer_buffer(int value){m_dmaParameter->dmaFramerBuffer = value;}

    unsigned int get_data_dma_counter(){return m_dmaParameter->dataDmaCounter;}
    void set_data_dma_counter(int value){m_dmaParameter->dataDmaCounter = value;}

    unsigned int get_buffer_in_use(){return m_dmaParameter->bufferInUse;}
    void set_buffer_in_use(int value){m_dmaParameter->bufferInUse = value;}

    unsigned int get_scan_source(){return m_dmaParameter->scanSource;}
    void set_scan_source(int value){m_dmaParameter->scanSource = value;}

    unsigned int get_store_frame_count(){return m_dmaParameter->storeFrameCount;}
    void set_store_frame_count(int value){m_dmaParameter->storeFrameCount = value;}

    unsigned int get_encoder_counter_offset(){return m_dmaParameter->encoderCounterOffset;}
    void set_encoder_counter_offset(int value){m_dmaParameter->encoderCounterOffset = value;}

    unsigned int get_steps_per_resolution(){return m_dmaParameter->stepsPerResolution;}
    void set_steps_per_resolution(int value){m_dmaParameter->stepsPerResolution = value;}

    unsigned int get_scan_zero_index_offset(){return m_dmaParameter->scanZeroIndexOffset;}
    void set_scan_zero_index_offset(int value){m_dmaParameter->scanZeroIndexOffset = value;}

    unsigned int get_max_store_index(){return m_dmaParameter->maxStoreIndex;}
    void set_max_store_index(int value){m_dmaParameter->maxStoreIndex = value;}

    unsigned int get_scan_timmer_counter(){return m_dmaParameter->scanTimmerCounter;}
    void set_scan_timmer_counter(int value){m_dmaParameter->scanTimmerCounter = value;}

    unsigned int get_scan_timmer_circled(){return m_dmaParameter->scanTimmerCircled;}
    void set_scan_timmer_circled(int value){m_dmaParameter->scanTimmerCircled = value;}

    unsigned char get_m_scan_data_mark(int index){return m_scanDataMark[index];}
    unsigned int get_dma_data_addr(){return m_dmaDataAddr;}
    unsigned int get_store_buffer_addr(){return m_storeBufferAddr;}

    static DmaOperate *get_dma_operate();
    static void destroyed();
private:
    volatile struct DmaParameter *m_dmaParameter;
    int m_fd;
    unsigned int m_dmaDataAddr;
    unsigned int m_storeBufferAddr;
    volatile unsigned char *m_scanDataMark;
    static QMutex m_mutex;
    static DmaOperate *m_dmaOperate;
};

#endif // DMAOPERATE_H
