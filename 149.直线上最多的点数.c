/*
 * @lc app=leetcode.cn id=149 lang=c
 *
 * [149] 鐩寸嚎涓婃渶澶氱殑鐐规暟
 */

// @lc code=start
#include <stdlib.h>

struct HashNode {
    int dy;
    int dx;
    int cnt;
    struct HashNode* next;
};

typedef struct {
    struct HashNode* table;
    int hashSize;
} HashTable;

int gcd(int a, int b);
HashTable* hashCreate(int hashSize);
int hashGetIdx(HashTable* ht, int dx, int dy);
void hashInsert(HashTable* ht, int dx, int dy);
int hashGetMax(HashTable* ht);
void hashClear(HashTable* ht);
void hashDestroy(HashTable* ht);

int maxPoints(int** points, int pointsSize, int* pointsColSize)
{
    if(pointsSize <= 1) return pointsSize;

    HashTable* ht = hashCreate(pointsSize * 2);
    int ans = 1;

    // 枚举基点 i
    for(int i = 0; i < pointsSize; i++)
    {
        hashClear(ht);
        int samePoint = 0; // 和i完全重合的点
        int curMax = 0;

        for(int j = 0; j < pointsSize; j++)
        {
            if(i == j) continue;
            int x1 = points[i][0], y1 = points[i][1];
            int x2 = points[j][0], y2 = points[j][1];
            int dx = x2 - x1;
            int dy = y2 - y1;

            if(dx == 0 && dy == 0)
            {
                samePoint++;
                continue;
            }
            // 约分
            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;

            // 标准化符号：让dx>0；dx=0则dy>0
            if(dx < 0)
            {
                dx = -dx;
                dy = -dy;
            }
            if(dx == 0)
            {
                dy = dy > 0 ? 1 : -1;
            }

            hashInsert(ht, dx, dy);
        }
        curMax = hashGetMax(ht);
        // 当前基点i：基点(1) + 同斜率点(curMax) + 完全重合点(samePoint)
        int total = 1 + curMax + samePoint;
        if(total > ans) ans = total;
    }

    hashDestroy(ht);
    return ans;
}

// 求最大公约数 gcd, 注意处理负数
int gcd(int a, int b)
{
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while(b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

HashTable* hashCreate(int hashSize)
{
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht -> hashSize = hashSize;
    ht -> table = (struct HashNode*)calloc(hashSize, sizeof(struct HashNode));
    return ht;
}

// 哈希函数，对约分后的dx dy
int hashGetIdx(HashTable* ht, int dx, int dy)
{
    long long key = (long long)dx * 20003 + dy;
    int idx = key % ht -> hashSize;
    if(idx < 0) idx += ht -> hashSize;
    return idx;
}

// 插入，dx dy已经是最简标准化形式
void hashInsert(HashTable* ht, int dx, int dy)
{
    int idx = hashGetIdx(ht, dx, dy);
    struct HashNode* p = &ht -> table[idx];
    while(p -> next != NULL)
    {
        p = p -> next;
        if(p -> dx == dx && p -> dy == dy)
        {
            p -> cnt += 1;
            return;
        }
    }
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode -> dx = dx;
    newNode -> dy = dy;
    newNode -> cnt = 1;
    newNode -> next = NULL;
    p -> next = newNode;
}

// 获取哈希表里最大计数，只遍历，不释放数组头
int hashGetMax(HashTable* ht)
{
    int maxCnt = 0;
    for(int i = 0; i < ht -> hashSize; ++i)
    {
        struct HashNode* p = ht -> table[i].next;
        while(p)
        {
            if(p -> cnt > maxCnt) maxCnt = p -> cnt;
            p = p -> next;
        }
    }
    return maxCnt;
}

// 清空链表，保留table数组
void hashClear(HashTable* ht)
{
    for(int i = 0; i < ht -> hashSize; ++i)
    {
        struct HashNode* p = ht -> table[i].next;
        ht -> table[i].next = NULL;
        while(p)
        {
            struct HashNode* tmp = p;
            p = p -> next;
            free(tmp);
        }
    }
}

// 释放哈希表
void hashDestroy(HashTable* ht)
{
    hashClear(ht);
    free(ht -> table);
    free(ht);
}

// @lc code=end

