#include <stdio.h>

#define BUS_RET_SUCCESS                    (0)
#define BUS_RET_FAILED                     (-1)

// 描述:execmd函数执行命令，并将结果存储到result字符串数组中 
// 参数:cmd表示要执行的命令
// result是执行的结果存储的字符串数组
// 函数执行成功返回1，失败返回0  
int api_exeCmdtoString(char *vpCmd, char *vpResult, int vLen) 
{
    char buffer[128] = {0};
    int len = 0;
    
    FILE* pipe = popen(vpCmd, "r");    
    if (NULL == pipe)
    {
         return BUS_RET_FAILED;  
    }                            
        
    while(!feof(pipe)) 
    {
        if(NULL != fgets(buffer, sizeof(buffer), pipe))
        {         
            len += strlen(buffer);
            
            if(len >= vLen)
            {      
                printf("len=%d >= vLen=%d.\n", len, vLen);
                return BUS_RET_FAILED;
            }
            
            strcat(vpResult, buffer);
        }
    }
    
    pclose(pipe);
    
    return BUS_RET_SUCCESS;
}

int api_extractStatisticsFromCmd(const char *vpCmd, unsigned long *vpUsStats, unsigned long *vpDsStats)
{
    char usStr[64] = {0};
    char dsStr[64] = {0};

    //"          RX bytes:884786511 (843.7 MiB)  TX bytes:413554232 (394.3 MiB)"
    if(EOF == sscanf(vpCmd,
                "%*[]+ %*[^ ] %*[^ ] %[^ ] %*[^ ] %*[^ ] %*[^ ] %[^ ] %*[^ ] %*[^\n]",
                dsStr,
                usStr))
    {
        printf("read from  \"%s\" error.\n", vpCmd);
        return BUS_RET_FAILED;
    }
    
    if(EOF == sscanf(dsStr,
                "%*[^:]:%d[^\n]",
                vpDsStats))
    {
        printf("read from  \"%s\" error.\n", dsStr);
        return BUS_RET_FAILED;
    }
    
    if(EOF == sscanf(usStr,
                "%*[^:]:%d[^\n]",
                vpUsStats))
    {
        printf("read from  \"%s\" error.\n", usStr);
        return BUS_RET_FAILED;
    }    
    
    printf("dsStr=%s, usStr=%s.\n", dsStr, usStr);
    
    return BUS_RET_SUCCESS;
}

static int api_getIfconfigStatsbyIfName(char *vpWanIfName, unsigned long *vpUsStats, unsigned long *vpDsStats)
{
    char result[128] = {0};
    char cmd[128] = {0};
    
    snprintf(cmd, sizeof(cmd), "ifconfig %s |grep bytes", vpWanIfName);
    printf("cmd=%s\n", cmd);
    
    if(BUS_RET_SUCCESS != api_exeCmdtoString(cmd, result, sizeof(result)))
    {
       printf("call api_exeCmdtoString failed!\n");
       return BUS_RET_FAILED;
    }
    
    if(BUS_RET_SUCCESS != api_extractStatisticsFromCmd(result, vpUsStats, vpDsStats))
    {
        printf("call api_extractStatisticsFromCmd failed!\n");
        return BUS_RET_FAILED;
    }
    
    return BUS_RET_SUCCESS;
}

static int api_getWanIfName(int vIndex, char *vpWanIfName, int vlen)
{
    strncpy(vpWanIfName, "eth3", vlen-1);

    printf("find the %d wan ifname is %s.\n", vIndex, vpWanIfName);

    return BUS_RET_SUCCESS;
}


static int api_getWanIfStatsInt(int vWanIndex, unsigned long *vpUsStats, unsigned long *vpDsStats)
{
    char wanIfName[32] = {0};

    int ret = BUS_RET_SUCCESS;
    ret = api_getWanIfName(vWanIndex, wanIfName, sizeof(wanIfName));
    if(BUS_RET_SUCCESS != ret)
    {
        printf("call api_getWanIfName failed!\n");
        return BUS_RET_FAILED;
    }

    ret = api_getIfconfigStatsbyIfName(wanIfName, vpUsStats, vpDsStats);
    if(BUS_RET_SUCCESS != ret)
    {
        printf("call api_getIfconfigStatsbyIfName failed!\n");
        return BUS_RET_FAILED;
    }
    
    return BUS_RET_SUCCESS;
}

typedef struct {
    char UsStats[32];
    char DsStats[32];
} api_WanIfStats_t;

static int api_getWanIfStats(int vWanIndex, api_WanIfStats_t *vpWanIfStats)
{
    unsigned long ulUsStats = 0;
    unsigned long ulDsStats = 0;

    int ret = BUS_RET_SUCCESS;

    ret = api_getWanIfStatsInt(vWanIndex, &ulUsStats, &ulDsStats);
    if(BUS_RET_SUCCESS != ret)
    {
        printf("call api_getWanIfStatsInt failed!\n");
        return BUS_RET_FAILED;
    }

    snprintf(vpWanIfStats->UsStats, sizeof(vpWanIfStats->UsStats), "%lu", ulUsStats);
    snprintf(vpWanIfStats->DsStats, sizeof(vpWanIfStats->DsStats), "%lu", ulDsStats);

    return BUS_RET_SUCCESS;
}

int main()
{
    unsigned long long int us = 0, ds = 0;
    int ret = 0;

    ret = api_getIfconfigStatsbyIfName("eth3", &us, &ds);
    if(0 != ret)
    {
        printf("call api_getIfconfigStatsbyIfName failed!\n");
        return -1;        
    }
    
    printf("us=%d, ds=%d.\n", us, ds);
    
    
    api_WanIfStats_t wanIfStats;
    memset(&wanIfStats, 0, sizeof(wanIfStats));

    ret = api_getWanIfStats(3, &wanIfStats);
    if(BUS_RET_SUCCESS != ret)
    {
        printf("call api_getWanIfStats failed!\n");

        return BUS_RET_FAILED;
    }

    printf("wanIfStats:us=%s, ds=%s.\n", wanIfStats.UsStats, wanIfStats.DsStats);
    
    return 0;
} 