#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*返回目标字符串的长度，search为待替换的子字符串
replace替换的子字符串,pSrcStr为替换前的总的字符串
pResult为替换后的总的字符串,返回值为替换了多少个
search字符串。Len为输出结果的指针存储段pResult长度
*/

int str_replace_2(const char *search ,const char *replace,
                  const char *pSrcStr,char* pResult,unsigned int Len)
{
    int len=0, L1, L2, search_num=0;
    int len_search = strlen(search);
    //int len_replace = strlen(replace);
    len = strlen(pSrcStr);
    char* srcStr = (char*)malloc(len + len_search+1);
    char* psrcStr = srcStr;
    char* pSep = NULL;
    char* old_sub = (char*)malloc(len+1);
    memset(old_sub, 0, len+1);
    memset(pResult, 0, Len);
    memset(srcStr, 0, len+len_search+1);
    strncpy(srcStr, pSrcStr, len-1);
    strcat(srcStr, search);
    while ((pSep = strstr(srcStr, search))!=NULL)
    {
        ++ search_num;
        memset(old_sub, 0, len+1);
        L1 = strlen(srcStr);
        L2 = strlen(pSep);
        memmove(old_sub, srcStr, L1-L2);
        len = strlen(old_sub);
        srcStr += len+len_search;
        if (1 == search_num)
        {
            strcpy(pResult, old_sub);
        }
        else
        {
            strcat(pResult, old_sub);
        }
        if (NULL == strstr(srcStr, search))
        {
            break;
        }
        strcat(pResult, replace);
    }

    if(NULL != psrcStr)
    {
        free(psrcStr);
        psrcStr = NULL;
    }

    if(NULL != old_sub)
    {
        free(old_sub);
        old_sub = NULL;
    }

    return search_num-1;
}

int api_strReplace(const char *search , const char *replace,
                  const char *pSrcStr, char* pResult, unsigned int resultLen)
{
	if((NULL == search) || (NULL == replace) || (NULL == pSrcStr))
	{
		printf("input para error!\n");
		return -1;
	}

	if((NULL == pResult) || (0 >= resultLen))
	{
		printf("output pResult para error!\n");
		return -1;
	}	
	memset(pResult, 0, resultLen);
	
    int lenSrc = 0, lenSearch = 0;
	
    lenSearch = strlen(search);
	if(0 == lenSearch)
	{
		printf("search string is empty string, nothing to be replaced!\n");
		return 0;
	}
	
    lenSrc = strlen(pSrcStr);
	if(0 == lenSrc)
	{
		printf("pSrcStr string is empty string, cannot be replaced!\n");
		return 0;
	}

	char* pSrcTmpStr = NULL;
	char* pOldSubStr = NULL;
    pSrcTmpStr = (char*)malloc(lenSrc + lenSearch + 1);
   	if(NULL == pSrcTmpStr)
   	{
		printf("malloc pSrcTmp error!\n");
		goto fail;
	}
	memset(pSrcTmpStr, 0, lenSrc + lenSearch + 1);
    
    pOldSubStr = (char*)malloc(lenSrc + 1);
   	if(NULL == pOldSubStr)
   	{
		printf("malloc pOldSub error!\n");
		goto fail;
	}	
    memset(pOldSubStr, 0, lenSrc + 1);     

	//genete tmp string with src string  
	//add the search string for while loop find an ending case
    strcpy(pSrcTmpStr, pSrcStr);
    strcat(pSrcTmpStr, search);

	//pointer move to begin of search string
	char* pSep = NULL;

	//how many times to find search string
	int searchNum = 0;

	//calculate the len of output string 
	int lenOutStr = 0;

	//find string "search" in pSrcTmp
    char *p = pSrcTmpStr;
    while (NULL != (pSep = strstr(p, search)))
    {
        ++ searchNum;
        memset(pOldSubStr, 0, lenSrc + 1);

		//move old sub string before searh string
		int len1 = 0;
		int len2 = 0;
        len1 = strlen(p);
        len2 = strlen(pSep);
        memmove(pOldSubStr, p, len1 - len2);

		//move pointer to find next search string
		int lenOldSubStr = 0;
        lenOldSubStr = strlen(pOldSubStr);
        p += (lenOldSubStr + lenSearch);

		lenOutStr += lenOldSubStr;
		if(lenOutStr >= resultLen)
		{
			printf("output string length %d bigger than pResult string length %d!\n", lenOutStr, resultLen);
			goto fail;
		}

		//copy old sub string and replace string to result string
        if (1 == searchNum)
        {
            strcpy(pResult, pOldSubStr);
        }
        else
        {
            strcat(pResult, pOldSubStr);
        }

		//the last search string was added for end 
        if (NULL == strstr(p, search))
        {
            break;
        }

		lenOutStr += strlen(replace);
		if(lenOutStr >= resultLen)
		{
			printf("output string length %d bigger than pResult string length %d!\n", lenOutStr, resultLen);
			goto fail;
		}
		
        strcat(pResult, replace);
    }

    if(NULL != pOldSubStr)
    {
        free(pOldSubStr);
        pOldSubStr = NULL;
    }

    if(NULL != pSrcTmpStr)
    {
        free(pSrcTmpStr);
        pSrcTmpStr = NULL;
    }	

    return searchNum - 1;

fail:
	if(NULL != pOldSubStr)
    {
        free(pOldSubStr);
        pOldSubStr = NULL;
    }

    if(NULL != pSrcTmpStr)
    {
        free(pSrcTmpStr);
        pSrcTmpStr = NULL;
    }

	return -1;
}

