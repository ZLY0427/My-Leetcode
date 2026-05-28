/*
 * @lc app=leetcode.cn id=3 lang=c
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

int lengthOfLongestSubstring(char* s)
{
    // 变量声明
    int maxlen = 0;
    int size = strlen(s);

    // 函数主体
    for (int i = 0; i < size; i++)
    {
        int len = 1;
        for (int j = i + 1; j < size; j++)
        {
            bool is_sime = false;
            for (int k = i; k < j; k++)
            {
                // 判断是否有相同
                if (s[k] == s[j])
                {
                    is_sime = true;
                    break;
                }
            }
            if (is_sime)
            {
                break;
            }
            else
            {
                len++;
            }
        }

        // 更新最大长度
        if (maxlen < len)
        {
            maxlen = len;
        }
    }
    return maxlen;
}
// @lc code=end
