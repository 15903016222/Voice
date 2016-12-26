#ifndef FPGA_GLOBAL_H
#define FPGA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FPGA_LIBRARY)
#  define FPGASHARED_EXPORT Q_DECL_EXPORT
#else
#  define FPGASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FPGA_GLOBAL_H
