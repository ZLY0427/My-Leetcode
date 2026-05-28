/*
 * @lc app=leetcode.cn id=6 lang=c
 *
 * [6] Z ×ÖÐÎ±ä»»
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

char* convert(char* s, int numRows)
{
    if (numRows <= 1 || s == NULL)
    {
        if (s == NULL)
        {
            return NULL;
        }

        char* result = (char*)malloc(sizeof(char) * (strlen(s) + 1));
        if (result == NULL)
        {
            printf("¿Õ¼ä·ÖÅä´íÎó.\n");
            return NULL;
        }

        strcpy(result, s);
        return result;
    }

    int size = strlen(s);
    char**s_Z = (char**)malloc(size * sizeof(char*));
    if (s_Z == NULL)
    {
        printf("¿Õ¼ä·ÖÅä´íÎó.\n");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        s_Z[i] = (char*)calloc(numRows, sizeof(char));
        if (s_Z[i] == NULL)
        {
            printf("¿Õ¼ä·ÖÅä´íÎó.\n");
            for (int j = 0; j < i; j++)
            {
                free(s_Z[j]);
            }

            free(s_Z);
            return NULL;
        }
    }
    
    bool is_up = false;
    int row = 0;
    for (int i = 0; i < size; i++)
    {
        s_Z[i][row] = s[i];
        if (is_up)
        {
            row--;
        }
        else
        {
            row++;
        }
        if (row == 0)
        {
            is_up = false;
        }
        else if(row == numRows - 1)
        {
            is_up = true;
        }
    }
    int len = 0;
    char* result = (char*)malloc(sizeof(char) * (size + 1));
    if (result == NULL)
    {
        printf("ÄÚ´æ·ÖÅä´íÎó.\n");
        for (int i = 0; i < size; i++)
        {
            free(s_Z[i]);
        }
        
        free(s_Z);
        return NULL;
    }
    for (int j = 0; j < numRows; j++)
    {
        for (int i = 0; i < size; i++)
        {
            if (s_Z[i][j] != 0)
            {
                result[len++] = s_Z[i][j];
            }
        }
    }
    result[len] = '\0';

    for (int i = 0; i < size; i++)
    {
        free(s_Z[i]);
    }
    free(s_Z);

    return result;
}
// @lc code=end
