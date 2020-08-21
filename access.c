#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (access("/dev/ptmx", F_OK)) 
    {
		printf("'/dev/ptmx' not found.\n");
		return -1;
	}

    printf("'/dev/ptmx' found.\n");
    return 0;
}