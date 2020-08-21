/*===============================================================
*   文件名称：gets.c
*   创建日期：2016年08月03日
================================================================*/
#include <stdio.h>

 int main()
 {
     char filename[] = "/tmp/route_ipv4.log"; //文件名
     FILE *fp;
     char StrLine[1024];             //每行最大读取的字符数
     if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
     {
         printf("error!");
         return -1;
     }

     while (!feof(fp))
     {
         fgets(StrLine,1024,fp);  //读取一行
         printf("%s\n", StrLine); //输出
     }
     fclose(fp);                     //关闭文件
     return 0;
 }
