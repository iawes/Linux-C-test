/*===============================================================
*   文件名称：route.c
*   创建日期：2016年08月03日
================================================================*/
#include <stdio.h>
static void writeRouteToLog()
{
    char *cmd = "route -n > /tmp/route_ipv4.log";
    char *cmdInet6 = "route -n -A inet6 > /tmp/route_ipv6.log";

    system(cmd);
    system(cmdInet6);

    return;
}

#define MAX_CURRENT_ROUTE_NUM   (32)
#define MAX_ROUTE_LEN           (1024)

static int getRouteFromLog(char *vpFileName, unsigned int *vNum, char (*vppRouteArr)[MAX_ROUTE_LEN])
{
    int ret = 0;

    if((NULL == vpFileName) || (NULL == vNum) || (NULL == vppRouteArr))
    {
        printf("input para error!\n");
        return -1;
    }

    unsigned int maxNum = *vNum;
    *vNum = 0;

    FILE *fp = NULL;

    fp = fopen(vpFileName, "r");
    if(NULL == fp)
    {
        printf("cant open file %s!\n", vpFileName);
        return -1;
    }

    int lineNum = 0;
    while(!feof(fp))
    {
        if(0x2 > lineNum)
        {
            lineNum ++;
            continue;
        }

        fgets(vppRouteArr[*vNum], MAX_ROUTE_LEN, fp);

        (*vNum) ++;

        if(MAX_CURRENT_ROUTE_NUM < *vNum)
        {
            printf("route num is greater than 32!\n");
            break;
        }
    }

    fclose(fp);

    return 0;
}

int main(void)
{
    writeRouteToLog();

    int ret;
    char currentRouteArr[MAX_CURRENT_ROUTE_NUM][MAX_ROUTE_LEN] = {0};
    unsigned int routeNum = MAX_CURRENT_ROUTE_NUM;
    char *file = "/tmp/route_ipv4.log";

    writeRouteToLog();

    ret = getRouteFromLog(file, &routeNum, currentRouteArr);
    if(0 != ret)
    {
        return ret;
    }

    unsigned int loop = 0;
    for(loop=0; loop<routeNum; loop++)
    {
        printf("%d: %s", loop, &currentRouteArr[loop]);
    }

    char DestIPAddress[32] = {0};
    char DestSubnetMask[32] = {0};
    char GatewayIPAddress[32] = {0};
    char Interface[256] = {0};

    sscanf((char *)&currentRouteArr[2],
            "%[^ ] %[^ ] %[^ ] %*[^ ] %*[^ ] %*[^ ] %*[^ ] %[^\n]",
            DestIPAddress,
            DestSubnetMask,
            GatewayIPAddress,
            Interface);

    printf("\nDestIPAddress=%s\nDestSubnetMask=%s\nGatewayIPAddress=%s\nInterface=%s\n",
            DestIPAddress,
            DestSubnetMask,
            GatewayIPAddress,
            Interface);

    return 0;
}
