
/*
#include <iostream>

int main()
{
	printf("Hiiiiii...");
	system("pause");
	return 0;
}
*/



#include <iostream>
#include <stdio.h>
#include "example_dll.h"

int main(void)
{
        hello("World");
        printf("%d\n", Double(333));
        CppFunc();

        MyClass a;
        a.func();

        return 0;
}

