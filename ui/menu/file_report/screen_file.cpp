#include "screen_file.h"

ScreenFile::ScreenFile(QObject *parent) :
    BaseFile(parent)
{

}

bool ScreenFile::save(const QString &fileName)
{
    return false;
}
