/*
 * @lc app=leetcode.cn id=136 lang=c
 *
 * [136] 只出现一次的数字
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

struct HashNode {
    int val;
    struct HashNode* next;
};

struct Hash {
    struct HashNode** head;
    int hashSize;
};

int getHashKey(int val, int hashSize);
void Insert_Hash(struct Hash* hash, int val);
bool Find_Hash(struct Hash* hash, int val);
void Remove_Hash(struct Hash* hash, int val);

struct Hash* Create_Hash(int hashSize);
void Number_Hash(struct Hash* hash, int val);
void Deltete_Hash(struct Hash* hash);

int singleNumber(int* nums, int numsSize)
{
    if (numsSize == 1) return nums[0];

    struct Hash* hash = Create_Hash(numsSize);
    for (int i = 0; i < numsSize; ++i)
        Number_Hash(hash, nums[i]);

    int result = 0;
    for (int i = 0; i < numsSize; ++i)
    {
        if (Find_Hash(hash, nums[i]))
        {
            result = nums[i];
            break;
        }
    }

    Deltete_Hash(hash);
    return result;
}

int getHashKey(int val, int hashSize)
{
    return (val > 0) ? (val % hashSize) : (-val % hashSize);
}

void Insert_Hash(struct Hash* hash, int val)
{
    int hashKey = getHashKey(val, hash -> hashSize);

    struct HashNode* node = (struct HashNode*)malloc(sizeof(struct HashNode));
    if (!node) return ;
    node -> val = val;
    node -> next = hash -> head[hashKey];
    hash -> head[hashKey] = node;
}

bool Find_Hash(struct Hash* hash, int val)
{
    int hashKey = getHashKey(val, hash -> hashSize);

    struct HashNode* node = hash -> head[hashKey];
    while (node)
    {
        if (node -> val == val) return true;
        node = node -> next;
    }
    return false;
}

void Remove_Hash(struct Hash* hash, int val)
{
    int hashKey = getHashKey(val, hash -> hashSize);

    struct HashNode* node = hash -> head[hashKey];
    struct HashNode* pre = NULL;
    while (node)
    {
        if (node -> val == val)
        {
            if (!pre)
                hash -> head[hashKey] = node -> next;
            else
                pre -> next = node -> next;
        }

        pre = node;
        node = node -> next;
    }
}

struct Hash* Create_Hash(int hashSize)
{
    struct Hash* hash = (struct Hash*)malloc(sizeof(struct Hash));
    if (!hash) return NULL;
    hash -> hashSize = hashSize;

    hash -> head = (struct HashNode**)malloc(sizeof(struct HashNode*) * hash -> hashSize);
    if (!hash -> head)
    {
        free(hash);
        return NULL;
    }

    for (int i = 0; i < hash -> hashSize; ++i)
        hash -> head[i] = NULL;

    return hash;
}

void Number_Hash(struct Hash* hash, int val)
{
    if (Find_Hash(hash, val))
        Remove_Hash(hash, val);
    else
        Insert_Hash(hash, val);
}

void Deltete_Hash(struct Hash* hash)
{
    if (!hash) return ;

    for (int i = 0; i < hash -> hashSize; ++i)
    {
        struct HashNode* node = hash -> head[i];
        while (node)
        {
            struct HashNode* tmp = node;
            node = node -> next;
            free(tmp);
        }
    }
    free(hash -> head);
    free(hash);
}
// @lc code=end

