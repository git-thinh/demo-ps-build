#ifdef MY_COMPILE_DLL
#define MY_DECLSPEC __declspec(dllexport)
#else
#define MY_DECLSPEC __declspec(dllimport)
#endif

class MY_DECLSPEC TestInterface
{
public:
   TestInterface() ;
   virtual ~TestInterface() = 0 ;
   virtual bool Get(bool &flag, int &num) = 0 ;
} ;

typedef TestInterface* (*newtestdlltype)(const bool, const int) ;
typedef void (*deletetestdlltype)(TestInterface *) ;

TestInterface* MY_DECLSPEC newtestdll(const bool, const int) ;
void MY_DECLSPEC deletetestdll(TestInterface*) ;