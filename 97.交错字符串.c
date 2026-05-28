/*
 * @lc app=leetcode.cn id=97 lang=c
 *
 * [97] 交错字符串
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool** create_bool_array(int i, int j);
void free_bool_array(bool** arr, int rows);

bool isInterleave(char* s1, char* s2, char* s3)
{
    if (!s1 || !s2 || !s3) return false;

    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    int s3Size = strlen(s3);

    if (s1Size + s2Size != s3Size) return false;

    // interlace[i][j]表示s1的前i个字符与s2的前j个字符是否能够组成s3的前i + j个字符
    bool** interlace = create_bool_array(s1Size + 1, s2Size + 1);
    if (!interlace) return false;

    interlace[0][0] = true;

    for (int i = 1; i <= s1Size; i++)
        interlace[i][0] = interlace[i - 1][0] && s1[i - 1] == s3[i - 1];
    for (int j = 1; j <= s2Size; j++)
        interlace[0][j] = interlace[0][j - 1] && s2[j - 1] == s3[j - 1];

    for (int i = 1; i <= s1Size; i++)
        for (int j = 1; j <= s2Size; j++)
            interlace[i][j] = (interlace[i-1][j] && s1[i-1] == s3[i+j-1]) ||
                              (interlace[i][j-1] && s2[j-1] == s3[i+j-1]);

    bool result = interlace[s1Size][s2Size];

    free_bool_array(interlace, s1Size);

    return result;
}

bool** create_bool_array(int i, int j)
{
    bool** arr = (bool**)malloc(sizeof(bool*) * i);
    if (!arr) return NULL;

    for (int r = 0; r < i; r++)
    {
        arr[r] = (bool*)calloc(j, sizeof(bool));
        if (!arr[r])
        {
            for (int k = 0; k < r; k++)
                free(arr[k]);
            free(arr);
            return NULL;
        }
    }

    return arr;
}

void free_bool_array(bool** arr, int rows)
{
    if (!arr) return;
    for (int r = 0; r <= rows; r++)
        free(arr[r]);
    free(arr);
}
// @lc code=end



/*
bool interleave(char* s1, char* s2, char* s3,
            int index1, int index2, int index3,
            int s1Size, int s2Size, int s3Size,
            int choose);

bool isInterleave(char* s1, char* s2, char* s3)
{
    if (!s1 || !s2 || !s3) return false;

    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    int s3Size = strlen(s3);

    if (s1Size + s2Size != s3Size) return false;

    return interleave(s1, s2, s3, 0, 0, 0, s1Size, s2Size, s3Size, 1) ||
           interleave(s1, s2, s3, 0, 0, 0, s1Size, s2Size, s3Size, 2);
}

bool interleave(char* s1, char* s2, char* s3,
            int index1, int index2, int index3,
            int s1Size, int s2Size, int s3Size,
            int choose)
{
    if (index1 == s1Size && index2 == s2Size && index3 == s3Size) return true;
    if (choose == 1 && index1 < s1Size && index3 < s3Size && s1[index1] == s3[index3])
        return interleave(s1, s2, s3,
                          index1 + 1, index2, index3 + 1,
                          s1Size, s2Size, s3Size, 1) ||
               interleave(s1, s2, s3,
                          index1 + 1, index2, index3 + 1,
                          s1Size, s2Size, s3Size, 2);
   if (choose == 2 && index2 < s2Size && index3 < s3Size && s2[index2] == s3[index3])
        return interleave(s1, s2, s3,
                          index1, index2 + 1, index3 + 1,
                          s1Size, s2Size, s3Size, 1) ||
               interleave(s1, s2, s3,
                          index1, index2 + 1, index3 + 1,
                          s1Size, s2Size, s3Size, 2);
    return false;
}
*/