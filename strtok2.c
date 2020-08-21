#include <stdio.h>
#include <string.h>


int main(void)
{
   char ID[]="0001,004,0005,08,000009";
   char *p;
   char LanInterface[8][128] = {0};
   int num = 0;

   p = strtok(ID, ",");
   while (p && (8 > num))
   {
	   printf("%s\n", p);
	   strncpy(LanInterface[num], p, sizeof(LanInterface[num])-1);
	   p = strtok(NULL, ",");
	   num ++;
   }
   
   int loop = 0;
   for(loop=0; loop<num; loop++)
   {
		printf("LanInterface[%d] = %s\n", loop, LanInterface[loop]);
   }   
   
   return 0;
} 