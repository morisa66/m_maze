#ifndef __M_LOG_H__
#define __M_LOG_H__


#include <fstream>
#include <time.h> 

#include "../_morisa.h"

#ifdef USE_CONCURRENCY
#include <mutex>
using std::mutex;
using std::lock_guard;
mutex mtx;
#endif 

MORISA_NAMESPACE_BEGIN

template <typename T>
bool m_log(const T& info, bool is_show_time = true, bool is_end_line = true)
{
	using std::endl;
#ifdef USE_CONCURRENCY
	lock_guard<mutex> m_mtx(mtx);
#endif 
	std::ofstream log(LOG_PATH, std::ios::app);
	if (!log.is_open()) return false;
	if (is_show_time)
	{
		time_t cur;
		time(&cur);
		log << endl << ctime(&cur);
	}
	log << info;
	if (is_end_line)
	{
		log << endl;
	}
	log.close();
	return true;
}


MORISA_NAMESPACE_END

#endif

