//#include "mingw.thread.h"
#include <mutex>
//#include "mingw.mutex.h"
//#include "mingw.condition_variable.h"

#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <map>

#include "___msgPublish.h"
#include "___msgSubscribe.h"

void ___msgPublish::init()
{
	// m_pipeHandle = CreateNamedPipe(DEFINE_PIPENAME, PIPE_ACCESS_INBOUND | PIPE_ACCESS_OUTBOUND, PIPE_WAIT, 1, 1024, 1024, 120 * 1000, NULL);
	// m_pipeOpen = true;
	// if (m_pipeHandle == INVALID_HANDLE_VALUE)
	// {
	// 	m_pipeOpen = false;
	// 	printf("Error: %d", GetLastError());
	// }

	m_thread = std::thread([](std::mutex &_mutexMsgReceiver, std::condition_variable &_notificationMsgReceiver) {
		std::unique_lock<std::mutex> _lock(_mutexMsgReceiver);
		while (true)
		{
			_notificationMsgReceiver.wait(_lock);
			//std::cout << " _notificationMsgReceiver signal ..." << endl;
		}
	}, m_mutexMsgReceiver, m_notificationMsgReceiver);
	m_thread.detach();
}

void ___msgPublish::close()
{
	HANDLE hThread = m_thread.native_handle();
	CloseHandle(hThread);
	hThread = NULL;
}

void ___msgPublish::join(void *pClient, const char *pName)
{
	m_Subscribe.push_back(pClient);
	m_Items.push_back(pName);

	//m_Items.insert(pClient, pFunc);
	//std::cout << "registerSubscribe(): " << pName << " = " << pClient << endl;
}

void ___msgPublish::sendBroadcast(char *pData)
{
	//std::cout << "sendBroadcast(): " << m_Subscribe.size() << endl;
	//for (std::vector<void*>::iterator it = m_Subscribe.begin(); it != m_Subscribe.end(); ++it) {
	//	___msgSubscribeInterface* p = (___msgSubscribeInterface*)(*it);
	//	if (p != NULL) {
	//		p->m_pData = pData;
	//		p->Subscribe();
	//	}
	//}
	std::unique_lock<std::mutex> lk(m_mutexSubscribe);
	m_MSG.push(pData);
	char *pBufMsg = m_MSG.front();
	m_MSG.pop();
	// if(m_pipeOpen == true)
	// 	WriteFile(m_pipeHandle, pBufMsg, strlen(pBufMsg) + 1, NULL, NULL);
	delete pBufMsg; //?????????
	lk.unlock();
	m_notificationSubscribe.notify_all();
}

void ___msgPublish::release()
{
	// //std::cout << "release(): " << m_Subscribe.size() << endl;
	// for (std::vector<void*>::iterator it = m_Subscribe.begin(); it != m_Subscribe.end(); ++it) {
	// 	//___msgSubscribe* p = (___msgSubscribe*)*it;
	// 	void* p = *it;
	// 	if (p != NULL)
	// 		delete p;
	// }
}
