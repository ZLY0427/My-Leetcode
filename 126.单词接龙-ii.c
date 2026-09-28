/*
 * @lc app=leetcode.cn id=126 lang=c
 *
 * [126] 单词接龙 II
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief 队列节点：保存一条搜索路径，存储单词下标数组
 * @param path 动态数组，存放路径上每个单词在wordList中的下标，beginWord用特殊下标标记
 * @param pathLen 当前路径包含单词个数
 * @param next 下一个队列节点指针
 */
struct QueueNode {
    int* path;
    int pathLen;
    struct QueueNode* next;
};

/**
 * @brief 链式队列，BFS使用，按层遍历
 * @param head 队头
 * @param tail 队尾
 * @param length 当前队列元素数量
 */
struct Queue {
    struct QueueNode* head;
    struct QueueNode* tail;
    int length;
};

#ifdef RUN_LOCATED_VSCODE
/**
 * @brief 链表节点，保存单词下标
 * @param val 单词下标
 * @param next 下一个链表节点指针
*/
struct ListNode {
    int val;
    struct ListNode* next;
};
#endif

/**
 * @brief 链表，保存相邻单词下标
 * @param head 链表头
 * @param number 链表元素数量
 */
struct List {
    struct ListNode* head;
    int number;
};

/**
 * @brief 无向图节点，保存相邻单词的下标
 * @param neighbor 相邻单词下表列表
 */
struct GraphNode {
    struct List* neighbor;
};

/**
 * @brief 无向图，方便寻找相邻单词的下标
 * @param graphNode 节点数组
 * @param count 节点数量
 */
struct Graph {
    struct GraphNode* graphNode;
    int count;
};

/**
 * @brief 哈希表节点
 * @param template 模板单词
 * @param indexlist 模板单词对应的单词下标列表
 * @param next 下一个哈希表节点指针
 */
struct HashNode {
    char* template;
    struct List* indexlist;
    struct HashNode* next;
};

/**
 * @brief 哈希表
 * @param hashTable 节点数组
 * @param count 节点数量
 */
struct HashTable {
    struct HashNode* hashTable;
    int count;
};

struct Queue* create_Queue();
void push_Queue(struct Queue* queue, int* path, int pathLen);
struct QueueNode* pop_Queue(struct Queue* queue);
void free_Queue(struct Queue* queue);

struct List* create_List();
void push_List(struct List* list, int val);
void delete_List(struct List* list, int val);
void free_List(struct List* list);

struct Graph* create_Graph(int count);
void addEdge_Graph(struct Graph* graph, int srcID, int dstID);
struct List* getNeighbor_Graph(struct Graph* graph, int srcID);
void free_Graph(struct Graph* graph);

bool is_str_single_diff(char* s1, char* s2);
bool is_str_same(char* s1, char* s2);

/**
 * @brief 寻找从beginWord到endWord所有最短转换序列
 * 规则：每次只能改变一个字符；转换后的单词必须在wordList中；返回全部最短路径
 * @param beginWord 起始单词
 * @param endWord 目标单词
 * @param wordList 单词字典数组
 * @param wordListSize 字典单词总数
 * @param returnSize 输出参数：最终找到的最短路径条数
 * @param returnColumnSizes 输出参数：数组，每个元素代表对应路径的单词数量
 * @return char*** 三维数组，每一行是一条单词路径；内存由调用者释放
 */
