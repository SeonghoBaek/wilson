/** 
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#ifndef _LOG_H_
#define _LOG_H_

#define LOG_PRINT_ENABLE 1

#define NODEBUS_LOG_ERROR -1

#define NODEBUS_LOG_WARN 0

#define NODEBUS_LOG_INFO 1

#define NODEBUS_LOG_DEBUG 2

#define NODEBUS_LOG_VERBOSE 3

#define DEBUG_MODE 0
#define RELEASE_MODE 0

#define  LOGE(...) \
           NBUS_PrintMessage(NODEBUS_LOG_ERROR,__func__,__LINE__,__VA_ARGS__)

#define  LOGW(...) \
           NBUS_PrintMessage(NODEBUS_LOG_WARN,__func__,__LINE__,__VA_ARGS__)


#define  LOGI(...) \
           NBUS_PrintMessage(NODEBUS_LOG_INFO,__func__,__LINE__,__VA_ARGS__)

#if (DEBUG_MODE == 0)
#define  LOGD(...) \
           NBUS_PrintMessage(NODEBUS_LOG_DEBUG,__func__,__LINE__,__VA_ARGS__)
#else
#define LOGD(...)
#endif

#define  LOGV(...) \
           NBUS_PrintMessage(NODEBUS_LOG_VERBOSE,__func__,__LINE__,__VA_ARGS__)

void NBUS_PrintMessage(int type, const char *func, int line, const char *fmt, ...);

#endif
