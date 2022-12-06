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

    typeof(num1) mask = num1 & num2;

    if (mask & 0x01)
        putchar('0');
    mask >>= 1;

    for (typeof(mask) i = 1;i < sizeof(mask) * 8 && mask>0;i++)
    {
        if (mask & 0x01)
            printf(", %d", i);
        mask >>= 1;
    }

    return 0;
}
