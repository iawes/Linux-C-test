#include <stdio.h>

int main()
{
#include <string.h> 
#include <stdio.h> 

int main(void) 
{ 
   char string[30] = {0}; 
   char *ptr, c = 'r'; 

   strcpy(string, "This is a string"); 
   ptr = strrchr(string, c); 
   if (ptr) 
      printf("The character %c is at position: %d, result:%s\n", c, ptr-string, ptr); 
   else 
      printf("The character was not found\n"); 
   return 0; 
}
    
}
