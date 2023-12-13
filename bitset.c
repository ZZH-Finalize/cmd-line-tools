#include "common.h"

const char* usage = "usage: bitset <number1> <number2> ...";

#define DISP_CHAR(ch) printf(#ch ": %c(0x%02X)\r\n", ch == '\n' ? '\\' : ch, ch)

int main(const int argc, const char** argv)
{
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    char pipe_char = getchar();

    if ((argc < 2) && (EOF == pipe_char)) {
        puts(usage);
        return -1;
    }

    uint32_t value = 0;
    char pArg[32];

    for (int i = 1; i < argc; i++) {
        snprintf(pArg, sizeof(pArg), "%s", argv[i]);
        uint32_t bitPos1 = 0, bitPos2 = 0;
        // printf("%s\r\n", argv[i]);
        char* dashPos = strchr(pArg, '-');
        if (NULL != dashPos && dashPos != pArg) {
            *dashPos = '\0'; // split str into two parts
            uint8_t res = getNum(pArg, &bitPos1);
            res &= getNum(dashPos + 1, &bitPos2);

            if (res && bitPos1 <= 31 && bitPos2 <= 31) {
                if (bitPos1 > bitPos2)
                    swap(bitPos1, bitPos2);

                // printf("bitPos1:%d, bitPos2:%d\r\n", bitPos1, bitPos2);
                uint64_t tmp = 1;
                tmp <<= bitPos2 - bitPos1 + 1;
                value |= (tmp - 1) << bitPos1;
            } else {
                *dashPos = '-';
                printf("%s is not a vaild field\r\n", pArg);
            }
        } else {
            if (getNum(pArg, &bitPos1)) // 转换成功
                value |= 1 << bitPos1;
            else
                printf("%s is not a valid number\r\n", pArg);
        }
    }

    while (':' != pipe_char) pipe_char = getchar();

    char num_buf[] = {"0x00000000"};
    char* pnum_buf = num_buf;

    for (pipe_char = getchar(); EOF != pipe_char; pipe_char = getchar()) {
        if ((' ' != pipe_char) && (',' != pipe_char) && ('\r' != pipe_char)
            && ('\n' != pipe_char)) {
            *pnum_buf++ = pipe_char;
        } else if (pnum_buf != num_buf) {
            *pnum_buf = '\0';
            // printf("numbuf: %s\r\n", num_buf);
            uint32_t bit_pos = 0;

            if (getNum(num_buf, &bit_pos)) {
                value |= 1 << bit_pos;
            } else {
                printf("%s is not a valid number\r\n", num_buf);
            }

            pnum_buf = num_buf;
        }
    }

    printf("Final Result: %u - %#X\r\n", value, value);

    return 0;
}
