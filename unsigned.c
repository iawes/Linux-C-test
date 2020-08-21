/*===============================================================
*   文件名称：unsigned.c
*   创建日期：2019年08月01日
================================================================*/
#include "stdio.h"

int main(void)
{
    unsigned int a = 1;
    long b = 0;
    
    printf("unsigned int len:%d, long len:%d.\n", sizeof(a), sizeof(b));
    printf("a:%d, b:%ld.\n", a, b);
    
    unsigned int c = 2147483649;
    long d = (long)c;
    long e = 56%0x7fffffff;
    long f = 0xffffffff;
    long g = 0x7fffffff;
    printf("c:%u, d:%ld.\n", c, d);
    printf("c:%u, e:%ld.\n", c, e);
    printf("f:%ld, g:%ld.\n", f, g);
    
    return 0;
}