char*** findLadders(char* beginWord, char* endWord, char** wordList,
                    int wordListSize, int* returnSize, int** returnColumnSizes)
{
    // 边界判断：空指针、单词长度不一致直接返回空
    if (!beginWord || !endWord || !wordList || wordListSize <= 0 || strlen(beginWord) != strlen(endWord)) return NULL;

    int wordSize = strlen(beginWord);   // 每个单词字符长度
    int listSize = wordListSize;       // 单词列表总个数
    int beginIndex = listSize;         // 起始单词的虚拟下标（不在wordList，设为listSize区分）
    int endIndex = -1;                 // 目标单词在wordList中的下标，初始-1表示不存在

    // 查找endWord是否存在于单词列表
    for (int i = 0; i < listSize; ++i)
    {
        if (strcmp(wordList[i], endWord) == 0)
        {
            endIndex = i;
            break;
        }
    }
    if (endIndex == -1)
    {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }   // 目标单词不在字典，无解

    struct Graph* graph = create_Graph(listSize);
    if (!graph) return NULL;
    // 两两比较，只差一个字符则添加边
    for(int i = 0; i < listSize; ++i)
        for(int j = i + 1; j < listSize; ++j)
            if(is_str_single_diff(wordList[i], wordList[j]))
                addEdge_Graph(graph, i, j);

    struct Queue* queue = create_Queue(); // 创建BFS队列
    if (!queue)
    {
        free_Graph(graph);
        return NULL;
    }

    // 初始化起始路径：只包含beginWord虚拟下标
    int* path = (int*)malloc(sizeof(int));
    if (!path)
    {
        free_Graph(graph);
        free_Queue(queue);
        return NULL;
    }
    path[0] = beginIndex;
    push_Queue(queue, path, 1); // 将起始路径入队
    free(path);                 // push内部会拷贝path，本地path可以释放

    bool* visited = (bool*)calloc(listSize, sizeof(bool)); // 全局访问标记，记录已经完成访问的单词
    if (!visited)
    {
        free_Graph(graph);
        free_Queue(queue);
        return NULL;
    }

    bool found = false;                // 是否已经找到最短层（找到则不再继续往下层搜索）
    char*** res = NULL;                // 结果集：存放所有最短单词路径
    int* colSizes = NULL;              // 每条路径长度数组，对应returnColumnSizes
    *returnSize = 0;                   // 初始化结果条数为0

    // BFS层序遍历，一层一层扩展，保证最先找到的就是最短路径
    while (queue -> length > 0 && !found)
    {
        int levelSize = queue -> length;             // 当前层节点数量
        bool* levelVisited = (bool*)calloc(listSize, sizeof(bool)); // 当前层新访问标记，同层可以重复访问，层结束统一更新visited

        for (int l = 0; l < levelSize; ++l)
        {
            struct QueueNode* curNode = pop_Queue(queue); // 取出队首路径
            int curIdx = curNode -> path[curNode -> pathLen - 1]; // 当前路径末尾单词下标
            
            char* curWord;
            if (curIdx == beginIndex) curWord = beginWord;
            else curWord = wordList[curIdx];

            // 当前单词等于目标单词，找到一条最短路径
            if (curIdx == endIndex)
            {
                found = true;
                // 扩容结果数组，保存新路径
                res = realloc(res, (*returnSize + 1) * sizeof(char**));
                colSizes = realloc(colSizes, (*returnSize + 1) * sizeof(int));
                colSizes[*returnSize] = curNode -> pathLen;

                char** oneAns = malloc(curNode -> pathLen * sizeof(char*));
                for(int k = 0; k < curNode -> pathLen; ++k)
                {
                    int wid = curNode -> path[k];
                    if(wid == beginIndex) oneAns[k] = strdup(beginWord);
                    else oneAns[k] = strdup(wordList[wid]);
                }
                res[(*returnSize)++] = oneAns;

                free(curNode -> path);
                free(curNode);
                continue;
            }

            // 获取当前单词的邻居
            struct List* neighborList;   // 邻居列表
            if(curIdx == beginIndex)
            {
                // beginWord是虚拟节点，需要单独遍历wordList找和begin只差1字符的邻居
                neighborList = create_List();
                for(int i = 0; i < listSize; ++i)
                {
                    if(!visited[i] && is_str_single_diff(beginWord, wordList[i]))
                        push_List(neighborList, i);
                }
            }
            else
            {
                // wordList内单词，直接读取预建图的邻接链表
                neighborList = getNeighbor_Graph(graph, curIdx);
            }

            struct ListNode* p = neighborList -> head;
            while(p != NULL)
            {
                int neighbor = p -> val;
                if(visited[neighbor])
                {
                    p = p -> next;
                    continue;
                }
                // 复制路径，生成新路径入队
                int* newPath = malloc((curNode -> pathLen + 1) * sizeof(int));
                memcpy(newPath, curNode -> path, curNode -> pathLen * sizeof(int));
                newPath[curNode -> pathLen] = neighbor;
                push_Queue(queue, newPath, curNode -> pathLen + 1);
                free(newPath);
                levelVisited[neighbor] = true;

                p = p -> next;
            }
            // 如果是临时创建的begin的邻接链表，要释放
            if(curIdx == beginIndex)
                free_List(neighborList);

            free(curNode -> path);
            free(curNode);
        }

        // 当前层全部处理完毕，把本层访问到的单词标记为全局已访问，防止下层重复访问（保证最短）
        for(int i = 0; i < listSize; ++i)
            if(levelVisited[i]) visited[i] = true;
        free(levelVisited);
    }

    free_Graph(graph);
    free_Queue(queue);
    free(visited);
    *returnColumnSizes = colSizes;
    return res;
}

