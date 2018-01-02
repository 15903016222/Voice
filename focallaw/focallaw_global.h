#ifndef __FOCALLAW_GLOBAL_H__
#define __FOCALLAW_GLOBAL_H__

#include <QtCore/qglobal.h>
#include <qmath.h>

#ifdef WIN32

#define FOCALLAWSHARED_EXPORT

#else

#if defined(FOCALLAW_LIBRARY)
#  define FOCALLAWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FOCALLAWSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif

namespace Dpl {

static inline float degree2pi(float val)
{
    return val * M_PI / 180;
}

static inline float pi2degree(float val)
{
    return val * 180 / M_PI;
}

//#define FOCALLAWSHARED_EXPORT

}

#endif // __FOCALLAW_GLOBAL_H__
