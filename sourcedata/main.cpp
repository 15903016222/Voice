#include "sourcedata.h"
#include <stdio.h>
#include "dmaoperate.h"
#include <QApplication>
#include <QCoreApplication>
int main(int argc,char *argv[])
{
    QCoreApplication a(argc, argv);
    SourceData *base;
    base = SourceData::get_source_data();
    printf("m_sourceData->m_delayTime:%d\n",base->get_delay_time());
    base->start_timer();
    a.exec();
    return 0;
}
