#define MY_COMPILE_DLL
#include "testdll.h"
#include <stdio.h>

TestInterface::TestInterface()
{
}

TestInterface::~TestInterface()
{
}

class MY_DECLSPEC Test : public TestInterface
{
    public:
      Test(const bool, const int);
      virtual ~Test();
      virtual bool Get(bool &flag, int &num);

    private:
      bool f_flag;
      int f_num;
      char f_text80[80];
};

Test::Test(const bool flag, const int num)
    : TestInterface(), f_flag(flag), f_num(num)
{
}

Test::~Test()
{
}

bool Test::Get(bool &flag, int &num)
{
      printf("Test::Get -- %d \n", f_num);

      flag = f_flag;
      num = f_num;
      return true;
}

TestInterface *newtestdll(const bool flag, const int num)
{
      return new Test(flag, num);
}

void deletetestdll(TestInterface *f)
{
      delete f;
}