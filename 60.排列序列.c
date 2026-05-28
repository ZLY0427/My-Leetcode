/*
 * @lc app=leetcode.cn id=60 lang=c
 *
 * [60] 排列序列
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* getPermutation(int n, int k)
{
    // 预计算阶乘: fact[i] = i!
    int fact[10] = {1};   // 0 ~ 9 的阶乘
    for (int i = 1; i <= n; ++i)
    {
        fact[i] = fact[i - 1] * i;
    }

    // 可用数字：1 到 n，用布尔数组标记是否已使用
    bool used[10] = {false};

    // 分配结果字符串，长度 n + 1
    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[n] = '\0';

    k--;

    // 逐位确定
    for (int i = 0; i < n; ++i)
    {
        int remaining = n - i - 1;   // 剩余位置数
        int blockSize = fact[remaining];   // 每个前缀对应的排列数

        int index = k / blockSize;   // 在当前可用数字中选第 index 个（0-based）
        k %= blockSize;

        // 在 1 ~ n 中找第 index 个未使用的数字
        int count = 0;
        for (int num = 1; num <= n; ++num)
        {
            if (!used[num])
            {
                if (count == index)
                {
                    used[num] = true;
                    result[i] = '0' + num;
                    break;
                }
                count++;
            }
        }
    }

    return result;
}
// @lc code=end

