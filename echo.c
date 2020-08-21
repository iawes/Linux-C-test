/*===============================================================
*   文件名称：echo.c
*   创建日期：2017年08月02日
================================================================*/
#include "stdio.h"
#include "unistd.h"
#include "string.h"

#define UPGRADE_MSG_FILE "upgrade_msg.txt"

void plug_write_upgrade_response_Json(char *vpUpgradeJson)
{
    char cmd[3072] = {0};

    snprintf(cmd, sizeof(cmd), "echo \'%s\' >> %s", vpUpgradeJson, UPGRADE_MSG_FILE);

    system(cmd);

    return ;
}

#define SPC_UPGRADE_PATH "/repo/yaweili/1521_5401China/apps/private/appkgs/smartpltclient/build/plugin"

void plug_get_spc_upgrade_version(char *vpVersion, int vLen)
{
    char infoPath[128] = {0};

    snprintf(infoPath, sizeof(infoPath), "%s%s", SPC_UPGRADE_PATH, "/Info.plugin");

    if(0 != access(infoPath, F_OK))
    {
        printf("%s does not exist!\n", infoPath);
        return ;
    }

    char cmd[256] = {0};

    snprintf(cmd, sizeof(cmd), "grep \'^Version\' %s | awk -F \':\' \'{print $2}\'", infoPath);

    FILE *fpRead = NULL;
    fpRead = popen(cmd, "r");
    if(NULL == fpRead)
    {
        printf("popen failed!\n");
        return ;
    }

    char tmp[256] = {0};
    while (NULL != fgets(tmp, sizeof(tmp), fpRead))
    {
        if(tmp[strlen(tmp)-1] = '\n')
        {
            tmp[strlen(tmp)-1] = '\0';
        }

        strncpy(vpVersion, tmp, vLen-1);
    }

    pclose(fpRead);
    fpRead=NULL;

    return ;
}

int main(void)
{
    char *pJson = "{\"hostMAC\":[\"10:2f:6b:a6:86:e6\"]}";

    printf("Json = %s.\n", pJson);

    plug_write_upgrade_response_Json(pJson);

    char version[64] = {0};
    plug_get_spc_upgrade_version(version, sizeof(version));
    printf("version = %s\n", version);

    return 0;
}
