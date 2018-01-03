#include "___msgSubscribe.h"
#include <iostream>

class _testClass : public ___msgSubscribe<_testClass>
{
private:
public:
	~_testClass() { }
	_testClass() {
		//std::cout << "_testClass(): " << this << endl;
		registerSubscribe(this, &_testClass::TaskMsgReceiver);
	}

	void TaskMsgReceiver(_testClass* pClass) {
		std::cout << "_testClass.TaskMsgReceiver() = ";
		if (pClass->m_pData != NULL)
			std::cout << pClass->m_pData << std::endl;
		else
			std::cout << std::endl;
	}
	
	void funA() {
		std::cout << " funA() ";
	}
};
