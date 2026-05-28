/*
 * @lc app=leetcode.cn id=55 lang=c
 *
 * [55] 跳跃游戏
 */

// @lc code=start
#include <stdbool.h>

bool canJump(int* nums, int numsSize)
{
    // 处理错误情况
    if (!nums || numsSize < 1) return false;

    // 处理特殊情况
    if (numsSize == 1) return true;

    int* times = (int*)malloc(sizeof(int) * numsSize);
    if (!times) return false;

    times[numsSize - 1] = 0;    // 索引为 numsSize - 1 时到 numsSize - 1 不需要跳数

    for (int i = numsSize - 2; i >= 0; i--)
    {
        if (nums[i] == 0)   // 当 nums[i] 为 0 时, 其无法移动故不可达
        {
            times[i] = -1;   // 将 -1 设置为不可达
        }
        else if (nums[i] + i >= numsSize - 1)
        {
            times[i] = 1;
        }
        else
        {
            int minTimes = numsSize - 1 - i;   // 每次仅跳一个索引(理论最大)
            bool reachable = false;
            for (int jumpLength = 1; jumpLength <= nums[i]; jumpLength++)
            {
                if (times[i + jumpLength] < 0) continue;   // 若小于零表示不可达, 跳过
                reachable = true;   // 只要有一个能够到达就改为 true
                minTimes = times[i + jumpLength] + 1 < minTimes ? times[i + jumpLength] + 1 : minTimes;
                // 若当前跳数更少, 则更新计数器 minTimes
                // 否则不进行操作
            }
            times[i] = reachable ? minTimes : -1;
            // 如果可达将最小跳数添加入 times 表中
            // 否则将 times[i] 设值为 -1 (不可达)
        }

    }
    bool result = times[0] == -1 ? false : true;   // 将结果复制出来
    free(times);   // 释放内存

    return result;
}
// @lc code=end