/**
 * @brief 创建空队列
 * @return struct Queue* 队列指针，失败返回NULL
 */
struct Queue* create_Queue()
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (!queue) return NULL;
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> length = 0;
    return queue;
}

/**
 * @brief 入队：拷贝一份路径存入新节点
 * @param queue 目标队列
 * @param path 待入队的下标数组
 * @param pathLen 路径长度
 */
void push_Queue(struct Queue* queue, int* path, int pathLen)
{
    if (!queue ||!path || pathLen <= 0) return ;
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) return ;
    int* copyPath = malloc(sizeof(int) * pathLen);
    if (!copyPath)
    {
        free(newNode);
        return ;
    }
    memcpy(copyPath, path, sizeof(int) * pathLen);
    newNode -> path = copyPath;
    newNode -> pathLen = pathLen;
    newNode -> next = NULL;

    if (queue -> length <= 0)
    {
        queue -> head = newNode;
        queue -> tail = newNode;
        queue -> length = 1;
    }
    else
    {
        queue -> tail -> next = newNode;
        queue -> tail = newNode;
        ++(queue -> length);
    }
}

/**
 * @brief 出队：弹出队头节点，由调用者释放节点内path和节点本身
 * @param queue 队列
 * @return struct QueueNode* 弹出节点，空队列返回NULL
 */
struct QueueNode* pop_Queue(struct Queue* queue)
{
    if(!queue || queue -> length <= 0) return NULL;
    struct QueueNode* qNode = queue -> head;
    queue -> head = queue -> head -> next;
    --(queue-> length);
    return qNode;
}

/**
 * @brief 释放队列所有节点以及队列本身
 * @param queue 待释放队列
 */
void free_Queue(struct Queue* queue)
{
    if (!queue) return ;
    while (queue -> length > 0)
    {
        struct QueueNode* qNode = pop_Queue(queue);
        free(qNode -> path);
        free(qNode);
    }
    free(queue);
}

/**
 * @brief 创建空链表
 * @return struct List* 链表指针，失败返回NULL
 */
struct List* create_List()
{
    struct List* list = (struct List*)malloc(sizeof(struct List));
    if(!list) return NULL;
    list -> head = NULL;
    list -> number = 0;

    return list;
}

/**
 * @brief 以头插法添加列表节点
 * @param list 目标链表
 * @param val 待添加的值
 * @return void
 */
void push_List(struct List* list, int val)
{
    if (!list || val < 0) return ;
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!newNode) return ;

    newNode -> val = val;
    newNode -> next = list -> head;
    list -> head = newNode;
    ++(list -> number);
}

