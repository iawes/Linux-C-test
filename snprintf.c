/*===============================================================
*   文件名称：snprintf.c
*   创建日期：2016年06月21日
================================================================*/
#include <stdio.h>

int main()
{
    unsigned long long a = 0;
    char DsStats[32] = {0};

    memset(DsStats, 0, sizeof(DsStats));
    snprintf(DsStats, sizeof(DsStats) - 1, "%llu", a);
    printf("DsStats: %10d %s\n", a, DsStats);

    a = 2141514320;
    memset(DsStats, 0, sizeof(DsStats));
    snprintf(DsStats, sizeof(DsStats) - 1, "%llu", a);
    printf("DsStats: %llu %s\n", a, DsStats);

    int b = 2141514320;
    memset(DsStats, 0, sizeof(DsStats));
    snprintf(DsStats, sizeof(DsStats) - 1, "%d", b);
    printf("DsStats: %10d %s\n", b, DsStats);

    int c = 8;
    memset(DsStats, 0, sizeof(DsStats));
    snprintf(DsStats, sizeof(DsStats) - 1, "hello%d", c);
    printf("DsStats: %s\n", DsStats);

    return 0;
}
