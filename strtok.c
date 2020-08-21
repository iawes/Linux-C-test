/*===============================================================
*   文件名称：strtok.c
*   创建日期：2016年08月02日
================================================================*/
#include <string.h>
#include <stdio.h>
int main()
{
  char *p;
  char *buffer;
  char *delims={ " .," };

  buffer=strdup("Find words, all of them.");
  printf("%s\n",buffer);
  p=strtok(buffer,delims);
  while(p!=NULL){
    printf("word: %s\n",p);
    p=strtok(NULL,delims);
  }
  printf("%s\n",buffer);
  return 0;
}

