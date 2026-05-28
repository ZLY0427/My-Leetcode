/*
 * @lc app=leetcode.cn id=50 lang=c
 *
 * [50] Pow(x, n)
 */

// @lc code=start
#include <stdio.h>

double myPow(double x, int n)
{
    if (x == 0 && n <= 0)   // 特殊情况
    {
        printf("错误, 输出结果不可信.\n");
        return 0;
    }

    if (n == 0) return 1;   // 处理 n == 0 的特殊情况

    int size = n >= 0 ? n - 1 : -(n + 1);   // 防止越界
    double now_x = x;   // 当前使用的底数
    double result = x;   // 结果

    while (size > 0)
    {
        if (size % 2 == 1)   // 判断当前大小的底数是否有剩余, 
        {                    // 若有则添加到 result 中
            result *= now_x; // 若无则跳过该步骤
            size--;
        }

        while (size > 0 && size % 2 == 0)
        {
            now_x *= now_x;
            size /= 2;
        }
    }

    for (int i = 0; i < size; i++)
    {
        result *= now_x;
    }

    return n >= 0 ? result : 1 / result;
}

// @lc code=end

