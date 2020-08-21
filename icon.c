/*
 * =====================================================================================
 *
 *       Filename:  iconv.c
 *
 *    Description:  j
 *
 *        Version:  1.0
 *        Created:  08/05/2015 05:51:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iconv.h>
bool unicode_to_utf8 (char *inbuf, size_t *inlen, char *outbuf, size_t *outlen)
{
  /* 目的编码, TRANSLIT：遇到无法转换的字符就找相近字符替换
   *           IGNORE ：遇到无法转换字符跳过*/
  char *encTo = "UTF-8//IGNORE";
/* 源编码 */
  char *encFrom = "UNICODE";

  /* 获得转换句柄
   *@param encTo 目标编码方式
   *@param encFrom 源编码方式
   *
   * */
  iconv_t cd = iconv_open (encTo, encFrom);
  if (cd == (iconv_t)-1)
  {
     perror ("iconv_open");
  }

  /* 需要转换的字符串 */
  printf("inbuf=%s\n", inbuf);

  /* 打印需要转换的字符串的长度 */
  printf("inlen=%d\n", *inlen);


  /* 由于iconv()函数会修改指针，所以要保存源指针 */
  char *tmpin = inbuf;
  char *tmpout = outbuf;
  size_t insize = *inlen;
  size_t outsize = *outlen;

  /* 进行转换
   *@param cd iconv_open()产生的句柄
   *@param srcstart 需要转换的字符串
   *@param inlen 存放还有多少字符没有转换
   *@param tempoutbuf 存放转换后的字符串
   *@param outlen 存放转换后,tempoutbuf剩余的空间
   *
   * */
  size_t ret = iconv (cd, &tmpin, inlen, &tmpout, outlen);
  if (ret == -1)
  {
     perror ("iconv");
  }

  /* 存放转换后的字符串 */
  printf("outbuf=%s\n", outbuf);

  //存放转换后outbuf剩余的空间
  printf("outlen=%d\n", *outlen);

  int i = 0;

  for (i=0; i<(outsize- (*outlen)); i++)
  {
     //printf("%2c", outbuf[i]);
     printf("%x\n", outbuf[i]);
  }

  /* 关闭句柄 */
  iconv_close (cd);

  return 0;
}

bool utf8_to_unicode (char *inbuf, size_t *inlen, char *outbuf, size_t *outlen)
{

  /* 目的编码, TRANSLIT：遇到无法转换的字符就找相近字符替换
   *           IGNORE ：遇到无法转换字符跳过*/
  char *encTo = "UNICODE//IGNORE";
  /* 源编码 */
  char *encFrom = "UTF-8";

  /* 获得转换句柄
   *@param encTo 目标编码方式
   *@param encFrom 源编码方式
   *
   * */
  iconv_t cd = iconv_open (encTo, encFrom);
  if (cd == (iconv_t)-1)
  {
      perror ("iconv_open");
  }

  /* 需要转换的字符串 */
  printf("inbuf=%s\n", inbuf);

  /* 打印需要转换的字符串的长度 */
  printf("inlen=%d\n", *inlen);

  /* 由于iconv()函数会修改指针，所以要保存源指针 */
  char *tmpin = inbuf;
  char *tmpout = outbuf;
  size_t insize = *inlen;
  size_t outsize = *outlen;

  /* 进行转换
   *@param cd iconv_open()产生的句柄
   *@param srcstart 需要转换的字符串
   *@param inlen 存放还有多少字符没有转换
   *@param tempoutbuf 存放转换后的字符串
   *@param outlen 存放转换后,tempoutbuf剩余的空间
   *
   * */
  size_t ret = iconv (cd, &tmpin, inlen, &tmpout, outlen);
  if (ret == -1)
  {
     perror ("iconv");
  }

  /* 存放转换后的字符串 */
  printf("outbuf=%s\n", outbuf);

  //存放转换后outbuf剩余的空间
  printf("outlen=%d\n", *outlen);

  int i = 0;

  for (i=0; i<(outsize- (*outlen)); i++)
  {
     //printf("%2c", outbuf[i]);
     printf("%x\n", outbuf[i]);
  }

  /* 关闭句柄 */
  iconv_close (cd);

  return 0;
}

int main ()
{
  /* 需要转换的字符串 */
  //char inbuf[1024] = "abcdef哈哈哈哈行"; 
  char *text = "在不";    
    
  char inbuf[1024] = {};
  strcpy (inbuf, text);
  size_t inlen = strlen (inbuf);

  /* 存放转换后的字符串 */
  char outbuf[1024] = {};
  size_t outlen = 1024;

  utf8_to_unicode (inbuf, &inlen, outbuf, &outlen);
  printf ("print outbuf: %s\n", outbuf);
  //鍦ㄤ笉

  size_t outsize = strlen(outbuf);
  size_t insize = 1024;
  char instr[1024] = {};
  unicode_to_utf8 (outbuf, &outsize, instr, &insize);
  printf ("print buf: %s\n", instr);
  
  char *in = "氓\u009c篓盲赂\u00 ";
  char inbuf1[1024] = {};
  strcpy (inbuf1, in);
  size_t inlen1 = strlen (inbuf1);
  /* 存放转换后的字符串 */
  char outbuf1[1024] = {};
  size_t outlen1 = 1024;  
  unicode_to_utf8 (inbuf1, &inlen1, outbuf1, &outlen1);
  printf ("print outbuf1: %s\n", outbuf1);  
  
  
  
  return 0;
}