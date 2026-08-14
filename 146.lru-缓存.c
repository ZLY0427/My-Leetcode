/*
 * @lc app=leetcode.cn id=146 lang=c
 *
 * [146] LRU »º´æ
 */

// @lc code=start
#include <stdlib.h>

typedef struct LNode {
    int key;
    int val;
    struct LNode* prev;
    struct LNode* next;
} LNode;

typedef struct List {
    LNode* head;
    LNode* tail;
    int count;
} List;

typedef struct HashNode {
    LNode* node;
    struct HashNode* next;
} HashNode;

typedef struct Hash {
    HashNode* hashTable;
    int hashSize;
} Hash;

typedef struct LRUCache {
    int capacity;
    Hash* hash;
    List* list;
} LRUCache;

LNode* create_ListNode(int key, int val);
List* create_List();
void insert_List(List* list, LNode* node);
void extract_List(List* list, LNode* node);
void freeLastNode_List(List* list);
void delete_List(List* list);

Hash* create_Hash(int hashSize);
int gethashkey_Hash(Hash* hash, int key);
LNode* getListNode_Hash(Hash* hash, int key);
void insert_Hash(Hash* hash, LNode* node);
void free_HashNode(Hash* hash, int key);
void delete_Hash(Hash* hash);

LRUCache* create_LRU(int capacity);

LRUCache* lRUCacheCreate(int capacity)
{
    return create_LRU(capacity);
}

int lRUCacheGet(LRUCache* obj, int key)
{
    LNode* listNode = getListNode_Hash(obj -> hash, key);
    if (!listNode) return -1;
    extract_List(obj -> list, listNode);
    insert_List(obj -> list, listNode);

    return listNode -> val;
}

void lRUCachePut(LRUCache* obj, int key, int value)
{
    LNode* listNode = getListNode_Hash(obj -> hash, key);
    if (listNode)
    {
        extract_List(obj -> list, listNode);
        listNode -> val = value;
        insert_List(obj -> list, listNode);
        return ;
    }

    listNode = create_ListNode(key, value);
    if (!listNode) return ;
    if (obj -> list -> count < obj -> capacity)
    {
        insert_Hash(obj -> hash, listNode);
        insert_List(obj -> list, listNode);
    }
    else
    {
        int hashKey = obj -> list -> tail -> prev -> key;
        free_HashNode(obj -> hash, hashKey);
        freeLastNode_List(obj -> list);
        insert_Hash(obj -> hash, listNode);
        insert_List(obj -> list, listNode);
    }
}

void lRUCacheFree(LRUCache* obj)
{
    delete_List(obj -> list);
    delete_Hash(obj -> hash);
    free(obj);
}

LNode* create_ListNode(int key, int val)
{
    LNode* node = (LNode*)malloc(sizeof(LNode));
    if (!node) return NULL;

    node -> key = key;
    node -> val = val;
    node -> prev = NULL;
    node -> next = NULL;

    return node;
}

List* create_List()
{
    List* list = (List*)malloc(sizeof(List));
    if (!list) return NULL;

    list -> head = (LNode*)malloc(sizeof(LNode));
    list -> tail = (LNode*)malloc(sizeof(LNode));
    if (!list -> head || !list -> tail)
    {
        free(list -> head);
        free(list -> tail);
        free(list);
        return NULL;
    }
    list -> head -> prev = NULL;
    list -> head -> next = list -> tail;
    list -> head -> key = -1;
    list -> head -> val = -1;

    list -> tail -> prev = list -> head;
    list -> tail -> next = NULL;
    list -> tail -> key = -1;
    list -> tail -> val = -1;

    list -> count = 0;

    return list;
}

void insert_List(List* list, LNode* node)
{
    if (!list || !node) return ;

    LNode* node_prev = list -> head;
    LNode* node_next = node_prev -> next;

    node_prev -> next = node;
    node -> prev = node_prev;
    node -> next = node_next;
    node_next -> prev = node;

    ++(list -> count);
}

void extract_List(List* list, LNode* node)
{
    if (!list || !node) return ;

    LNode* node_prev = node -> prev;
    LNode* node_next = node -> next;

    node_prev -> next = node_next;
    node_next -> prev = node_prev;

    node -> next = NULL;
    node -> prev = NULL;

    --(list -> count);
}

void freeLastNode_List(List* list)
{
    if (!list) return ;

    LNode* node = list -> tail -> prev;
    extract_List(list, node);
    free(node);
}

void delete_List(List* list)
{
    if (!list) return ;

    LNode* node = list -> head;
    while (node)
    {
        LNode* temp = node;
        node = node -> next;
        
        free(temp);
    }

    free(list);
}

Hash* create_Hash(int hashSize)
{
    if (hashSize <= 0) return NULL;
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    if (!hash) return NULL;

    hash -> hashSize = hashSize;
    hash -> hashTable = (HashNode*)malloc(sizeof(HashNode) * hashSize);
    if (!hash -> hashTable)
    {
        free(hash);
        return NULL;
    }

    for (int i = 0; i < hashSize; ++i)
    {
        hash -> hashTable[i].node = NULL;
        hash -> hashTable[i].next = NULL;
    }

    return hash;
}

int gethashkey_Hash(Hash* hash, int key)
{
    if (!hash) return -1;
    if (key < 0) return 0;
    return key % hash -> hashSize;
}

LNode* getListNode_Hash(Hash* hash, int key)
{
    if (!hash) return NULL;

    HashNode* hashNode = hash -> hashTable[gethashkey_Hash(hash, key)].next;
    while (hashNode)
    {
        if (hashNode -> node -> key == key) return hashNode -> node;
        hashNode = hashNode -> next;
    }

    return NULL;
}

void insert_Hash(Hash* hash, LNode* node)
{
    if (!hash || !node) return ;

    int hashKey = gethashkey_Hash(hash, node -> key);

    HashNode* node_hash = (HashNode*)malloc(sizeof(HashNode));
    if (!node_hash) return ;

    node_hash -> node = node;
    node_hash -> next = hash -> hashTable[hashKey].next;
    hash -> hashTable[hashKey].next = node_hash;
}

void free_HashNode(Hash* hash, int key)
{
    if (!hash) return ;

    int hashKey = gethashkey_Hash(hash, key);

    HashNode* node = hash -> hashTable[hashKey].next;
    HashNode* node_prev = &(hash -> hashTable[hashKey]);
    while (node)
    {
        if (node -> node -> key == key)
        {
            node_prev -> next = node -> next;
            free(node);
            return ;
        }
        node_prev = node;
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
            HashNode* temp = node;
            node = node -> next;
            free(temp);
        }
    }
    free(hash -> hashTable);
    free(hash);
}

LRUCache* create_LRU(int capacity)
{
    if (capacity <= 0) return NULL;

    LRUCache* lru = (LRUCache*)malloc(sizeof(LRUCache));
    if (!lru) return NULL;

    lru -> capacity = capacity;
    lru -> hash = create_Hash(capacity);
    lru -> list = create_List();
    if (!lru -> hash || !lru -> list)
    {
        delete_Hash(lru -> hash);
        delete_List(lru -> list);
        free(lru);
        return NULL;
    }

    return lru;
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
// @lc code=end