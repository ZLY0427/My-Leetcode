/*
 * @lc app=leetcode.cn id=146 lang=c
 *
 * [146] LRU 缓存
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

typedef struct HashNode {
    int key;
    int val;
    int time_since_last_use;
    struct HashNode* next;
} HashNode;

typedef struct Hash {
    HashNode* hashTable;
    int hashSize;
} Hash;

typedef struct {
    int capacity;
    int nowUsed;
    Hash* hash;
} LRUCache;

Hash* create_Hash(int hashSize);
int getKey_Hash(Hash* hash, int key);
void insert_Hash(Hash* hash, int key, int val);
int getVal_Hash(Hash* hash, int key);
void remove_Hash(Hash* hash, int key);
void delete_Hash(Hash* hash);
int getMax__time_since_last_use__key_Hash(Hash* hash);
void add_one__time_since_last_use__Hash(Hash* hash);
void zeroize__time_since_last_use__Hash(Hash* hash, int key);

LRUCache* lRUCacheCreate(int capacity)
{
    LRUCache* obj = (LRUCache*)malloc(sizeof(LRUCache));
    if (!obj) return NULL;
    
    obj -> capacity = capacity;
    obj -> nowUsed = 0;

    obj -> hash = create_Hash(capacity);
    if (!obj -> hash)
    {
        free(obj);
        return NULL;
    }
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key)
{
    if (!obj) return -1;

    int val = getVal_Hash(obj -> hash, key);
    if (val == -1) return -1;

    add_one__time_since_last_use__Hash(obj -> hash);
    zeroize__time_since_last_use__Hash(obj -> hash, key);

    return val;
}

void lRUCachePut(LRUCache* obj, int key, int value)
{
    if (!obj) return ;

    add_one__time_since_last_use__Hash(obj -> hash);

    if (getVal_Hash(obj -> hash, key) != -1)
    {
        remove_Hash(obj -> hash, key);
        insert_Hash(obj -> hash, key, value);
        return ;
    }

    if (obj -> nowUsed < obj -> capacity)
    {
        insert_Hash(obj -> hash, key, value);
        ++(obj -> nowUsed);
    }
    else
    {
        int max_key = getMax__time_since_last_use__key_Hash(obj -> hash);
        remove_Hash(obj -> hash, max_key);
        insert_Hash(obj -> hash, key, value);
    }
}

void lRUCacheFree(LRUCache* obj)
{
    if (!obj) return ;

    delete_Hash(obj -> hash);
    free(obj);
}

Hash* create_Hash(int hashSize)
{
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    if (!hash) return NULL;

    hash -> hashSize = hashSize;
    hash -> hashTable = (HashNode*)malloc(sizeof(HashNode) * hashSize);
    if (!hash -> hashTable)
    {
        free(hash);
        return NULL;
    }

    for (int i = 0; i < hashSize; i++)
    {
        hash -> hashTable[i].val = -1;
        hash -> hashTable[i].time_since_last_use = -1;
        hash -> hashTable[i].next = NULL;
    }

    return hash;
}

int getKey_Hash(Hash* hash, int key)
{
    if (!hash) return -1;
    if (key < 0) return 0;
    return key % hash -> hashSize;
}

void insert_Hash(Hash* hash, int key, int val)
{
    if (!hash) return ;

    int index = getKey_Hash(hash, key);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (!node) return ;
    
    node -> key = key;
    node -> val = val;
    node -> time_since_last_use = 0;
    node -> next = NULL;

    node -> next = hash -> hashTable[index].next;
    hash -> hashTable[index].next = node;
}

int getVal_Hash(Hash* hash, int key)
{
    if (!hash) return -1;

    int index = getKey_Hash(hash, key);
    HashNode* node = hash -> hashTable[index].next;
    while (node)
    {
        if (node -> key == key)
        {
            node -> time_since_last_use = 0;
            return node -> val;
        }
        node = node -> next;
    }

    return -1;
}

void remove_Hash(Hash* hash, int key)
{
    if (!hash) return ;

    int index = getKey_Hash(hash, key);
    HashNode* node = hash -> hashTable[index].next;
    HashNode* pre = &(hash -> hashTable[index]);
    while (node)
    {
        if (node -> key == key)
        {
            pre -> next = node -> next;
            free(node);
            return ;
        }

        pre = node;
        node = node -> next;
    }
}

void delete_Hash(Hash* hash)
{
    if (!hash) return ;

    for (int i = 0; i < hash -> hashSize; ++i)
    {
        HashNode* node = hash -> hashTable[i].next;
        while (node)
        {
            HashNode* tmp = node;
            node = node -> next;
            free(tmp);
        }
    }

    free(hash -> hashTable);
    free(hash);
}

int getMax__time_since_last_use__key_Hash(Hash* hash)
{
    if (!hash) return -1;

    int max = -1;
    int max_key = -1;
    for (int i = 0; i < hash -> hashSize; ++i)
    {
        HashNode* node = hash -> hashTable[i].next;
        while (node)
        {
            if (node -> time_since_last_use > max)
            {
                max = node -> time_since_last_use;
                max_key = node -> key;
            }

            node = node -> next;
        }
    }

    return max_key;
}

void add_one__time_since_last_use__Hash(Hash* hash)
{
    if (!hash) return ;

    for (int i = 0; i < hash -> hashSize; ++i)
    {
        HashNode* node = hash -> hashTable[i].next;
        while (node)
        {
            ++(node -> time_since_last_use);
            node = node -> next;
        }
    }
}

void zeroize__time_since_last_use__Hash(Hash* hash, int key)
{
    if (!hash) return ;

    int index = getKey_Hash(hash, key);
    HashNode* node = hash -> hashTable[index].next;
    while (node)
    {
        if (node -> key == key)
        {
            node -> time_since_last_use = 0;
            return ;
        }
        node = node -> next;
    }
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
// @lc code=end

