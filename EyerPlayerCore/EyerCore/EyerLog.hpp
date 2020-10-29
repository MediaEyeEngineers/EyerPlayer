#ifndef	EYER_LIB_LOG_H
#define	EYER_LIB_LOG_H

#define EYER_LOG_LEVEL_ERROR 1
#define EYER_LOG_LEVEL_INFO 2
#define EYER_LOG_LEVEL_WARNING 3

#ifdef EYER_PLATFORM_ANDROID
// #define BaseEyerLog(format, ...) printf(format, ##__VA_ARGS__)

#include <android/log.h>
#define LOG_TAG "EyerWand"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define EyerLog(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define BaseEyerLog(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#else
#define EyerLog(format, ...) EyerPrintf(__FILE__, __FUNCTION__ ,__LINE__, 2, format, ##__VA_ARGS__)
#define BaseEyerLog(format, ...) printf(format, ##__VA_ARGS__)
#endif


void EyerPrintf(const char * file, const char * function, int line, int level, const char * _format, ...);

#endif