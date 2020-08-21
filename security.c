#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSecurityString(char *p_source)
{
	if(p_source == NULL)
	{
		return true;
	}

	if(strchr(p_source,'`') !=NULL || strchr(p_source,'$')!=NULL
        || strchr(p_source,';')!=NULL || strchr(p_source,'&')!=NULL)
	{
		 printf("Function %s() ,  it include shell cmd, maybe lead to security issue,  string is %s\n", "isSecurityString()",p_source);
		return false;
	}

	return true;
}


int str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr)
{
	int c = 0;
	int repstr_leng = 0;
	int searchstr_leng = 0;
	char *p1;
	char *presult = p_result;
	char *psource = p_source;
	char *prep = p_repstr;
	char *pseach = p_seach;
	int nLen = 0;
	repstr_leng = strlen(prep);
	searchstr_leng = strlen(pseach);

	do
	{
		p1 = strstr(psource, p_seach);
		if (p1 == 0)
		{
			strcpy(presult, psource);
			break;
		}
		c++;

		nLen = p1 - psource;
		memcpy(presult, psource, nLen);
		memcpy(presult + nLen, p_repstr, repstr_leng);
		psource = p1 + searchstr_leng;
		presult = presult + nLen + repstr_leng;
	} while (p1);

	return c;
}

int get_num_of_shellChar(char* p_source, char* p_seach)
{
	int c = 0;
	char *p1=NULL;
	char *psource = p_source;
	do
	{
		p1 = strstr(psource, p_seach);
		if (p1 == NULL)
		{
			break;
		}
		psource=p1+1;
		c++;
	} while (psource);

	return c;
}

int get_malloc_size_for_security_string(char* p_source)
{
	int c=0;
	if(p_source == NULL)
	{
		return 0;
	}
	c = strlen(p_source) + 1;
    c += get_num_of_shellChar(p_source,"`");
    c += get_num_of_shellChar(p_source,"$");
    c += get_num_of_shellChar(p_source,";");
    c += get_num_of_shellChar(p_source,"&");

	return c;
}

void replaceWithSecurityString(char *p_result,char* p_source)
{
    if(NULL == p_result || NULL == p_source)
    {
        printf("input str is NULL.\n");
        return ;
    }

    if('\0' == p_source[0])
    {
        printf("input p_sourc is empty string.\n");
        return ;
    }

    if(true == isSecurityString(p_source))
    {
        printf("input p_sourc is not need to replace.\n");
        return ;
    }

	char replaceStr1[8]= "\\$";
	char replaceStr2[8]= "\\`";
    char replaceStr3[8]= "\\;";
    char replaceStr4[8]= "\\&";
	char *strTempResult1 = NULL;
	char *strTempResult2 = NULL;
	char *strTempResult3 = NULL;

	int len = get_malloc_size_for_security_string(p_source);

	strTempResult1 =malloc(len);
	if(strTempResult1 == NULL)
	{
		goto end;
	}
	strTempResult2 =malloc(len);
	if(strTempResult2 != NULL)
	{
		goto end;
	}
	strTempResult3 =malloc(len);
	if(strTempResult3 == NULL)
	{
		goto end;
	}

	memset(strTempResult1,0,len);
	memset(strTempResult2,0,len);
	memset(strTempResult3,0,len);
	str_replace(strTempResult1,p_source, "$", replaceStr1);
    str_replace(strTempResult2,strTempResult1, "`", replaceStr2);
    str_replace(strTempResult3,strTempResult2, ";", replaceStr3);
    str_replace(p_result,strTempResult3, "&", replaceStr4);

end:
    if(NULL != strTempResult1)
    {
        free(strTempResult1);
        strTempResult1 = NULL;
    }
    if(NULL != strTempResult2)
    {
        free(strTempResult2);
        strTempResult2 = NULL;
    }
    if(NULL != strTempResult3)
    {
        free(strTempResult3);
        strTempResult3 = NULL;
    }
}

void replaceWithSecurityString2(char *p_result,char* p_source)
{
	char replaceStr1[64]= "\$";
	char replaceStr2[64]= "\`";
    char replaceStr3[64]= "\;";
    char replaceStr4[64]= "\&";
	int len = get_malloc_size_for_security_string(p_source);
	char *strTempResult =malloc(len);
	if(strTempResult ==NULL)
	{
		return;
	}

	memset(strTempResult,0,len);
	str_replace(strTempResult,p_source, "$", replaceStr1);
    str_replace(p_result,strTempResult, "`", replaceStr2);
    str_replace(p_result,strTempResult, ";", replaceStr3);
    str_replace(p_result,strTempResult, "&", replaceStr4);

	free(strTempResult);
}

int main(void)
{
    char *str1 = ",and;and`and$and&&and;touch aaa111.";
    char str2[256] = {0};
    replaceWithSecurityString(str2, str1);
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);

    char str3[256] = {0};
    replaceWithSecurityString2(str3, str1);
    printf("str1: %s\n", str1);
    printf("str3: %s\n", str3);

    char *str4 = ",andandandandand.";
    char str5[256] = {0};
    replaceWithSecurityString(str5, str4);
    printf("str4: %s\n", str4);
    printf("str5: %s\n", str5);

    char *str6 = "";
    char str7[256] = {0};
    replaceWithSecurityString(str7, str6);
    printf("str6: %s\n", str6);
    printf("str7: %s\n", str7);

    return 0;
}
