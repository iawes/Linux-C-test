#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <errno.h>

#define MATCH_NUM (10)

int main(void)
{
    char *str = "1970-01-01 08:00:43 test 1971-11-11 08:00:431972-12-12 08:00:43";

    const char *pattern = "((([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})-(((0[13578]|1[02])-(0[1-9]|[12][0-9]|3[01]))|((0[469]|11)-(0[1-9]|[12][0-9]|30))|(02-(0[1-9]|[1][0-9]|2[0-8]))))|((([0-9]{2})(0[48]|[2468][048]|[13579][26])|((0[48]|[2468][048]|[3579][26])00))-02-29))\\s+([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
    //const char *pattern = "\\d{4}(-|\\/)((0[1-9])|(1[0-2]))(-|\\/)((0[1-9])|([1-2][0-9])|(3[0-1]))(T|\\s)(([0-1][0-9])|(2[0-3])):([0-5][0-9]):([0-5][0-9])";
    
    regex_t reg;
    regmatch_t match;
    char buf[1024] = {0};
    int i = 0;

    memset(&match, 0, sizeof(regmatch_t));
    
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
        while((ret = regexec(&reg, str, 1, &match, REG_EXTENDED)) == 0)
        {  
            memset(buf,0, sizeof(buf));
            int len = match.rm_eo - match.rm_so;  // 匹配长度
            memcpy(buf, str+match.rm_so, len);
            printf("%s\n",buf);
            
            int offset = match.rm_eo;
            memset(&match, 0, sizeof(regmatch_t));
            str += offset;
            
            if (*str == '\0')  break;
        }
    }
    
    regfree(&reg);
    return 0;
}