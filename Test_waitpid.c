#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int ret, i, status;
    char *child_argv[16] = {0};
    pid_t pid;
    if (argc < 2)
    {
        fprintf(stderr, "Usage:%s <exe_path> <args...>", argv[0]);
        return -1;
    }

    for (i = 1; i < argc; ++i)
    {
        child_argv[i-1] = (char *)calloc(1, strlen(argv[i])+1);
        memcpy(child_argv[i-1], argv[i], strlen(argv[i]));
    }

    while(1)
    {
        pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "fork() error.errno:%d error:%s", errno, strerror(errno));
            break;
        }
        if (pid == 0)
        {
            ret = execv(child_argv[0], (char **)child_argv);
            if (ret < 0)
            {
                fprintf(stderr, "execv ret:%d errno:%d error:%s", ret, errno, strerror(errno));
                continue;
            }
            exit(0);
        }
        if (pid > 0)
        {
            pid = wait(&status);
            fprintf(stdout, "Child process id: %d, status:%d\n", pid, status);
            //todo:此处按照规范写文件
        }
    }/* endless loop here */

    return 0;
}