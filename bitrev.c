/*
@file: bit_reverse.c
@author: ZZH
@date: 2022-11-28
@info: 位反转工具
*/
#include "common.h"

const char* usage = "usage: bit_reverse <number> <bit-length>";

int main(const int argc, const char** argv)
{
    if (argc < 3) {
        puts(usage);
        return -1;
    }

    uint32_t num = 0, len = 0;

    if (!getNum(argv[1], &num))
        printf("%s is not a valid number\r\n", argv[1]);

    if (!getNum(argv[2], &len))
        printf("%s is not a valid number\r\n", argv[2]);

    uint32_t r = reverseBits(num, len);
    printf("%d(%#02X) - %d(%#02X)\r\n", num, num, r, r);

    return 0;
}
