#include "_testClass.hpp"
#include "___msgPublish.h"
#include <iostream>

int _tmain(int argc, char* argv[])
{ 
	_testClass* p1 = new _testClass;
	_testClass* p2 = new _testClass;
    p1->funA();
    p2->funA();

	___msgPublish::getInstance().sendBroadcast("1");
	//___msgPublish::getInstance().sendBroadcast("2");
	//___msgPublish::getInstance().sendBroadcast("3");
	//___msgPublish::getInstance().sendBroadcast("4");
	//___msgPublish::getInstance().sendBroadcast("5");

	std::string a;
	while (a != "exit") {
		std::cin >> a;
		___msgPublish::getInstance().sendBroadcast((char*)a.c_str());
	} 

	___msgPublish::getInstance().release();
	   
	return 0;
}
