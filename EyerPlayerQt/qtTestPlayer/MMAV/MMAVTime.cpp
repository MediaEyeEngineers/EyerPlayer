#include "MMAV.h"

#include <chrono>

/*
* 获取当前的时间戳 
* 单位ms
*/
long long MMAVTime::getTime()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	return (long long)tmp.count();
}