/*===============================================================
*   文件名称：time2.c
*   创建日期：2019年02月15日
================================================================*/
#include <time.h>
#include <stdio.h>
#include <string.h>

#define TRUE (0)
#define FALSE (1)

int cslibTms_rollforwardNtpTimeFromEpochTime(const char *t, const char *format, char *buf, int bufLen)
{
    /* transfer time string to time_t */
    struct tm tm0;
    memset(&tm0, 0, sizeof(struct tm));
    time_t pre;
    if(NULL == strptime(t, format, &tm0))
    {
        printf("call strptime failed.\n");
        return -1;
    }
    
    pre = mktime(&tm0);
    if(-1 == pre)
    {
        printf("call mktime failed.\n");
        return -1;
    }

    /* get now time_t */
    time_t now;
    now = time(NULL);

    /* Calculate on the basis of difference */
    time_t convert = now - pre;
    if(0 > convert)
    {
        printf("pre before now.\n");
        return -1;
    }    
    
    struct tm *tmp, tm1;
    memset(&tm1, 0, sizeof(struct tm));
    tmp = localtime_r(&convert, &tm1);
    if(NULL == tmp)
    {
        printf("call localtime_r failed.\n");
        return -1;
    }
    
    /* transfer to string */
    if(NULL == strftime(buf, bufLen, format, &tm1))
    {
        printf("call strftime failed.\n");
        return -1;
    }

    return 0;
}

char *convertNtpTime(char *s)
{
    int ret = 0;
    char time[255] = {0};
    char time_convert[255] = {0};
    strncpy(time, s, strlen("1970-01-01 15:00:33"));
    ret = cslibTms_rollforwardNtpTimeFromEpochTime(time, "%Y-%m-%d %H:%M:%S", time_convert, sizeof(time_convert));
    if(0!= ret)
    {
        return s;
    }

    memcpy(s, time_convert, strlen(time_convert));

    return s;
}
 
int main() 
{
   /* struct tm tm; 
    struct tm tm2; 
    char buf[255];
    char *p = NULL;


    p = strptime("1970-01-01 08:00:00", "%Y-%m-%d %T" , &tm2);
    if(NULL == p)
    {
        printf("strptime char is error.\n");
    }
    
      
    strptime("1970-01-01 08:00:33", "%Y-%m-%d %T" , &tm);
    printf("asctime:%s\n",asctime(&tm));
 
    memset(buf,0,sizeof(buf));
    strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);
    puts(buf);

    memset(buf,0,sizeof(buf));
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    puts(buf);

    memset(buf,0,sizeof(buf));
    strftime(buf, sizeof(buf), "%c", &tm);
    puts(buf);

    memset(buf,0,sizeof(buf));
    strftime(buf, sizeof(buf), "%Y-%m-%d %T", &tm);
    puts(buf);

    memset(buf,0,sizeof(buf));
    strftime(buf, sizeof(buf), "%Ec", &tm);
    puts(buf);

    time_t    timetTime;  
    //tm结构转换成time_t结构  
    timetTime = mktime(&tm2);  
    printf("11111-timetTime=%d\n", timetTime);  
    //用ctime函数校验下，上面转换是否正确  
    printf("After transfer, time is: %s\n", ctime((time_t*)&timetTime));
    
    
    //tm结构转换成time_t结构  
    timetTime = mktime(&tm);  
    printf("22222-timetTime=%d\n", timetTime);  
    //用ctime函数校验下，上面转换是否正确  
    printf("After transfer, ctime is: %s\n", ctime((time_t*)&timetTime));
    printf("After transfer, asctime:%s\n",asctime(&tm));
*/
    char time[255] = {0};
    cslibTms_rollforwardNtpTimeFromEpochTime("1970-01-01 15:00:33", "%Y-%m-%d %H:%M:%S", time, sizeof(time));
    printf("time is %s.\n", time);
    
    cslibTms_rollforwardNtpTimeFromEpochTime("2016-01-01 15:00:33", "%Y-%m-%d %H:%M:%S", time, sizeof(time));
    printf("time is %s.\n", time);    

    char slt[1024] = {"1970-01-01 15:00:33 plugin es ddt "};
    printf(convertNtpTime(slt));
    
    return 0;
} 
