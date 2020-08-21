/*===============================================================
*   文件名称：ntol.c
*   创建日期：2016年06月28日
================================================================*/
#include <stdio.h>
#include <arpa/inet.h>
int main(void)
{
    int x = 0x7A;
    int y = 774778450;
    int z = 808464506;
    int a = 1546661980;

    printf("x = %08d, %08x,  ntol = %08d, %08x\n", x, x, ntohl(x), ntohl(x));
    printf("y = %08d, %08x,  ntol = %08d, %08x\n", y, y, ntohl(y), ntohl(y));
    printf("y = %08d, %08x,  hton = %08d, %08x\n", y, y, htonl(y), ntohl(y));
    printf("z = %08d, %08x,  ntol = %08d, %08x\n", z, z, ntohl(z), ntohl(z));
    printf("a = %08d, %08x,  ntol = %08d, %08x\n", a, a, ntohl(a), ntohl(a));

    return 0;
}
