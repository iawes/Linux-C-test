/*===============================================================
*   文件名称：aes.c
*   创建日期：2016年11月15日
================================================================*/
#include <stdio.h>
#include "openssl/aes.h"

static const unsigned char key[] = "94c595255f61a542cb4c9231e066cd89";

void get_hex_string(char *buf,unsigned char orig[], int len)
{
    int i=0;

    for(i=0; i<len; i++)
    {
        sprintf(buf+2*i,"%02x",orig[i]);
    }
}

void get_hex_string2(char *buf,unsigned char orig[])
{
    int i=0;

    for(i=0;*(orig+i)!=0x00;i++)
    {
        sprintf(buf+2*i,"%02x",orig[i]);
    }
}

int main()
{
    unsigned char text[]="hello world!";
    unsigned char enc_out[80];
    unsigned char dec_out[80];

    AES_KEY enc_key, dec_key;
	
	printf("text = %s\n", text);	

    AES_set_encrypt_key(key, 256, &enc_key);
    AES_encrypt(text, enc_out, &enc_key);
	
    char enc_out_str[128] = {0};
    get_hex_string(enc_out_str, enc_out, 32);
    printf("enc_out_str = %s.\n", enc_out_str);	

    AES_set_decrypt_key(key,256,&dec_key);
    AES_decrypt(enc_out, dec_out, &dec_key);
	
    char dec_out_str[128] = {0};
    get_hex_string(dec_out_str, dec_out, 32);
    printf("dec_out_str = %s.\n", dec_out_str);
	
		//test2
//char enc_out_str[128] = {0};
    get_hex_string2(enc_out_str, enc_out);
    printf("enc_out_str = %s.\n", enc_out_str);		
    //char dec_out_str[128] = {0};
    get_hex_string2(dec_out_str, dec_out);
    printf("dec_out_str = %s.\n", dec_out_str);
	
   int i;

    printf("original:\t");
    for(i=0;*(text+i)!=0x00;i++)
        printf("%X ",*(text+i));
    printf("\nencrypted:\t");
    for(i=0;*(enc_out+i)!=0x00;i++)
        printf("%X ",*(enc_out+i));
    printf("\ndecrypted:\t");
    for(i=0;*(dec_out+i)!=0x00;i++)
        printf("%X ",*(dec_out+i));
    printf("\n");	
	
    return 0;
}
