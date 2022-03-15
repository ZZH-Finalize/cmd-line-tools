#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    const char* varPath = getenv("PATH");
    while (*varPath)
    {
        putchar(*varPath == ':' ? '\n' : *varPath);
        varPath++;
    }
}
