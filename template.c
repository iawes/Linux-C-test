#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//资源使用代码
int act_movie(char *p)
{
    if(p == NULL)
    {
        printf("input is NULL.\n");
        return -1;
    }
    
    printf("%s\n", p);
    
    return 0;
}

//定义模板方法函数，负责资源管理
int template(int (*play_movie)(char *p), int len)
{
    int ret;
    
    //申请内存
    char *p_movie = (char *)malloc(len);
    strcpy(p_movie, "playing moive and have a see.");
    
    //读取sd卡视频，并存放在p_movie中
    
    //根据电影类型来选择播放方式
    ret = play_movie(p_movie);
    
    //释放内存
    free(p_movie);
    
    return ret;
}

int main(void)
{
    int ret;
    
    //调用模板方法函数
    ret = template(act_movie, 1024);
    
    return 0;
}