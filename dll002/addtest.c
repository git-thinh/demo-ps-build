/* addtest.c

   Demonstrates using the function imported from the DLL, in a flexible and
   elegant way.
*/

#include <stdlib.h>
#include <stdio.h>
#include "add.h"

int main(int argc, char** argv)
{
  printf("%d\n", Add(6, 23));

  return 0;
}