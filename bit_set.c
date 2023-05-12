#include "common.h"

int main(const int args, const char** argv)
{
    uint32_t value = 0;
    char pArg[32];
    for (int i = 1;i < args;i++)
    {
        snprintf(pArg, sizeof(pArg), "%s", argv[i]);
        uint32_t bitPos1 = 0, bitPos2 = 0;
        // printf("%s\r\n", argv[i]);
        char* dashPos = strchr(pArg, '-');
        if (NULL != dashPos && dashPos != pArg)
        {
            *dashPos = '\0';//split str into two parts
            uint8_t res = getNum(pArg, &bitPos1);
            res &= getNum(dashPos + 1, &bitPos2);

            if (res && IsInCloseRange(bitPos1, 0, 31) && IsInCloseRange(bitPos2, 0, 31))
            {
                if (bitPos1 > bitPos2)
                    swap(bitPos1, bitPos2);

                // printf("bitPos1:%d, bitPos2:%d\r\n", bitPos1, bitPos2);

                uint32_t bitMask = 1 << bitPos1;

                for (int i = bitPos1;i <= bitPos2;i++)
                {
                    value <<= 1;
                    value |= bitMask;
                }
            }
            else
            {
                *dashPos = '-';
                printf("%s is not a vaild field\r\n", pArg);
            }
        }
        else
        {
            
            if (getNum(pArg, &bitPos1))//转换成功
                value |= 1 << bitPos1;
            else
                printf("%s is not a valid number\r\n", pArg);
        }

    }
    printf("Final Result: %u - %#X\r\n", value, value);
    return 0;
}
