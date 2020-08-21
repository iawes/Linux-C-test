#include <stdio.h>
int main(int argc, char *argv[])
{
	int i = 0;
	
	i = atoi(argv[1]);
	
	if(i == 5)
	{		
		goto stop;
	}
	
	if(i == 3)
	{		
		goto stand;
	}
	
	printf("i = %d\n", i);
	
stop: 
	printf( "i = 5 end.\n");
	
stand: 
	printf( "i = 3 end.\n");	
	
	printf( " end.\n");

	return 0;
}