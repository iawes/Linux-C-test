#include <stdio.h>
#include <stdlib.h>
//#include  "sys/type.h"
#include  "sys/wait.h"

int main(int argc, char *argv[]) 
{ 
    pid_t status;  
	
	printf("argv[1] = %s.\n", argv[1]);
	
	
	char cmd[256] = {0};
	snprintf(cmd, sizeof(cmd), "ifconfig %s", argv[1]);
	
    status = system(cmd); 
    if(status == -1)
	{
		printf("system error");
    }
	else
	{
		if(WIFEXITED(status))
		{
			   if(0 == WEXITSTATUS(status))
			   {
					printf("run  successfully %d\n", WEXITSTATUS(status));
			   }
			   else
			   {
					printf("run failed %d\n",WEXITSTATUS(status));
			   }
		}
		else
		{
			printf("exit code %d \n",WEXITSTATUS(status));
		}
	}	
			
    return 0;
}