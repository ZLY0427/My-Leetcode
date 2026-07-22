/*
 * @lc app=leetcode.cn id=135 lang=c
 *
 * [135] ·Ö·¢ÌÇ¹û
 */

// @lc code=start
#include <stdlib.h>

int getSum(int* arr, int size);

int candy(int* ratings, int ratingsSize)
{
    int* need = (int*)calloc(ratingsSize, sizeof(int));
    need[0] = 1;

    for (int i = 1; i < ratingsSize; ++i)
        need[i] = (ratings[i] > ratings[i - 1]) ? (need[i - 1] + 1) : 1;

    for (int i = ratingsSize - 2; i >= 0; --i)
        need[i] = (ratings[i] > ratings[i + 1]) ? ((need[i] > need[i + 1] + 1) ? need[i] : (need[i + 1] + 1)) : need[i];
    
    int sum = getSum(need, ratingsSize);
    free(need);

    return sum;
}

int getSum(int* arr, int size)
{
    int sum = arr[0];
    for (int i = 1; i < size; ++i)
        sum += arr[i];
    return sum;
}
// @lc code=end

