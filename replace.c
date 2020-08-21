#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*返回目标字符串的长度，search为待替换的子字符串
replace替换的子字符串,pSrcStr为替换前的总的字符串
pResult为替换后的总的字符串,返回值为替换了多少个
search字符串。Len为输出结果的指针存储段pResult长度
*/

int str_replace(const char *search ,const char *replace,
                  const char *pSrcStr,char* pResult,unsigned int Len)
{
    int len=0, L1, L2, search_num=0;
    int len_search = strlen(search);
    //int len_replace = strlen(replace);
    strlen(pSrcStr);
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
        strlen(old_sub);
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


int main(void)
{
	int 0;
	char *pSrcStr = "ZXABC' MNT'DFGK' MNT'KLOP' MNT'YUIT ";
	char rstStr[128] = {0};

	api_strReplace("MNT", "BMPQ", pSrcStr, rstStr, sizeof(rstStr));

	printf("src str = %s.\n", pSrcStr);
	printf("rst str = %s.\n", rstStr);
	printf("%d.\n", len);

	char *pSrcStr2 = "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1,InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.3,InternetGatewayDevice.LANDevice.1.WLANConfiguration.1";
	char rstStr2[256] = {0};

	api_strReplace("InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.", "LAN", pSrcStr2, rstStr2, sizeof(rstStr2));

	printf("src str = %s.\n", pSrcStr2);
	printf("rst str = %s.\n", rstStr2);
	printf("%d.\n", len);

	char rstStr3[256] = {0};

	api_strReplace("InternetGatewayDevice.LANDevice.1.WLANConfiguration.", "SSID", rstStr2, rstStr3, sizeof(rstStr3));

	printf("src str = %s.\n", rstStr2);
	printf("rst str = %s.\n", rstStr3);
	printf("%d.\n", len);

	char rstStr4[256] = {0};

	api_strReplace("LAN", "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.", rstStr3, rstStr4, sizeof(rstStr4));
    char rstStr5[256] = {0};
	api_strReplace("SSID", "InternetGatewayDevice.LANDevice.1.WLANConfiguration.", rstStr4, rstStr5, sizeof(rstStr4));

	printf("src str = %s.\n", rstStr3);
	printf("rst str = %s.\n", rstStr4);
    printf("rst str = %s.\n", rstStr5);
	printf("%d.\n", len);

	char rstStr6[256] = {0};
    char rstStr7[256] = {0};

	api_strReplace("", "InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.", rstStr3, rstStr6, sizeof(rstStr6));
    printf("%d.\n", len);   
	api_strReplace("SSID", "", rstStr3, rstStr7, sizeof(rstStr7));
    printf("%d.\n", len);   

	printf("src str = %s.\n", rstStr3);
	printf("rst str = %s.\n", rstStr6);
    printf("rst str = %s.\n", rstStr7);
	
	return 0;
}
