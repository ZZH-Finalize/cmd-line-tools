#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
@brief 检查输入的格式字符串是否符合要求,要求为,在整个格式字符串中,只允许出现一次%s用于匹配输入,若要输出%本身可使用%%,并且不限次数
@param fmt 格式字符串
@return 0 不合格 1 合格
*/
static uint8_t CheckFmt(const char* fmt)
{
    if (NULL == fmt)
        return 0;

    int len = strlen(fmt) - 1, num = 0;
    for (int i = 0;i < len && num < 2;i++)
    {
        if ('%' == fmt[i])
        {
            switch (fmt[i + 1])
            {
                case '%':
                    i++;
                    break;

                case 's':
                    num++;
                    break;

                default:
                    return 0;
            }
        }
    }

    return num < 2;
}


int main(const int argc, const char** argv)
{
    char* fmt = (char*) malloc(1024 * 4);

    if (fmt)
    {
        printf("please input a format string: ");
        gets(fmt);

        if (CheckFmt(fmt))
        {
            for (int i = 1;i < argc;i++)
            {
                const char* pCurStr = argv[i];
                const char* pEndCur = pCurStr + strlen(pCurStr);

                do
                {
                    char* index = strchr(pCurStr, ' ');
                    // printf("cur: %p, index: %p\r\n", pCurStr, index);

                    if (NULL != index)//一个字符串包含多个参数
                    {
                        size_t splitLen = (size_t) index - (size_t) pCurStr;
                        char* newBuf = (char*) malloc(splitLen + 1);

                        if (!newBuf)
                            continue;

                        newBuf[splitLen] = '\0';
                        memcpy(newBuf, pCurStr, splitLen);
                        printf(fmt, newBuf);
                        free(newBuf);
                        pCurStr += splitLen + 1;
                    }
                    else//单独的参数,直接输出即可
                    {
                        printf(fmt, pCurStr);
                        pCurStr = pEndCur;
                    }

                } while (pCurStr < pEndCur);
            }
        }
        else
        {
            printf("format string: \"%s\" is not vaild\r\n", fmt);
        }
    }

    free(fmt);
    return 0;
}
