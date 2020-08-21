#include <stdio.h>
#include <stdlib.h>

void random_bytes(unsigned char *buf, int len)
{
    int i;

    for (i = 0; i < len; ++i)
    {
        //buf[i] = mrand48() >> 24;
        buf[i] = (rand()%16);
        printf("buf[%d] = %d:%x\n", i, buf[i], buf[i]);
        //printf("buf[%d] = %x\n", i, buf[i]);
    }        
}

void get_rnd_string(char *buf,unsigned char orig[], int len)
{
	int i=0;

    for(i=0; i<len; i++)
    {
        sprintf(buf+i,"%x",orig[i]);
    }
}

#define DEV_RND_LEN 16

unsigned char pre_dev_rnd[DEV_RND_LEN]= {0};
unsigned char cur_dev_rnd[DEV_RND_LEN]= {0};

void new_dev_rnd()
{
    static int flag = 0;
    memcpy(pre_dev_rnd,cur_dev_rnd,DEV_RND_LEN);
    random_bytes(cur_dev_rnd,DEV_RND_LEN);
    if(flag ==0)
    {
        memcpy(pre_dev_rnd,cur_dev_rnd,DEV_RND_LEN);
        flag = 1;
    }

    return;
}

int main()
{
    new_dev_rnd();

    char dev_rnd[64] = {0};

    get_rnd_string(dev_rnd, cur_dev_rnd, 16);

    printf("dev_rnd = %s\n", dev_rnd);

    return 0;
}