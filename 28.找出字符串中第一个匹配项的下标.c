/*
 * @lc app=leetcode.cn id=28 lang=c
 *
 * [28] 找出字符串中第一个匹配项的下标
 */

// @lc code=start
// BF算法
/*
#include <stdbool.h>
#include <string.h>

int strStr(char* haystack, char* needle)
{
    int len1 = strlen(haystack);
    int len2 = strlen(needle);

    if ((len1 <= 0) || (len2 <= 0) || (len1 < len2))
    {
        return -1;
    }

    for (int i = 0; i < len1; i++)
    {
        bool is_same = true;
        if (haystack[i] == needle[0])
        {
            for (int j = 1; j < len2; j++)
            {
                if (haystack[i + j] != needle[j])
                {
                    is_same = false;
                    break;
                }
            }
            if (is_same)
            {
                return i;
            }
        }
    }
    return -1;
}
*/

// KMP算法
#include <string.h>
#include <stdlib.h>

int* getNext(const char* needle);
int kmp(char* str, char* pattern);

int strStr(char* haystack, char* needle)
{
    return kmp(haystack, needle);
}

int kmp(char* str, char* patten)
{
    int* next = getNext(patten);
    int s_size = strlen(str), p_size = strlen(patten);
    int sCur = 0, pCur = 0;

    while (sCur < s_size && pCur < p_size)
    {
        if (str[sCur] == patten[pCur])
        {
            sCur++;
            pCur++;
        }
        else if (pCur > 0)
        {
            pCur = next[pCur];
        }
        else
        {
            sCur++;
        }
    }

    return pCur == p_size ? sCur - p_size : -1;
}

int* getNext(const char* str)
{
    int size = strlen(str);
    if (size < 2) return NULL;
    int* next = (int*)malloc(sizeof(int) * size);
    next[0] = next[1] = 0;
    int comp = 0, cur = 2;

    while (cur < size)
    {
        if (str[cur - 1] == str[comp])
        {
            next[cur] = comp + 1;
            cur++;
            comp++;
        }
        else if (comp > 0)
        {
            comp = next[comp];
        }
        else
        {
            next[cur++] = 0;
        }
    }

    return next;
}
// @lc code=end

