#ifndef _____MSG_SUBSCRIBE_H
#define _____MSG_SUBSCRIBE_H

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

#endif // !_____MSG_SUBSCRIBE_H
