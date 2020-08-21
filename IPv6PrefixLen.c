#include <stdio.h>
#include <stdlib.h>

typedef struct _dbus_wanConnectionInfo
{
    char index[16];
    char IfName[32];    
    char LanInterface[512];
    char ConnectionType[32];
    char VLANIDMark[64];
    char PRI8021pMark[64];
    char IPMode[64];
    char ConnectionStatus[32];
    char ExternalIPAddress[32];
    char SubnetMask[32];
    char DefaultGateway[32];
    char DNS1[32];
    char DNS2[32];
    char IPv6ConnStatus[32];
    char IPv6IPAddress[40];
    char IPv6IPrefixLength[8];
    char IPv6DefaultGateway[40];
    char IPv6DNS1[40];
    char IPv6DNS2[40];
    char IPv6Prefix[40];
    unsigned long int RxBytes; 
    unsigned long int TxBytes; 
    unsigned long int RxPkts; 
    unsigned long int TxPkts; 
}dbus_wanConnectionInfo;


static void api_convertIPv6Prefix(char *vpIPv6Prefix, dbus_wanConnectionInfo *vpWanIfInfo)
{
    //3ffe:501:ffff:2000::/56

    if(EOF == sscanf(vpIPv6Prefix, "%[^/]/%[^ ]", vpWanIfInfo->IPv6Prefix, vpWanIfInfo->IPv6IPrefixLength))
    {
        printf("read IPv6Prefix and IPv6IPrefixLength from  \"%s\" error.\n", vpIPv6Prefix);
        
        return ;
    }
    
    return ;
}

int main()
{
    dbus_wanConnectionInfo wanIfInfo;
    memset(&wanIfInfo, 0, sizeof(wanIfInfo));
    
    char *str = "";
    
    api_convertIPv6Prefix(str, &wanIfInfo);
    
    printf("IPv6Prefix = %s\t IPv6IPrefixLength = %s\n", wanIfInfo.IPv6Prefix, wanIfInfo.IPv6IPrefixLength);
    
    return 0;
}