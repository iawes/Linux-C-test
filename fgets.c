/*===============================================================
*   文件名称：fgets.c
*   创建日期：2016年08月03日
================================================================*/
#include <stdio.h>

int main()
{
    FILE *fp = NULL;

    fp = fopen("/tmp/route_ipv4.log", "r");
    if(NULL == fp)
    {
        printf("call fopen error!\n");
        return -1;
    }

    int lineNum = 0;
    while(!feof(fp))
    {
        //if(0x2 > lineNum)
        //{
        //    lineNum ++;
        //    continue;
        //}

        char line[1024] = {0};
        if(NULL == fgets(line, 1024, fp));
        {
            printf("call fgets error!\n");
        //    fclose(fp);
        //    return -1;
        }

        printf("%s\n", line);
    }

    fclose(fp);

    return 0;
}
