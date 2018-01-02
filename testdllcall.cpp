#include <windows.h>
#include "testdll.h"

int main(void)
{
   bool bb ;
   int i, ii, numinstances=4 ;
   HMODULE testdll = LoadLibrary("libtestdll.dll") ;
   newtestdlltype ffunc_newtestdll =
            (newtestdlltype)GetProcAddress(testdll, "newtestdll") ;
   deletetestdlltype ffunc_deletetestdll =
            (deletetestdlltype)GetProcAddress(testdll, "deletetestdll") ;

   TestInterface **ftest = NULL ;
   ftest = new TestInterface*[numinstances] ;
   for (i=0; i<numinstances; i++) {
      ftest[i] = ffunc_newtestdll(i%2==0, i) ;
      ftest[i]->Get(bb, ii) ;
   }

   for (i=0; i<numinstances; i++) {
      ffunc_deletetestdll(ftest[i]) ;
      ftest[i] = NULL ;
   }
   delete [] ftest ;
   FreeLibrary(testdll) ;
   return 1 ;
}