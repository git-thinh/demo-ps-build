#ifndef _____MSG_PUBLISH_H
#define _____MSG_PUBLISH_H

#include "mingw.thread.h"
#include <mutex>
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"

#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <map>

class ___msgPublish
{
// [ SINGLETON ]
public:
	static ___msgPublish& getInstance()
	{
		static ___msgPublish    instance;
		return instance;
	}
private:
	___msgPublish() { init(); }
	~___msgPublish() { close(); }
public:
	___msgPublish(___msgPublish const&) = delete;
	void operator=(___msgPublish const&) = delete;
//end [ SINGLETON ]

private:	
	std::queue<char*> m_MSG;
	std::vector<void*> m_Subscribe;
	
	// HANDLE m_pipeHandle;
	// bool m_pipeOpen;

	std::mutex m_mutexMsgReceiver;
	std::condition_variable m_notificationMsgReceiver;

	std::thread m_thread;
	std::vector<const char*> m_Items; 

	///////////////////////////////////////
	void init() ;

	void close() ;
public:
	void join(void* pClient, const char* pName) ;

	void sendBroadcast(char* pData);

	void release() ;
};

#endif // !_____MSG_PUBLISH_H