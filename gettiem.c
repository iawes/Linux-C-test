/*===============================================================
*   文件名称：gettiem.c
*   创建日期：2016年06月22日
================================================================*/
#include <stdio.h>
#include <time.h>

int libutil_getPONIfUpTime(int *vptime)
{
    time_t upTime = 0;

    FILE *f = fopen("/home/yaweili/test/o5time.log", "r");

    if(NULL != f)
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t r = 0;


        r = getline(&line, &len, f);
        if(-1 == r)
        {
            return -1;
        }

        if(NULL != line)
        {
            upTime = atoi(line);

            free(line);
            line = NULL;
        }
    }

    fclose(f);

    time_t curTime = 0;
    time(&curTime);

    *vptime = curTime - upTime;

    return 0;
}


int main(void)
{
    time_t timep = 0;
    time_t timeq = 0;
    struct tm *p;
    int uptime = 0;

    time(&timep);

    printf("%s\n", asctime(gmtime(&timep)));

    printf("%s\n",ctime(&timep));

    printf("time(): %d\n", timep);

    p = localtime(&timep);
    timep = mktime(p);
    printf("mktime(): %d\n", timep);

    char cmd[128] = {0};
    snprintf(cmd, sizeof(cmd)-1, "echo %d > /home/yaweili/test/o5time.log", timep);
    system(cmd);

    FILE *f = fopen("/home/yaweili/test/o5time.log", "r");

    if(f)
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t r = 0;

        getline(&line, &len, f);


        if(line)
        {
            printf("line: %s", line);
            free(line);
            line = NULL;
        }
    }

    fclose(f);

    sleep(5);

    libutil_getPONIfUpTime(&uptime);

    printf("time; %d\n", uptime);

    return 0;
}
