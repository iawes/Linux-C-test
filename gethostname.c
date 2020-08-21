#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>

int main(void)
{
	//char *p = dhmp;
	
	struct hostent *entry1;
	struct hostent *entry2;
	
	entry1 = gethostbyname("dhmp:Myjsy12PL@218.207.69.242:21");
	if(NULL == entry1)
	{		
		printf("gethostbyname dhmp:Myjsy12PL@218.207.69.242:21 failed.");
	}
	
	
	
	entry2 = gethostbyname("dhmp");
	if(NULL == entry1)
	{		
		printf("gethostbyname dhmp failed.");
	}
	
	return 0;
}