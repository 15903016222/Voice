#include "phascanidata.h"
#include <stdio.h>

QMutex PhascanIDate::m_mutex;
static unsigned int getBeamDataAddr(unsigned int dmaAddress,int i);

PhascanIDate::PhascanIDate()
{
    m_dma_operate = DmaOperate::get_dma_operate();
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(timeoutFun()));
    m_dma_operate->set_store_frame_count(100);
}

PhascanIDate::~PhascanIDate()
{

}

void PhascanIDate::timeoutFun()
{
    static int j=0;
    int counter = 0 ,i = 0;

    if(m_dma_operate->get_dma_framer_buffer()){
        m_mutex.lock();
        m_dma_operate->set_dma_framer_buffer(0);
        counter = m_dma_operate->get_data_dma_counter();
        i = (counter + 3) & 0x3;
        //printf("counter():%d  use:%d\n",i,m_dma_operate->get_buffer_in_use());
        if(i == m_dma_operate->get_buffer_in_use()){
            i = (i + 3) & 0x3;
        }
        //printf("counter():%d  use:%d\n",i,m_dma_operate->get_buffer_in_use());
        m_dma_operate->set_buffer_in_use(i);
        emit data_address_event(getBeamDataAddr(m_dma_operate->get_dma_data_addr(),i));
        m_mutex.unlock();
    }else if(get_is_freeze()){
        m_mutex.lock();
        if(get_data_recalling()){
            i = 0;
            emit recall_address_event(getBeamDataAddr(m_dma_operate->get_dma_data_addr(),i));
        }else{
            counter = m_dma_operate->get_data_dma_counter();
            i = (counter + 3) & 0x3;
            m_dma_operate->set_buffer_in_use(i);
            emit freeze_address_event(getBeamDataAddr(m_dma_operate->get_dma_data_addr(),i));
        }
        m_mutex.unlock();
    }

}

void PhascanIDate::adjust_scan_or_index_address(int dimension,int  scan,int index,int dataSize)
{
    if(dimension == 1){
        m_dma_operate->set_scan_timmer_counter(scan);
        if(m_dma_operate->get_m_scan_data_mark(scan)) {
            memcpy((void *)m_dma_operate->get_dma_data_addr(),(void *)(m_dma_operate->get_store_buffer_addr() + scan * dataSize), dataSize);
        }else {
            memcpy((void *)m_dma_operate->get_dma_data_addr(),0,dataSize);
        }
    }else if(dimension == 2){

    }
}

static unsigned int getBeamDataAddr(unsigned int dmaAddress,int i)
{
    return (dmaAddress + DMA_DATA_OFFSET + REGION_SIZE * i);
}
