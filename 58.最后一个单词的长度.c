/*
 * @lc app=leetcode.cn id=58 lang=c
 *
 * [58] 最后一个单词的长度
 */

// @lc code=start
#include <stdbool.h>
#include <string.h>

int lengthOfLastWord(char* s)
{
    int last_len = 0;
    bool is_lastword = false;

    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (!is_lastword)
        {
            if (s[i] != ' ')
            {
                last_len++;
                is_lastword = true;
            }
        }
        else
        {
            if (s[i] == ' ')
            {
                break;
            }
            else
            {
                last_len++;
            }
        }
    }
    return last_len;
}
// @lc code=end

