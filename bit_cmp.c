/*
@file: bit_cmp.c
@author: ZZH
@date: 2022-12-06
@info: 位比较工具
*/
#include "common.h"

int main(const int argc, const char** argv)
{
    if (argc < 3)
        return -1;

    uint32_t num1 = 0, num2 = 0;

    if (!getNum(argv[1], &num1))
        printf("%s is not a valid number\r\n", argv[1]);

    if (!getNum(argv[2], &num2))
        printf("%s is not a valid number\r\n", argv[2]);

    typeof(num1) mask = num1 ^ num2;
    char buf[128];
    uint32_t len = 0;

    for (typeof(mask) i = 0;i < sizeof(mask) * 8 && mask>0;i++)
    {
        if (mask & 0x01)
            len += sprintf(&buf[len], "%d, ", i);
        mask >>= 1;
    }

    if (0 != len)
    {
        buf[len - 2] = '\0';
        puts(buf);
    }

    return 0;
}
