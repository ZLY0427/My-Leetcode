/*
 * @lc app=leetcode.cn id=71 lang=c
 *
 * [71] 简化路径
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

struct Stack{
    char* name;
    int nameSize;

    struct Stack* next;
};

struct Stack* initStack();
char* pop(struct Stack* stack);
int push(struct Stack* stack, char* name);
void FreeStack(struct Stack* stack);
int isEmpty(struct Stack* stack);

char* simplifyPath(char* path)
{
    if (!path) return NULL;

    int pathlen = strlen(path);

    struct Stack* stack = initStack();
    // 第一个节点的 nameSize 为总体长度(不含'/')
    if (!stack) return NULL;

    int left = 0;
    while (left < pathlen)
    {
        while (left < pathlen && path[left] == '/')
        {
            left++;
            continue;
        }

        if (left >= pathlen) break;

        int right = left + 1;

        while (right < pathlen && path[right] != '/') right++;
        // 索引在 [left, right - 1] 的 path 为文件夹名

        int nameSize = right - left;
        char* name = (char*)malloc(sizeof(char) * (nameSize + 1));
        if (!name)
        {
            FreeStack(stack);
            return NULL;
        }

        strncpy(name, path + left, nameSize);
        name[nameSize] = '\0';

        if (nameSize == 1 && name[0] == '.');
        else if (nameSize == 2 && name[0] == '.' && name[1] == '.')
        {
            pop(stack);
        }
        else
        {
            if (!push(stack, name))
            {
                FreeStack(stack);
                return NULL;
            }
        }
        free(name);
        left = right;
    }

    struct Stack* inOrderStack = initStack();
    while (!isEmpty(stack))
    {
        char* temp = pop(stack);
        push(inOrderStack, temp);
        free(temp);
    }
    
    if (isEmpty(inOrderStack))
    {
        FreeStack(stack);
        FreeStack(inOrderStack);
        return "/";
    }

    // 计算所需总长度：每个名字前加 '/'，所以总长度 = nameSize总数 + 节点数（每个'/'）
    int totalLen = inOrderStack -> nameSize + 1;
    struct Stack* temp = inOrderStack -> next;
    int count = 0;
    while (temp)
    {
        count++;
        temp = temp -> next;
    }
    totalLen += count; // 每个目录前加一个 '/'

    char* result = (char*)malloc(sizeof(char) * totalLen);
    if (!result)
    {
        FreeStack(stack);
        FreeStack(inOrderStack);
        return NULL;
    }

    result[0] = '\0';
    temp = inOrderStack -> next;
    while (temp)
    {
        strcat(result, "/");
        strcat(result, temp -> name);
        temp = temp -> next;
    }

    FreeStack(stack);
    FreeStack(inOrderStack);

    return result;
}

struct Stack* initStack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack -> next = NULL;
    stack -> nameSize = 0;
    stack -> name = NULL;

    return stack;
}

char* pop(struct Stack* stack)
{
    if (isEmpty(stack)) return NULL;

    struct Stack* node = stack->next;
    stack->next = node->next;
    stack->nameSize -= node->nameSize;

    char* name = node->name; // 直接返回，不复制
    free(node);              // 只释放节点结构，不释放 name
    return name;
}

int push(struct Stack* stack, char* name)
{
    struct Stack* newNode = (struct Stack*)malloc(sizeof(struct Stack));
    if (!newNode) return 0;

    int len = strlen(name);
    newNode -> name = (char*)malloc(len + 1);
    if (!newNode -> name)
    {
        free(newNode);
        return 0;
    }
    strcpy(newNode -> name, name);
    newNode -> nameSize = len;

    newNode -> next = stack -> next;
    stack -> next = newNode;

    stack -> nameSize += newNode -> nameSize;

    return 1;
}

void FreeStack(struct Stack* stack)
{
    struct Stack* current = stack;
    while (current)
    {
        struct Stack* next = current -> next;
        free(current -> name);
        free(current);
        current = next;
    }
}

int isEmpty(struct Stack* stack)
{
    return stack -> next ? 0 : 1;
}
// @lc code=end

