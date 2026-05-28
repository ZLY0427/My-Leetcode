/*
 * @lc app=leetcode.cn id=123 lang=c
 *
 * [123] 买卖股票的最佳时机 III
 */

// @lc code=start
#include <limits.h>

int maxProfit(int* prices, int pricesSize)
{
    if (!prices || pricesSize < 1) return -1;
    if (pricesSize == 1) return 0;

    // 定义4个状态变量，初始化为极小值（INT_MIN）
    // buy1：第一次买入股票后的最大利润
    // sell1：第一次卖出股票后的最大利润
    // buy2：第二次买入股票后的最大利润
    // sell2：第二次卖出股票后的最大利润
    int buy1 = INT_MIN;
    int sell1 = 0;
    int buy2 = INT_MIN;
    int sell2 = 0;

    // 遍历所有价格，更新状态
    for (int i = 0; i < pricesSize; ++i)
    {
        // 第一次买入：要么不操作，要么今天买入（利润 = -当前价格）
        buy1 = (buy1 > -prices[i]) ? buy1 : -prices[i];
        // 第一次卖出：要么不操作，要么卖出第一次买入的股票（利润 = 第一次买入利润 + 当前价格）
        sell1 = (sell1 > buy1 + prices[i]) ? sell1 : buy1 + prices[i];
        // 第二次买入：要么不操作，要么用第一次卖出的利润买入（利润 = 第一次卖出利润 - 当前价格）
        buy2 = (buy2 > sell1 - prices[i]) ? buy2 : sell1 - prices[i];
        // 第二次卖出：要么不操作，要么卖出第二次买入的股票（利润 = 第二次买入利润 + 当前价格）
        sell2 = (sell2 > buy2 + prices[i]) ? sell2 : buy2 + prices[i];
    }

    // 最终最大利润一定是第二次卖出（可以只卖1次，sell2会自动取最大值）
    return sell2;
}
// @lc code=end

