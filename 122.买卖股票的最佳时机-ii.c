/*
 * @lc app=leetcode.cn id=122 lang=c
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
int maxProfit(int* prices, int pricesSize)
{
    if (!prices || pricesSize <= 0) return -1;
    if (pricesSize == 1) return 0;

    int max = 0, now = 0;
    
    for (int i = 1; i < pricesSize; ++i)
    {
        if (prices[i] > prices[i - 1])
            now += prices[i] - prices[i - 1];
        else
        {
            max += now;
            now = 0;
        }
    }

    return max + now;
}
// @lc code=end

