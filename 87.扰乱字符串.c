/*
 * @lc app=leetcode.cn id=87 lang=c
 *
 * [87] 扰乱字符串
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isScramble(char* s1, char* s2)
{
    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    
    // 长度不同直接返回 false
    if (s1Size != s2Size) return false;

    int n = s1Size;

    // 两个字符串完全相同直接返回 true
    if (strcmp(s1, s2) == 0) return true;

    // 统计字符频率，字符不同直接返回 false
    int count[26] = {0};
    for (int i = 0; i < n; ++i)
    {
        ++count[s1[i] - 'a'];
        --count[s2[i] - 'a'];
    }
    for (int i = 0; i < 26; ++i)
        if (count[i] != 0) return false;

    // 三维 dp 数组：dp[i][j][k] = s1[i..i+k-1] 和 s2[j..j+k-1] 是否是扰乱字符串
    bool dp[n][n][n + 1];
    // 初始化 dp 为 false
    memset(dp, 0, sizeof(dp));

    // 初始化：长度为 1 的情况
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dp[i][j][1] = (s1[i] == s2[j]);

    // 枚举子串长度：从 2 到 n
    for (int len = 2; len <= n; len++)
        // 枚举 s1 的起始位置
        for (int i = 0; i + len <= n; i++)
            // 枚举 s2 的起始位置
            for (int j = 0; j + len <= n; j++)
                // 枚举分割点：把长度为 len 的串分成 t 和 len-t 两部分
                for (int t = 1; t < len; t++)
                {
                    // 情况1：不交换 → 前半段匹配前半段，后半段匹配后半段
                    bool noSwap = dp[i][j][t] && dp[i + t][j + t][len - t];
                    // 情况2：交换 → 前半段匹配后半段，后半段匹配前半段
                    bool swap = dp[i][j + len - t][t] && dp[i + t][j][len - t];
                    
                    if (noSwap || swap)
                    {
                        dp[i][j][len] = true;
                        break; // 找到一种满足即可，无需继续判断
                    }
                }

    return dp[0][0][n];
}
// @lc code=end

