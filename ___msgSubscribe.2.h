
#ifndef _____MSGSUBSCRIBE
#define _____MSGSUBSCRIBE

#include "mingw.thread.h"
#include <mutex>
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"

#include <vector>
#include <thread>
#include <atomic>
#include <queue>
#include <map>

struct AtomicCounter {
	std::atomic<int> value;

	void increment() {
		++value;
	}

	void decrement() {
		--value;
	}

	int get() {
		return value.load();
	}
};

#define DEFINE_BUFSIZE 512
#define DEFINE_PIPENAME L"\\\\.\\pipe\\LogPipe"

std::mutex m_mutexSubscribe;
std::condition_variable m_notificationSubscribe;

///////////////////////////////////////////////////////////////

class ___msgSubscribeInterface
{
public:
	char* m_pData;
public:
	___msgSubscribeInterface() :m_pData(0) {}
	virtual ~___msgSubscribeInterface() {}
	virtual void Subscribe() = 0;
};

///////////////////////////////////////////////////////////////

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
	void init() {		
		// m_pipeHandle = CreateNamedPipe(DEFINE_PIPENAME, PIPE_ACCESS_INBOUND | PIPE_ACCESS_OUTBOUND, PIPE_WAIT, 1, 1024, 1024, 120 * 1000, NULL);
		// m_pipeOpen = true;
		// if (m_pipeHandle == INVALID_HANDLE_VALUE)
		// {
		// 	m_pipeOpen = false;
		// 	printf("Error: %d", GetLastError());
		// }

		m_thread = std::thread([](std::mutex& _mutexMsgReceiver, std::condition_variable& _notificationMsgReceiver) {
			std::unique_lock<std::mutex> _lock(_mutexMsgReceiver);
			while (true) {
				_notificationMsgReceiver.wait(_lock);
				//std::cout << " _notificationMsgReceiver signal ..." << endl; 
			}
		}, m_mutexMsgReceiver, m_notificationMsgReceiver);
		m_thread.detach();
	}

	void close() {
		HANDLE hThread = m_thread.native_handle(); 
		CloseHandle(hThread);
		hThread = NULL;	
	}
public:
	void join(void* pClient, const char* pName) {
		m_Subscribe.push_back(pClient);
		m_Items.push_back(pName);
		
		//m_Items.insert(pClient, pFunc); 
		//std::cout << "registerSubscribe(): " << pName << " = " << pClient << endl;
	}

	void sendBroadcast(char* pData) {
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
		char* pBufMsg = m_MSG.front();
		m_MSG.pop();
		// if(m_pipeOpen == true) 
		// 	WriteFile(m_pipeHandle, pBufMsg, strlen(pBufMsg) + 1, NULL, NULL);
		delete pBufMsg; //?????????
		lk.unlock();
		m_notificationSubscribe.notify_all();
	}

	void release() {
		// //std::cout << "release(): " << m_Subscribe.size() << endl;
		// for (std::vector<void*>::iterator it = m_Subscribe.begin(); it != m_Subscribe.end(); ++it) {
		// 	//___msgSubscribe* p = (___msgSubscribe*)*it;
		// 	void* p = *it;
		// 	if (p != NULL)
		// 		delete p;
		// }
	}
};

///////////////////////////////////////////////////////////////

template <typename T>
class ___msgSubscribe : public ___msgSubscribeInterface
{
private:
	typedef void (T::*PTR_METHOD_SUBSCRIBE)(T*);
	PTR_METHOD_SUBSCRIBE m_pMethodSubscribe;
	T* m_pClass;
	std::thread m_thread;
public:
	___msgSubscribe() {
		//m_pMethodSubscribe = NULL;
		//m_pClass = NULL;
		//m_thread = 0;
	};
	~___msgSubscribe() {
		HANDLE hThread = m_thread.native_handle();
		//DWORD dwExit;
		//// actually wait for the thread to exit
		//WaitForSingleObject(hThread, WAIT_INFINITE);
		//// get the thread's exit code (I'm not sure why you need it)
		//GetExitCodeThread(hThread, &dwExit);
		// cleanup the thread
		CloseHandle(hThread);
		hThread = NULL;
	};

	virtual void TaskMsgReceiver(T* pClass) = 0;

	void registerSubscribe(T* pClass, PTR_METHOD_SUBSCRIBE pMethodSubscribe)
	{
		m_pClass = pClass;
		m_pMethodSubscribe = pMethodSubscribe;

		___msgPublish::getInstance().join(pClass, &(typeid(pClass).name()[5]));

		m_thread = std::thread([](T* _pClass, PTR_METHOD_SUBSCRIBE _pMethodSubscribe) {
			std::unique_lock<std::mutex> lk(m_mutexSubscribe);
			while (true) {
				m_notificationSubscribe.wait(lk);
				//std::cout << " receiver signal ..." << endl;
				(_pClass->*_pMethodSubscribe)(_pClass);
			}
		}, m_pClass, m_pMethodSubscribe);
		m_thread.detach();
	}

	void Subscribe() {
		//(m_pClass->*m_pMethodSubscribe)(m_pClass); 
	}
};

#endif // !_____MSGSUBSCRIBE
