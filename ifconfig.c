/*===============================================================
*   文件名称：ifconfig.c
*   创建日期：2016年08月16日
================================================================*/
#include "stdio.h"

#define BUS_RET_SUCCESS                    (0)
#define BUS_RET_FAILED                     (-1)

static int api_getWanMac(const char *vpWanIfName, char *vpMacAddress)
{
    int ret = BUS_RET_SUCCESS;
    char cmd[64] = {0};
    char result[128] = {0};

    snprintf(cmd, sizeof(cmd), "ifconfig %s|grep HWaddr", vpWanIfName);

    FILE *pStream = NULL;
    pStream = popen(cmd, "r");
    if(NULL == pStream)
    {
        printf("run \"%s\" failed!\n", cmd);
        return BUS_RET_FAILED;
    }

    if(fread(result, sizeof(char), sizeof(result), pStream) == 0)
    //if (fgets(result, sizeof(result), pStream) == NULL)
    {
        printf("fgets failed!\n");
        pclose(pStream);
        pStream = NULL;
        return BUS_RET_FAILED;
    }
    
    printf("result:\n%s\n", result);

    //result like this:
    //pon_3_0_1      Link encap:Ethernet  HWaddr 00:01:02:03:0A:10
    if(EOF == sscanf(result, "%*[^ ] %*[^ ] %*[^ ] %*[^ ] %[^\n]", vpMacAddress))
    {
        printf("read MAC from  \"%s\" error.\n", result);

        pclose(pStream);
        pStream = NULL;
        return BUS_RET_FAILED;
    }

    pclose(pStream);
    pStream = NULL;
    return BUS_RET_SUCCESS;
}

int main(void)
{
    char *ifEth = "";
    char MAC[32] = {0};

    int ret = BUS_RET_SUCCESS;

    ret = api_getWanMac(ifEth, MAC);
    if(BUS_RET_SUCCESS != ret)
    {
        printf("call api_getWANMAC failed\n");
        return -1;
    }
	
	printf("MAC is %s\n", MAC);

    return 0;
}

