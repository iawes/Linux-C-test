#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/sysinfo.h>

int oalTms_rollforwardNtpTimeFromEpochTime(const char *t, const char *format, char *buf, int bufLen)
{
    #define TIME_OF_YEAR (365*24*60*60)
    /* transfer time string to time_t */
    struct tm tm0;
    memset(&tm0, 0, sizeof(struct tm));
    time_t pre;
    if(NULL == strptime(t, format, &tm0))
    {
        printf("call strptime failed.");
        return -1;
    }
    
    pre = mktime(&tm0);
    if(-1 == pre)
    {
        printf("call mktime failed.");
        return -1;
    }
    
    /* if > 1970 year, do not convert */
    if(pre > TIME_OF_YEAR)
    {
        return -1;
    }

    /* get now time_t */
    time_t now;
    now = time(NULL);

    /* get up time */
    struct sysinfo info;
    sysinfo(&info);

    /* Calculate on the basis of difference */
    time_t convert = now - info.uptime + pre;
    if(0 > convert)
    {
        printf("pre before now.");
        return -1;
    }    
    
    struct tm *tmp, tm1;
    memset(&tm1, 0, sizeof(struct tm));
    tmp = localtime_r(&convert, &tm1);
    if(NULL == tmp)
    {
        printf("call localtime_r failed.");
        return -1;
    }
    
    /* transfer to string */
    if(NULL == strftime(buf, bufLen, format, &tm1))
    {
        printf("call strftime failed.");
        return -1;
    }

    return 0;
}

char *convertNtpTime(char *s)
{
    int ret = 0;
    regex_t reg;
    regmatch_t match;
    /* this patten will match string like : 1970-01-01 08:00:43 or 2018-04-06 20:09:19, included in CT Tianyi 3.0 plugin logs */
    const char *pattern = "((([0-9]{4})-([0-9]{2})-(([0-9]{2})))\\s+([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9]))";

    memset(&reg, 0, sizeof(reg));
    memset(&match, 0, sizeof(match));
    
    ret = regcomp(&reg, pattern, REG_EXTENDED);
    if(ret != 0)
    {
        char err[256] = {0};
        regerror(ret, &reg, err, sizeof(err));
        printf("failreason: %s.\n", err);
        
        return s;
    }
    
    char *p = s;
    while((ret = regexec(&reg, p, 1, &match, REG_EXTENDED)) == 0)
    {      
        char orignalTime[256] = {0};
        int len = match.rm_eo - match.rm_so;  // 匹配长度
        if(len > sizeof(orignalTime)-1)
        {
            p += match.rm_eo;
            continue;
        }
        
        memcpy(orignalTime, p+match.rm_so, len);
        orignalTime[len] = '\0';
        printf("%s\n",orignalTime);
        if(NULL == strstr(orignalTime, "1970-"))
        {
            p += match.rm_eo;
            continue;
        }
        
        char convertTime[256] = {0};
        int result = oalTms_rollforwardNtpTimeFromEpochTime(orignalTime, "%Y-%m-%d %H:%M:%S", convertTime, sizeof(convertTime));
        if((0 == result) && (len == strlen(convertTime)))
        {
            memcpy(p+match.rm_so, convertTime, len);
            printf(s);
            printf("\n");
        }
        
        p += match.rm_eo;
    }
    
    regfree(&reg);
    return s;
}

    //const char *pattern = "((([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})-(((0[13578]|1[02])-(0[1-9]|[12][0-9]|3[01]))|((0[469]|11)-(0[1-9]|[12][0-9]|30))|(02-(0[1-9]|[1][0-9]|2[0-8]))))|((([0-9]{2})(0[48]|[2468][048]|[13579][26])|((0[48]|[2468][048]|[3579][26])00))-02-29))\\s+([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";

int main(void)
{
    char str[256] = "xxxx1970-01-01 08:00:43 test 1971-11-11 08:00:431972-12-12 08:00:43  08:00:49 1972-12-13 安装成功 1970-11-11 08:00:43";

    printf("convert time is :\n");
    printf(convertNtpTime(str));
    printf("\n");

    return 0;
}