/* add_vartest.c

   Demonstrates using the function and variables exported by our DLL.
*/

#include <stdlib.h>
#include <stdio.h>

/* Don't forget to change this to #include <add.h> for real applications where
   the header has been deployed to a standard include folder!
*/
#include "add_var.h"

int main(int argc, char** argv)
{
  /* foo + bar = Add(foo, bar) */
  printf("%d + %d = %d\n", foo, bar, Add(foo, bar));

  return 1;
}