#include <string.h>
#include <stdio.h>

#define MAX_URI_LEN 256
#define MAX_INSTANCE_DEPTH 3
#define isdigit(x)	((x)>='0'&&(x)<='9')

typedef struct
{
    int currentDepth;
    int instance[MAX_INSTANCE_DEPTH];
} InstanceId;

int cfgUtl_isDigitStr(const char *str)
{
    char *p = (char *)str;

    if (p == NULL)
        return 0;

    while (*p)
    {
        if (!isdigit(*p) && *p != '-')
        {
            return 0;
        }
        p++;
    }

    return 1;
}

void cfgUtl_changeToFormatUri(const char *uri, InstanceId *retIId)
{
    char *ptr;
    char *saveptr = NULL;
    char *token;
    int j = 0;
    char *delim = ".";

    char buf[MAX_URI_LEN];
    strncpy(buf, uri, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    ptr = buf;

    retIId->currentDepth = 0;
    for (j = 0; ; j++, ptr = NULL)
    {
        token = strtok_r(ptr, delim, &saveptr);
        if (token == NULL)
            break;
        else
        {
            if (cfgUtl_isDigitStr(token))
            {
                retIId->instance[retIId->currentDepth] = atoi(token);
                retIId->currentDepth++;
            }
            else
            {
                if (strncmp(token, "%d", strlen("%d")) == 0)
                {
                    retIId->instance[retIId->currentDepth] = 0;
                    retIId->currentDepth++;
                }
            }
        }
    }

    return;
}

void cfgUtl_dumpInstanceId(InstanceId *iid)
{
    int i;

    fprintf(stderr, "Depth:%d, iid={ ", iid->currentDepth);
    for (i = 0; i < iid->currentDepth; i++)
    {
        fprintf(stderr, "%d ", iid->instance[i]);
    }
    fprintf(stderr, "}\n");
}

int main()
{
    const char * path = "lancpi.1.21";
    InstanceId iid;
    memset(&iid, 0, sizeof(iid));
    cfgUtl_changeToFormatUri((const char *)path, &iid);
    cfgUtl_dumpInstanceId(&iid);
    
    return 0;
}