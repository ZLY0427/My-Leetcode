/*
 * @lc app=leetcode.cn id=75 lang=c
 *
 * [75] —’…´∑÷¿‡
 */

// @lc code=start
/*
void Sort(int* nums, int numsSize);
void MergeSort(int* nums, int left, int right, int* tempArr);

void sortColors(int* nums, int numsSize)
{
    Sort(nums, numsSize);
}

void Sort(int* nums, int numsSize)
{
    if (numsSize <= 1) return;
    int* tempArr = (int*)malloc(sizeof(int) * numsSize);

    MergeSort(nums, 0, numsSize - 1, tempArr);
    free(tempArr);
}

void MergeSort(int* nums, int left, int right, int* tempArr)
{
    if (left >= right) return ;
    int middle = (left + right) / 2;

    MergeSort(nums, left, middle, tempArr);
    MergeSort(nums, middle + 1, right, tempArr);

    int index = left;
    int low = left, high = middle + 1;
    while (low <= middle && high <= right && index <= right)
    {
        if (nums[low] <= nums[high])
            tempArr[index++] = nums[low++];
        else
            tempArr[index++] = nums[high++];
    }

    while (low <= middle && index <= right)
        tempArr[index++] = nums[low++];

    while (high <= right && index <= right)
        tempArr[index++] = nums[high++];

    for (index = left; index <= right; index++)
        nums[index] = tempArr[index];
}
*/

void sortColors(int* nums, int numsSize)
{
    int redCount = 0, whiteCount = 0, blueCount = 0;

    for (int index = 0; index < numsSize; index++)
        if (nums[index] == 0) redCount++;
        else if (nums[index] == 1) whiteCount++;
        else if (nums[index] == 2) blueCount++;
        else return ;

    int index = 0;
    
    int redNumber = redCount;
    while (index < redNumber) nums[index++] = 0;
    
    int whiteNumber = redCount + whiteCount;
    while (index < whiteNumber) nums[index++] = 1;
    
    int blueNumber = redCount + whiteCount + blueCount;
    while (index < blueNumber) nums[index++] = 2;
}
// @lc code=end

