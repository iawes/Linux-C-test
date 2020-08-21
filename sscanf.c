/*===============================================================
*   文件名称：sscanf.c
*   创建日期：2016年06月16日
================================================================*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned long   UINT32;
typedef unsigned long long UINT64;

#define MAX_INSTANCE_DEPTH 6

typedef struct
{
    UINT8 currentDepth;
    UINT32 instance[MAX_INSTANCE_DEPTH];
} InstanceId;

typedef struct {
    char status[64];
    char pppoeIP[64];
    char pppoeName[64];
    char cspeed[64];
    char aspeed[64];
    char bspeed[64];
    char maxspeed[64];
    char starttime[64];
    char endtime[64];
    char totalsize[64];
    char backgroundsize[64];
    char failcode[64];
} mbi_rstQuerySpeedtestStatOverTestserver_t;

int mbLib_parseUrl(const char *url, char *host, char *port)
{
    char tmp[256] = {0};
    int ret = 0;

    ret =  sscanf(url, "%*[^/]//%[^\n]", tmp);
    printf("sscanf ret = %d\n", ret);
        //return -1;

    ret = sscanf(tmp, "%[^:]:%[^\n]", host, port);
    printf("sscanf ret = %d\n", ret);
        //return -1;

    return 0;
}

static int getLanhostIidFromOID(char *vpOID, InstanceId *iid)
{
    printf("enter getLanhostIidFromOID().\n");
    if(NULL == vpOID || NULL == iid)
    {
        printf("input error.\n");
        return -1;
    }

    // like:  1/index/1
    iid->currentDepth = 2;

    int num = sscanf(vpOID, "%d/%d", &iid->instance[0], &iid->instance[1]);
	printf("iid num = %d.\n", num);
    if(0x02 != num)
    {
        printf("sscanf %s error.\n", vpOID);
        return -1;
    }

    printf("iid->instance[0] = %d, iid->instance[1] = %d.\n", iid->instance[0], iid->instance[1]);

    printf("end getLanhostIidFromOID().\n");

    return 0;
}

static void mbi_setSpeed(mbi_rstQuerySpeedtestStatOverTestserver_t *out)
{
    printf("bspeed: %s, cspeed: %s, aspeed: %s.\n", out->bspeed, out->cspeed, out->aspeed);

    int number = 0;

    int bspeed = 0;
    if(EOF == sscanf(out->bspeed, "%d[^.]", &bspeed))
    {
        printf("read from bspeed \"%s\" error.\n", out->bspeed);
    }

    srand((int)time(0));

    int cspeed = 0;
    number = (rand() % 11) - 5;
    cspeed = (bspeed * (100 + number)) / 100;

    int aspeed = 0;
    number = (rand() % 11) - 5;
    aspeed = (bspeed * (100 + number)) / 100;

    int dot = 0;

    dot = rand() % 100;
    snprintf(out->cspeed, sizeof(out->cspeed), "%d.%02d", cspeed, dot);

    dot = rand() % 100;
    snprintf(out->aspeed, sizeof(out->aspeed), "%d.%02d", aspeed, dot);

    printf("bspeed: %s, cspeed: %s, aspeed: %s.\n", out->bspeed, out->cspeed, out->aspeed);

    return ;
}

typedef struct
{
    //diagnosticsState_e DiagnosticsState;
    //testMode_e testMode;
    char downloadURL[256];
    char testURL[256];
    char reportURL[256];
    //status_e Status;
    char pppoeIP[128];
    char pppoeName[128];
    char Eupppoename[256];
    char Eupassword[256];
    char WANInterface[256];
    unsigned int cspeed;
    unsigned int aspeed;
    unsigned int bspeed;
    unsigned int maxspeed;
    char starttime[32];
    char endtime[32];
    unsigned int totalsize;
    unsigned int backgroundsize;
    int failcode;
} autoSpeedTest_t;

typedef struct
{
    unsigned int cspeed;
    unsigned int aspeed;
    unsigned int maxspeed;
    unsigned int totalsize;
    unsigned int backgroundsize;
} sample_report_t;

static void test_setSpeed(autoSpeedTest_t *st, sample_report_t *report)
{
    printf("st: bspeed: %d, cspeed: %d, aspeed: %d.\n", st->bspeed, st->cspeed, st->aspeed);
    printf("report: maxspeed: %d, cspeed: %d, aspeed: %d.\n", report->maxspeed, report->cspeed, report->aspeed);

    int number = 0;

    unsigned int bspeed = st->bspeed;

    srand((int)time(0));

    unsigned int cspeed = 0;
    number = (rand() % 11) - 5;
    cspeed = (bspeed * (100 + number)) / 100;

    unsigned int aspeed = 0;
    number = (rand() % 11) - 5;
    aspeed = (bspeed * (100 + number)) / 100;

    report->cspeed = cspeed;
    report->aspeed = aspeed;

    unsigned int maxspeed = 0;
    maxspeed = (cspeed>aspeed) ? cspeed:aspeed;

    number = rand() % 5 + 2;
    report->maxspeed = (maxspeed * (100 + number)) / 100;
    

    printf("bspeed: %d, cspeed: %d, aspeed: %d, maxspeed: %d.\n", st->bspeed, st->cspeed, st->aspeed, st->maxspeed);
    printf("bspeed: %d, cspeed: %d, aspeed: %d, maxspeed: %d.\n", st->bspeed, report->cspeed, report->aspeed, report->maxspeed);

    return ;
}

int main()
{
    char *string = "INTERNET_R_VID_100";

    int index = 0;

    sscanf(string, "%d", &index);

    printf("index = %d\n", index);

    char buf[]="port=5000";
    char key[100]="";
    char value[100]="";
    sscanf(buf,"%[^=]=%[^\n]",key,value);
    printf("key=%s\n",key);
    printf("value=%s\n",value);

    const  char wancon[] = "InternetGatewayDevice.WANDevice.1.WANConnectionDevice.5.WANIPConnection.1";
    char wan[32] = {0};
    char wana[32] = {0};

    index = 0;
//    sscanf(wancon, "%*[^.].%*[^.].%*[^.].%*[^.].%[^.].%[^.]", wan, wana);
//    printf("wan=%s\n",wan);
//    printf("wana=%s\n",wana);
    sscanf(wancon, "%*[^.].%*[^.].%*[^.].%*[^.].%d.%[^.]", &index, wana);
    printf("index=%d\n",index);
    printf("wana=%s\n",wana);


    char *url = "http://192.178.111.2:90";
    char host[256] = {0};
    char port[32] = {0};

    mbLib_parseUrl(url, host, port);

    printf("host=%s,port=%s\n", host, port);

	char OID[32] = "1/12/1";
    int index2 = 0;
    int num = sscanf(OID, "%*[^/]/%d/%*[^ ]", &index2);
	printf("num = %d, index = %d.\n", num, index2);

	char oid[] = "2/1";

	int ret = 0;
	InstanceId iid;
	memset(&iid, 0, sizeof(iid));
	ret = getLanhostIidFromOID(oid, &iid);
	if(0 != ret)
	{
		printf("call getLanhostIidFromOID failed.\n");
	}

    int index3 = 0;
    sscanf(wancon, "%*[^.].%*[^.].%*[^.].%*[^.].%d", &index3);
    printf("index3=%d\n",index3);

    mbi_rstQuerySpeedtestStatOverTestserver_t out = {0};
    strncpy(out.bspeed, "50.00", sizeof(out.bspeed)-1);
    strncpy(out.cspeed, "59.12", sizeof(out.cspeed)-1);
    strncpy(out.aspeed, "77.55", sizeof(out.aspeed)-1);

    mbi_setSpeed(&out);
    
    autoSpeedTest_t st;
    memset(&st, 0, sizeof(st));
    
    st.bspeed = 100000;
    
    sample_report_t report;
    memset(&report, 0, sizeof(report));
    
    report.cspeed = 12345;
    report.aspeed = 12300;
    report.maxspeed = 12700;
    
    test_setSpeed(&st, &report);
    
    sleep(2);
    
    test_setSpeed(&st, &report);

    return 0;
}
