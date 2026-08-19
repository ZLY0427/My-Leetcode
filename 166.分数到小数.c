/*
 * @lc app=leetcode.cn id=166 lang=c
 *
 * [166] 分数到小�?
 */

// @lc code=start
#include <stdlib.h>

struct HashNode {
    int val;
    int index;
    struct HashNode* next;
};

struct Hash {
    struct HashNode* table;
    int hashSize;
};

struct Hash* create_Hash(int hashSize);
int gethashval_Hash(struct Hash* hash, int val);
void insert_Hash(struct Hash* hash, int val, int index);
int getindex_Hash(struct Hash* hash, int val);
void delete_Hash(struct Hash* hash);

void add_Num_Char(char** str, int* index, int* maxLen, long long num);

char* fractionToDecimal(int numerator, int denominator)
{
    if (denominator == 0) return NULL;
    if (numerator == 0)
    {
        char* res = (char*)malloc(sizeof(char) * 2);
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    long long num = numerator;
    long long den = denominator;
    
    int sign = (num < 0) ^ (den < 0);
    num = num < 0 ? -num : num;
    den = den < 0 ? -den : den;

    int maxLen = 128;
    char* res = (char*)malloc(sizeof(char) * maxLen);
    if (!res) return NULL;
    int index = 0;

    if (sign) res[index++] = '-';

    long long integer = num / den;
    add_Num_Char(&res, &index, &maxLen, integer);

    long long rem = num % den;
    if (rem == 0)
    {
        res[index] = '\0';
        char* result = (char*)realloc(res, index + 1);
        return result;
    }
    
    res[index++] = '.';

    struct Hash* hash = create_Hash(1021);
    while (rem != 0)
    {
        int pos = getindex_Hash(hash, (int)rem);
        if(pos != -1)
        {
            while(index + 2 >= maxLen - 1)
            {
                char* temp = (char*)realloc(res, maxLen * 2);
                if(!temp) return NULL;
                res = temp;
                maxLen *= 2;
            }

            for(int i = index; i >= pos; --i)
                res[i + 1] = res[i];
            
            res[pos] = '(';
            res[index + 1] = ')';
            index += 2;
            break;
        }
        insert_Hash(hash, (int)rem, index);
        rem *= 10;
        long long bit = rem / den;
        add_Num_Char(&res, &index, &maxLen, bit);
        rem = rem % den;
    }
    delete_Hash(hash);
    res[index] = '\0';
    char* result = (char*)realloc(res, index+1);
    return result;
}

void add_Num_Char(char** str, int* index, int* maxLen, long long num)
{
    int digit = 0;
    long long tmp = num;
    if (tmp == 0)
        digit = 1;
    else
    {
        while (tmp > 0)
        {
            ++digit;
            tmp /= 10;
        }
    }

    while ((*index) + digit > (*maxLen) - 1)
    {
        char* temp = (char*)realloc(*str, sizeof(char) * (*maxLen) * 2);
        if (!temp) return ;
        *str = temp;
        (*maxLen) *= 2;
    }

    int* digits = (int*)malloc(sizeof(int) * digit);
    if (!digits) return ;

    for (int i = digit - 1; i >= 0; --i)
    {
        digits[i] = num % 10;
        num /= 10;
    }

    for (int i = 0; i < digit; ++i)
        (*str)[(*index)++] = digits[i] + '0';

    free(digits);
}

struct Hash* create_Hash(int hashSize)
{
    if (hashSize <= 0) return NULL;
    struct Hash* hash = (struct Hash*)malloc(sizeof(struct Hash));
    if (!hash) return NULL;

    hash -> hashSize = hashSize;
    hash -> table = (struct HashNode*)malloc(hashSize * sizeof(struct HashNode));
    if (!hash -> table)
    {
        free(hash);
        return NULL;
    }

    for (int i = 0; i < hashSize; ++i)
    {
        hash -> table[i].val = -1;
        hash -> table[i].next = NULL;
    }

    return hash;
}

int gethashval_Hash(struct Hash* hash, int val)
{
    if (!hash) return -1;

    if (val < 0) val = -val; 
    return val == 0 ? 0 : val % hash -> hashSize;
}

void insert_Hash(struct Hash* hash, int val, int index)
{
    if (!hash) return ;

    int key = gethashval_Hash(hash, val);
    struct HashNode* node = &(hash -> table[key]);
    while (node -> next != NULL)
        node = node -> next;

    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    if (!newNode) return ;
    newNode -> val = val;
    newNode -> index = index;
    newNode -> next = NULL;

    node -> next = newNode;
}

int getindex_Hash(struct Hash* hash, int val)
{
    if (!hash) return 0;

    int key = gethashval_Hash(hash, val);
    struct HashNode* node = &(hash -> table[key]);
    while (node != NULL)
    {
        if (node -> val == val) return node -> index;
        node = node -> next;
    }

    return -1;
}

void delete_Hash(struct Hash* hash)
{
    if (!hash) return ;
    for (int i = 0; i < hash -> hashSize; ++i)
    {
        struct HashNode* node = hash -> table[i].next;
        while (node != NULL)
        {
            struct HashNode* tmp = node;
            node = node -> next;
            free(tmp);
        }
    }

    free(hash -> table);
    free(hash);
}

// @lc code=end