// 参数说明:  
// in， 源字符串  
// out, 存放最后结果的字符串  
// outlen，out最大的大小  
// src，要替换的字符串  
// dst，替换成什么字符串  
char *strrpl(const char *src, char *dst, char *in, char *out, int outlen)  
{  
    char *p = in;  
    unsigned int  len = outlen - 1;  
    
    // 这几段检查参数合法性  
    if((NULL == src) || (NULL == dst) || (NULL == in) || (NULL == out))  
    {  
        return NULL;  
    }  
    if((strcmp(in, "") == 0) || (strcmp(src, "") == 0))
    {  
        return NULL;  
    }  
    if((outlen <= 0) || (outlen <= strlen(dst)))
    {  
        return NULL;  
    }  
    
    while((*p != '\0') && (len > 0))  
    {  
        //loop to find src string, if not find, copy in to out string
        if(strncmp(p, src, strlen(src)) != 0)  
        {  
            int n = strlen(out);  
    
            out[n] = *p;  
            out[n + 1] = '\0';  
    
            p++;  
            len--;  
        }  
        //if find, copy dst string to out and overlap src string
        else  
        {  
            strcat(out, dst);
            p += strlen(src);  
            len -= strlen(dst);  
        }  
    }  
    
    return out;  
}  

 // fork from https://github.com/irl/la-cucina/blob/master/str_replace.c
static char* str_replace(char* string, const char* substr, const char* replacement) {
    char* tok = NULL;
    char* newstr = NULL;
    char* oldstr = NULL;
    int   oldstr_len = 0;
    int   substr_len = 0;
    int   replacement_len = 0;

    newstr = strdup(string);
    substr_len = strlen(substr);
    replacement_len = strlen(replacement);

    if (substr == NULL || replacement == NULL) {
        return newstr;
    }

    while ((tok = strstr(newstr, substr))) {
        oldstr = newstr;
        oldstr_len = strlen(oldstr);
        newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));

        if (newstr == NULL) {
            free(oldstr);
            return NULL;
        }

        memcpy(newstr, oldstr, tok - oldstr);
        memcpy(newstr + (tok - oldstr), replacement, replacement_len);
        memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
        memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);

        free(oldstr);
    }

    return newstr;
}

int main_1(void)
{
	int len = 0;
	char *pSrcStr = "ZXABC' MNT'DFGK' MNT'KLOP' MNT'YUIT ";
	char rstStr[128] = {0};

	strrpl("MNT", "BMPQ", pSrcStr, rstStr, sizeof(rstStr));

	printf("src str = %s.\n", pSrcStr);
	printf("rst str = %s.\n", rstStr);
    printf("-----------------------------------------------------------------------------------\n");

	char *pSrcStr2 = "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1,InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.3,InternetGatewayDevice.LANDevice.1.WLANConfiguration.1";
	char rstStr2[256] = {0};

	strrpl("InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.", "LAN", pSrcStr2, rstStr2, sizeof(rstStr2));

	printf("src str = %s.\n", pSrcStr2);
	printf("rst str = %s.\n", rstStr2);
    printf("-----------------------------------------------------------------------------------\n");
	char rstStr3[256] = {0};

	strrpl("InternetGatewayDevice.LANDevice.1.WLANConfiguration.", "SSID", rstStr2, rstStr3, sizeof(rstStr3));

	printf("src str = %s.\n", rstStr2);
	printf("rst str = %s.\n", rstStr3);
    printf("-----------------------------------------------------------------------------------\n");
	char rstStr4[256] = {0};

	strrpl("LAN", "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.", rstStr3, rstStr4, sizeof(rstStr4));
    char rstStr5[256] = {0};
	strrpl("SSID", "InternetGatewayDevice.LANDevice.1.WLANConfiguration.", rstStr4, rstStr5, sizeof(rstStr4));

	printf("src str = %s.\n", rstStr3);
	printf("rst str = %s.\n", rstStr4);
    printf("rst str = %s.\n", rstStr5);
    printf("-----------------------------------------------------------------------------------\n");
	char rstStr6[256] = {0};
    char rstStr7[256] = {0};

	strrpl("", "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.", rstStr3, rstStr6, sizeof(rstStr6));
	strrpl("SSID", "", rstStr3, rstStr7, sizeof(rstStr7));

	printf("src str = %s.\n", rstStr3);
	printf("rst str = %s.\n", rstStr6);
    printf("rst str = %s.\n", rstStr7);
    printf("-----------------------------------------------------------------------------------\n");
	return 0;
}

int main()
{
	char *src = "http://192.168.1.1:9090/IGMP:224.1.1.2:2024/urn:schemas-upnp-org:service:AVTransport_control";
	
	char *p = str_replace(src, "/urn:schemas-upnp-org:service:AVTransport_control", "");
	printf("str1: %s!\n", p);
	
	char *q = str_replace(p, "IGMP:", "udp/");
	printf("str2: %s!\n", q);

	free(p);
	free(q);

	return 0;
}
