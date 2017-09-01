/******************************************************************************
* 版权所有 (C)2008，xxxx有限公司
*
* 文件名称： // Tracer.h
* 内容摘要： // 定义Tracer类，用于调试信息的输出
* 其它说明： // 无
* 版 本 号： // V0.0.1.0
* 作    者： // 部门 xxxx
* 完成日期： // 2015年7月15日
*
* 修改记录1： // 修改历史记录，包括修改日期、现版本号、修改者及修改内容
*   修改日期：
*   版 本 号：
*   修 改 人：
*   修改内容：
* 修改记录2：...
******************************************************************************/


#ifndef TRACER_H
#define TRACER_H


/******************************************************************************
*                                 头文件包含                                  *
******************************************************************************/
#define QT_ENV

#ifdef QT_ENV
#include <QString>
#include <QDebug>
#else
#include <string>
#endif


/******************************************************************************
*                                 常量定义                                    *
******************************************************************************/


/******************************************************************************
*                                 宏定义                                      *
******************************************************************************/

#ifdef NDEBUG

#define DEBUG_INIT(module, function) {}

#define DEBUG_MSG(level, msg) {}
#define DEBUG_MSG_MSG(level, msg1, msg2) {}
#define DEBUG_MSG_VALUE(level, msg, value) {}

#else

#define DEBUG_INIT(module, function) Tracer tracer(module, function)

#define DEBUG_MSG(level, msg) tracer.trace(level, msg)
#define DEBUG_MSG_MSG(level, msg1, msg2) tracer.trace(level, msg1, msg2)
#define DEBUG_MSG_VALUE(level, msg, value) tracer.trace(level, msg, value)

#endif


/******************************************************************************
*                                 数据类型                                    *
******************************************************************************/


/******************************************************************************
*                                 类声明                                      *
******************************************************************************/

class Tracer
{

public:

    #ifdef QT_ENV

    Tracer(const QString &moduleName, const QString &functionName);

    #else

    Tracer(const char *moduleName, const char *functionName);
    static void setTraceLevel(unsigned int traceLevel);

    void trace(unsigned int level, const char *msg);
    void trace(unsigned int level, const char *msg1, const char *msg2);
    void trace(unsigned int level, const char *msg, unsigned long value);

    #endif

	~Tracer();



private:
	static unsigned int s_traceLevel;

#ifdef QT_ENV
    QString m_infoHead;
    QString m_functionName;
#else
	std::string m_infoHead;
	std::string m_functionName;
#endif

private:
	/* 禁止拷贝与赋值 */
	Tracer(const Tracer &other);
	Tracer& operator=(const Tracer &other);
};


/******************************************************************************
*                                 模板                                        *
******************************************************************************/


/******************************************************************************
*                                 全局变量声明                                *
******************************************************************************/


/******************************************************************************
*                                 全局函数原型                                *
******************************************************************************/


#endif
