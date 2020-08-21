/*===============================================================
*   文件名称：uptime.c
*   创建日期：2019年06月27日
================================================================*/
#include <stdio.h>

int main()
{
    FILE *fp = NULL;
//fp = fopen("uptime.c", "r");
    fp = fopen("/proc/uptime", "r");
    if(fp == NULL)
    {
        printf("open file failed!\n");
        return 0;
    }
    // 分别保存两个数，长度要比文件中数略大
    // 可以使用cat /proc/uptime提前查看一下
    char t[20];
    char u[20];
    fscanf(fp, "%s %s", t, u);
    printf("%s %s\n", t, u);

    // 统计第一个数的整数位个数，并且转成long，省略第2个数处理
   unsigned long dt = 0;
    int i;
    for(i=0; i<20; i++)
    {
        if(t[i] == '.')
            break;
    }
    int j = 1;
    for(i--; i>=0; i--)
    {
        dt += (t[i]-'0') * j;
        j *= 10;
    }

    // long转date 并输出
    unsigned long day, hour, minute, second;
    day = dt / (60*60*24);
    dt = dt % (60*60*24);
    hour = dt / (60*60);
    dt = dt % (60*60);
    minute = dt / 60;
    second = dt % 60;

    printf("%ld:%ld:%ld:%ld\n", day, hour, minute, second);

    fclose(fp);
    return 0;
}
