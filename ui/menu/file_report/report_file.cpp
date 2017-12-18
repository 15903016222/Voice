#include "report_file.h"

ReportFile::ReportFile(QObject *parent) :
    BaseFile(parent)
{

}

bool ReportFile::save(const QString &fileName)
{
    return false;
}
