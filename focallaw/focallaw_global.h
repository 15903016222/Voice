#ifndef __FOCALLAW_GLOBAL_H__
#define __FOCALLAW_GLOBAL_H__

#include <QtCore/qglobal.h>

#if defined(FOCALLAW_LIBRARY)
#  define FOCALLAWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FOCALLAWSHARED_EXPORT Q_DECL_IMPORT
#endif

//#define FOCALLAWSHARED_EXPORT

#endif // __FOCALLAW_GLOBAL_H__