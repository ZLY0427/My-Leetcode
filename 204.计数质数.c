/*
 * @lc app=leetcode.cn id=204 lang=c
 *
 * [204] 计数质数
 */

// @lc code=start

#include <stdlib.h>
#include <stdbool.h>

int countPrimes(int n)
{
    int result = 0;
    bool* isPrime = (bool*)calloc(n, sizeof(bool));

    for (int i = 2; i < n; ++i)
        if (!isPrime[i])
        {
            ++result;
            if ((long long)i * i < n)
            {
                for (int j = i * i; j < n; j += i)
                    isPrime[j] = true;
            }
        }

    free(isPrime);
    return result;
}

// @lc code=end

