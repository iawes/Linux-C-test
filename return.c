/*===============================================================
*   文件名称：return.c
*   创建日期：2016年08月12日
================================================================*/
#include <stdio.h>
char *api_getDHCPEnableStatus(int vDHCPStatus)
{
    if(vDHCPStatus)
    {
        return "TRUE";
    }

    return "FALSE";
}

int main()
{
    printf("%s\n", api_getDHCPEnableStatus(1));

    return 0;
}
