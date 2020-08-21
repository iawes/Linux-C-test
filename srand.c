/*===============================================================
*   文件名称：srand.c
*   创建日期：2018年11月05日
================================================================*/
#include <stdio.h>
#include <stdlib.h>

#define SOFT_PROBE_CPU_OCCUPY_LOW    (5)
#define SOFT_PROBE_CPU_OCCUPY_HIGH   (29)


float libutil_getRandNumber(unsigned int lThresh,unsigned int hThresh)
{
    if(hThresh<=lThresh)
        return SOFT_PROBE_CPU_OCCUPY_LOW;
    struct timeval tpstart;
    gettimeofday(&tpstart,NULL);
    srand(tpstart.tv_usec);
    return (float)((rand()%(hThresh-lThresh))+lThresh);
}

float systool_getcpuOccupy(void)
{
    float cpu = 0;

    cpu=libutil_getRandNumber(SOFT_PROBE_CPU_OCCUPY_LOW,SOFT_PROBE_CPU_OCCUPY_HIGH);
    printf("111 float cpu is %f.\n", cpu);

    return cpu;
}

int main()
{
   int cpu = 0; 
   cpu = (int)systool_getcpuOccupy();
   printf("float cpu is %f.\n", cpu);
   printf("int cpu is %d.\n", cpu);

   if(cpu <= 0)
   {
       printf("222 int cpu is %d.\n", cpu);
   }

   return 0;
}
