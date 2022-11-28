#include "common.h"

int main(const int args, const char** argv)
{
    uint32_t value = 0;
    for (int i = 1;i < args;i++)
    {
        // printf("%s\r\n", argv[i]);
        uint32_t bitPos = 0;
        if (getNum(argv[i], &bitPos))//转换成功
            value |= 1 << bitPos;
        else
            printf("%s is not a valid number\r\n", argv[i]);
    }
    printf("Final Result: %u - %#X\r\n", value, value);
    return 0;
}
