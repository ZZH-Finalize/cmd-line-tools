/*
@file: bit_disp.c
@author: ZZH
@date: 2023-05-29
@info: 位显示工具
*/
#include <errno.h>
#include "common.h"

const char* usage = "usage: bitdsp <number1> <number2> ...";

int main(const int argc, const char** argv)
{
    if (argc < 2) {
        puts(usage);
        return -EPERM;
    }

    uint32_t value = 0;
    char buf[128]; // maxminum char number is nearly 118 chars

    for (int i = 1; i < argc; i++) {
        const char* pArg = argv[i];
        char* pBuf = buf;

        if (0 != getNum(pArg, &value)) {
            printf("%s: ", pArg);

            for (uint32_t offset = 0; offset < 32; offset++) {
                if (0 != (value & 0x01)) {
                    size_t remaining = sizeof(buf) - (size_t) (pBuf - buf);
                    int n = snprintf(pBuf, remaining, "%d, ", offset);
                    if (n < 0 || (size_t) n >= remaining) {
                        printf("serialize error\r\n");
                        return -EFAULT;
                    }

                    pBuf += n;
                }

                value >>= 1;

                if (0 == value) { // last bit is already handled
                    pBuf[-2] = '\0';
                    break;
                }
            }

            puts(buf);
        } else {
            printf("%s is not a valid number\r\n", pArg);
        }
    }

    return 0;
}
