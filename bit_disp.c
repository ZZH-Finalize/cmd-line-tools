/*
@file: bit_disp.c
@author: ZZH
@date: 2023-05-29
@info: 位显示工具
*/
#include "common.h"

const char* usage = "usage: bit_disp <number1> <number2> ...";

int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        puts(usage);
        return -1;
    }

    uint32_t value = 0;

    for (size_t i = 1; i < argc; i++)
    {
        const char *pArg = argv[i];
        if (0 != getNum(pArg, &value))
        {
            printf("%s: ", pArg);
            for (uint32_t offset = 0;offset < 32;offset++)
            {
                if (0 != (value & (1 << offset)))
                    printf("%d, ", offset);
            }
            printf("\b\b  \n");
        }
        else
        {
            printf("%s is not a valid number\r\n", pArg);
        }
    }

    return 0;
}