/**
 * @brief 删除链表中的节点
 * @param list 链表
 * @param val 待删除的值
 * @return void
 */
void delete_List(struct List* list, int val)
{
    if (!list || val < 0 || list -> number <= 0) return ;
    if (list -> head -> val == val)
    {
        struct ListNode* delNode = list -> head;
        list -> head = list -> head -> next;
        --(list -> number);
        free(delNode);
        return ;
    }
    struct ListNode* curNode = list -> head;
    while (curNode -> next)
    {
        if(curNode -> next -> val == val)
        {
            struct ListNode* delNode = curNode -> next;
            curNode -> next = curNode -> next -> next;
            --(list -> number);
            free(delNode);
            return ;
        }
        curNode = curNode -> next;
    }
}

/**
 * @brief 释放链表所有节点以及链表本身
 * @param list 链表
 * @return void
 */
void free_List(struct List* list)
{
    if (!list) return ;
    while (list -> number > 0)
    {
        struct ListNode* delNode = list -> head;
        list -> head = list -> head -> next;
        --(list -> number);
        free(delNode);
    }
    free(list);
}

/**
 * @brief 创建无向图中的节点
 * @param count 节点数
 * @return struct Graph* 图指针，失败返回NULL
 */
struct Graph* create_Graph(int count)
{
    if (count <= 0) return NULL;
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (!graph) return NULL;

    graph -> count = count;
    graph -> graphNode = (struct GraphNode*)malloc(count * sizeof(struct GraphNode));
    if (!graph -> graphNode)
    {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < count; ++i)
    {
        graph -> graphNode[i].neighbor = create_List();
        if (!graph -> graphNode[i].neighbor)
        {
            for (int j = 0; j < i; ++j)
                free_List(graph -> graphNode[j].neighbor);
            free(graph -> graphNode);
            free(graph);
            return NULL;
        }
    }

    return graph;
}

/**
 * @brief 添加无向图边
 * @param graph 图
 * @param src A节点
 * @param dst B节点
 * @return void
 */
void addEdge_Graph(struct Graph* graph, int src, int dst)
{
    if (!graph || src < 0 || dst < 0 || src >= graph -> count || dst >= graph -> count) return ;
    push_List(graph -> graphNode[src].neighbor, dst);
    push_List(graph -> graphNode[dst].neighbor, src);
}

/**
 * @brief 获取无向图A节点的邻接节点
 * @param graph 图
 * @param src 节点A
 * @return struct List* 邻接节点链表，失败返回NULL
 */
struct List* getNeighbor_Graph(struct Graph* graph, int src)
{
    if (!graph || src < 0 || src >= graph -> count) return NULL;
    return graph -> graphNode[src].neighbor;
}

/**
 * @brief 释放无向图所有节点以及无向图本身
 * @param graph 图
 * @return void
 */
void free_Graph(struct Graph* graph)
{
    if (!graph) return ;
    for (int i = 0; i < graph -> count; ++i)
        free_List(graph -> graphNode[i].neighbor);
    free(graph -> graphNode);
    free(graph);
}

/**
 * @brief 判断两个字符串是否恰好只有1个字符不同
 * @param s1 字符串1
 * @param s2 字符串2
 * @return true：恰好1处不同；false：其他情况
 */
bool is_str_single_diff(char* s1, char* s2)
{
    if (!s1 || !s2) return false;
    if (strlen(s1) != strlen(s2)) return false;
    int diff_count = 0;
    int len = strlen(s1);
    for (int i = 0; i < len; ++i)
        if (s1[i] != s2[i])
        {
            ++diff_count;
            if (diff_count > 1) return false;
        }
    return diff_count == 1;
}

/**
 * @brief 判断两个字符串完全相等
 * @param s1 字符串1
 * @param s2 字符串2
 * @return true相等 false不等
 */
bool is_str_same(char* s1, char* s2)
{
    return strcmp(s1, s2) == 0;
}

// @lc code=end
