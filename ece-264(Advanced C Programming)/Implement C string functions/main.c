#include <stdio.h>
#include <stdlib.h>
#include "answer02.h"
#include "answer02.c"

int main(int argc, char * * argv)
{
   printf("Hello World!\n");
   int count=0;
   const char* str= "Hello World!";
   count=my_strlen(str);
   printf("The length of the string %s is %d.\n",str,count);
   // Create your test-cases here, good luck!
   return 0;
}
