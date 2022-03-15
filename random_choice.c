#include <stdio.h>

int main(int argc, const char** argv)
{
    if (argc > 1)
    {
        // printf("argc: %d\r\n", argc);
        // for (int i = 0;i < argc;i++)
        //     printf("argc[%d]: %s\r\n", i, argv[i]);
        argc -= 1;
        size_t random = 0;
        asm("rdrand %0":"=r"(random));
        printf("select: %s\r\n", argv[(random % argc) + 1]);
    }

    return 0;
}
