#include <string.h> 
#include <stdio.h> 

static int api_findComma(const char *vpString)
{
    unsigned int pos;

    char *p = NULL;

    p = strchr(vpString, ',');
    if(NULL == p)
    {
        pos = 0;
    }
    else
    {
        pos = p - vpString;
    }

    return pos;
}

int main(void) 
{ 
   char *ptr; 
   const char *string = "   abcde";
   unsigned int pos = 0;
   char *dns = "8.8.8.8,8.8.4.4";
   
   ptr = strrchr(string, ' '); 
   if (ptr) 
      printf("The character ' ' is at position: %d, result:%s\n", strlen(ptr+1), ptr+1); 
   else 
      printf("The character was not found\n"); 
  
    pos = api_findComma(dns);
    
    printf("pos is %d!\n", pos);
    printf("dns2 is %s\n", dns+pos);
    
    char *tmp="abc 123,ABC"; 
                
    printf("hello %s\n","world",
    "you are %s\n",   
    "mine");
  
   return 0; 
}
