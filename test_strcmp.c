#include <stdio.h>

int main(void)
{
    char MAC_1[32] = "44C346F1234D";
    char MAC_2[32] = "00E04C3601F2";
    
    int flag = 0;
    
    if(0x00 == strcmp(MAC_1, MAC_2)
    {
        flag = 1;
    }
        
    if(flag)
    {
        printf("mac:%s has been in g_gdbus_lanhoststatics_list.\n", MAC_1);
        return 0;
    }
    
    printf("mac:%s has not been in g_gdbus_lanhoststatics_list.\n", MAC_1);

    return 0;
}