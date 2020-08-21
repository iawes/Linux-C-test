#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <errno.h>

#define MATCH_NUM (10)

int main(void)
{
    const char *str = "1970-01-01 08:00:43 test 1971-11-11 08:00:43";

    //const char *pattern = "((([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})-(((0[13578]|1[02])-(0[1-9]|[12][0-9]|3[01]))|((0[469]|11)-(0[1-9]|[12][0-9]|30))|(02-(0[1-9]|[1][0-9]|2[0-8]))))|((([0-9]{2})(0[48]|[2468][048]|[13579][26])|((0[48]|[2468][048]|[3579][26])00))-02-29))\\s+([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
    const char *pattern = "\\d{4}(-|\\/)((0[1-9])|(1[0-2]))(-|\\/)((0[1-9])|([1-2][0-9])|(3[0-1]))(T|\\s)(([0-1][0-9])|(2[0-3])):([0-5][0-9]):([0-5][0-9])";
    
    regex_t reg;
    regmatch_t match[MATCH_NUM];
    char buf[1024] = {0};
    int i = 0;

    memset(match, 0, sizeof(regmatch_t)*MATCH_NUM);
    
    int ret = 0;
    ret = regcomp(&reg, pattern, REG_EXTENDED);
    if(ret != 0)
    {
        printf("ret=%d\n",ret);

        char err[256] = {0};
        regerror(ret, &reg, err, sizeof(err));
        printf("failreason: %s.\n", err);
    }
    else
    {
        ret = regexec(&reg, str, MATCH_NUM, match, 0);
        printf("ret = %d.\n", ret);
        if(ret != REG_NOMATCH)
        {            
            // 提取组信息,i从1开始   
            for(i=0; i<MATCH_NUM&&match[i].rm_so!=-1; i++)  
            {  
                memset(buf,0, sizeof(buf));
                int len = match[i].rm_eo - match[i].rm_so;  // 匹配长度
                printf("num: %d, len: %d \t", i+1, len);
                memcpy(buf, str+match[i].rm_so, len);
                printf("%s\n",buf);
            }
        }
        else if (ret == REG_NOMATCH) {
            printf("No match.\n");
        }
        else
        {
            char err[256] = {0};
            regerror(ret, &reg, err, sizeof(err));
            printf("failreason: %s.\n", err);                
        }
    }
    
    regfree(&reg);
    return 0;
}