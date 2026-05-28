/*
 * @lc app=leetcode.cn id=38 lang=c
 *
 * [38] 外观数列
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

char* countAndSay(int n)
{
    if (n < 1) return NULL;   // 处理错误情况
    else if (n == 1)   // 处理特殊情况
    {
        char* returnFor1 = (char*)malloc(sizeof(char) * 2);
        returnFor1[0] = '1';
        returnFor1[1] = '\0';
        return returnFor1;
    }
    char* str = countAndSay(n - 1);   // 递归获取数组
    int strSize = strlen(str);   // 获取数组长度

    char* buffer = (char*)malloc(sizeof(char) * (strSize * 2 + 1));   // 缓冲区
    if (!buffer)   // 处理内存失败的情况
    {
        free(str);
        return NULL;
    }
    buffer[2 * strSize] = '\0';   // 添加结束符(好像不加也行)
    int index = 0;   // 建立索引, 同时这也是数组实际的大小
    // 主体循环
    for (int i = 0; i < strSize;)
    {
        int count = 1;
        int j = i + 1;

        while (j < strSize && str[j] == str[i])
        {
            count++;
            j++;
        }

        buffer[index++] = '0' + count;
        buffer[index++] = str[i];

        i = j;
    }

    // 重新分配大小
    char* result = (char*)realloc(buffer, sizeof(char) * (index + 1));
    if (!result)   // 处理内存分配失败的情况
    {
        free(str);
        return NULL;
    }
    else
        result[index] = '\0';   // 添加结束符(不能少)
    
    free(str);
    return result;
}
// @lc code=end

