/*===============================================================
*   文件名称：cpu.c
*   创建日期：2016年11月17日
================================================================*/
#include <stdio.h>
#include <stdlib.h>


#define FLT_MODULO        (1<<16)
#define double_pctcpu(p) ((double)p/(double)FLT_MODULO)

typedef struct
{
    char name[20];
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
    unsigned int stealstolen;
    unsigned int guest;
} CPU_OCCUPY;



float cal_cpuoccupy(CPU_OCCUPY *o, CPU_OCCUPY *n)
{
    //unsigned long cpu_use = 0;
    float cpu_use = 0;
    unsigned long total1, total2;
    unsigned long idle1, idle2;

    total1 = o->user + o->nice + o->system + o->idle + o->iowait + o->irq + o->softirq + o->stealstolen + o->guest;
    total2 = n->user + n->nice + n->system + n->idle + n->iowait + n->irq + n->softirq + n->stealstolen + n->guest;
    idle1 = o->idle;
    idle2 = n->idle;

    //cpu_use = (((total2 - total1) - (idle2 - idle1)) * 100 / (total2 - total1));
    cpu_use = (((total2 - total1) - (idle2 - idle1))/ (total2 - total1));
    return cpu_use;
}


void getcpuoccupy(CPU_OCCUPY *cpust)
{
    FILE *fd;
    char buff[256];
    CPU_OCCUPY *cpu_occupy;
    cpu_occupy = cpust;

    fd = fopen("/proc/stat", "r");
    fgets(buff, sizeof(buff), fd);

    sscanf(buff, "%s %u %u %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user,
           &cpu_occupy->nice, &cpu_occupy->system, &cpu_occupy->idle, &cpu_occupy->iowait,
           &cpu_occupy->irq, &cpu_occupy->softirq, &cpu_occupy->stealstolen, &cpu_occupy->guest);
    //printf("buff = %s\n",buff);

    printf("name = %s\n", cpu_occupy->name);
    printf("cpu_occupy->user = %u\n", cpu_occupy->user);
    printf("cpu_occupy->nice = %u\n", cpu_occupy->nice);
    printf("cpu_occupy->system = %u\n", cpu_occupy->system);
    printf("cpu_occupy->idle = %u\n", cpu_occupy->idle);
    printf("cpu_occupy->iowait = %u\n", cpu_occupy->iowait);
    printf("cpu_occupy->irq = %u\n", cpu_occupy->irq);
    printf("cpu_occupy->softirq = %u\n", cpu_occupy->softirq);
    printf("cpu_occupy->stealstolen = %u\n", cpu_occupy->stealstolen);
    printf("cpu_occupy->guest = %u\n", cpu_occupy->guest);

    fclose(fd);
}



float libutil_getcpuPercent(void)
{
    CPU_OCCUPY cpu_stat1;
    CPU_OCCUPY cpu_stat2;
    unsigned long cpu;
    getcpuoccupy((CPU_OCCUPY *)&cpu_stat1);
    sleep(1);
    getcpuoccupy((CPU_OCCUPY *)&cpu_stat2);
    cpu = cal_cpuoccupy((CPU_OCCUPY *)&cpu_stat1, (CPU_OCCUPY *)&cpu_stat2);
    printf("##########cpu = %lu\n", cpu);

    return cpu;
}

int main()
{
    float cpu = 0;
	char cpuStr[32] = {0};

    cpu = libutil_getcpuPercent();

    printf("cpu percent = %f.\n", cpu);
    printf("cpu percent = %f.\n", 100.0 * double_pctcpu(cpu));
    printf("cpu percent = %0.1f.\n", 100.0 * cpu);
	
	snprintf(cpuStr, sizeof(cpuStr), "%0.1f", 100 * cpu);
	printf("cpuStr = %s.\n", cpuStr);

    return 0;
}
