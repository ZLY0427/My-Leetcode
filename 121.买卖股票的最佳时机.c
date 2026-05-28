/*
 * @lc app=leetcode.cn id=121 lang=c
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
#include <stdlib.h>

int maxProfit(int* prices, int pricesSize)
{
    if (!prices || pricesSize <= 0) return -1;
    if (pricesSize == 1) return 0;

    int* left = (int*)malloc(sizeof(int) * pricesSize);
    int* right = (int*)malloc(sizeof(int) * pricesSize);
    if (!left || !right)
    {
        free(left);
        free(right);
        return -1;
    }

    left[0] = prices[0];
    right[pricesSize - 1] = prices[pricesSize - 1];

    for (int i = 1; i < pricesSize; ++i)
    {
        left[i] = (prices[i] < left[i - 1]) ? prices[i] : left[i - 1];
        right[pricesSize - i - 1] = (prices[pricesSize - i - 1] > right[pricesSize - i]) ? prices[pricesSize - i - 1] : right[pricesSize - i];
    }

    int max = 0;
    for (int i = 0; i < pricesSize; ++i)
        max = (max > right[i] - left[i]) ? max : right[i] - left[i];

    free(left);
    free(right);
    
    return max;
}
// @lc code=end

