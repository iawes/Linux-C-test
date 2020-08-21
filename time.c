#include <stdio.h>
#include <time.h>

char *gdbus_api_getCurrentTime()
{
	time_t now;
	struct tm *tm_now;
	char datetime[256] = {0};

	time(&now);
	tm_now = localtime(&now);

	strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", tm_now);
	printf("now datetime : %s\n", datetime);

	return datetime;	
}

int main(void)
{
    time_t now;
    struct tm *tm_now;
    char    datetime[200];

    time(&now);
    tm_now = localtime(&now);
    strftime(datetime, 200, "%x %X %n%Y-%m-%d %H:%M:%S %nzone: %Z\n", tm_now);

    printf("now datetime : %s\n", datetime);

    char datetime2[200] = {0};
    strftime(datetime2, 200, "%Y-%m-%d %H:%M:%S", tm_now);
    printf("now datetime : %s\n", datetime2);


//    time_t timep;
//    time (&timep);
//    printf("time: %s...",asctime(gmtime(&timep)));
	printf("data from function : %s", gdbus_api_getCurrentTime);
	
    return(0);
}
