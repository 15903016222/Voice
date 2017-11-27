#ifndef __FPGA_GLOBAL_H__
#define __FPGA_GLOBAL_H__

#include <QtCore/qglobal.h>

#if defined(FPGA_LIBRARY)
#  define FPGASHARED_EXPORT Q_DECL_EXPORT
#else
#  define FPGASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // __FPGA_GLOBAL_H__
