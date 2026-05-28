/*
 * @lc app=leetcode.cn id=67 lang=c
 *
 * [67] 二进制求和
 */

// @lc code=start
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct SNode
{
    char data;
    struct SNode* next;
};

struct Stack
{
    int len;
    struct SNode* top;
    struct SNode* base;
};

struct Stack* initStack();   // 栈初始换
void FreeStack(struct Stack* stack);   // 销毁栈
bool push(struct Stack* stack, char data);   // 入栈
bool pop(struct Stack* stack, char* returnData);   // 出栈

char* addBinary(char* a, char* b)
{
    int len_a = strlen(a);
    int len_b = strlen(b);

    struct Stack* stack = initStack();
    if (stack == NULL)
    {
        return NULL;
    }

    int i = len_a - 1;
    int j = len_b - 1;
    int carry = 0;

    while (i >= 0 && j >= 0)
    {
        int sum = carry + (a[i] - '0') + (b[j] - '0');
        carry = sum / 2;
        char curr = (sum % 2) + '0';

        if (!push(stack, curr))
        {
            FreeStack(stack);
            return NULL;
        }
        i--;
        j--;
    }

    while (i >= 0)
    {
        int sum = carry + (a[i] - '0');
        carry = sum / 2;
        char curr = (sum % 2) + '0';

        if (!push(stack, curr))
        {
            FreeStack(stack);
            return NULL;
        }
        i--;
    }

    while (j >= 0)
    {
        int sum = carry + (b[j] - '0');
        carry = sum / 2;
        char curr = (sum % 2) + '0';

        if (!push(stack, curr))
        {
            FreeStack(stack);
            return NULL;
        }
        j--;
    }

    if (carry == 1)
    {
        if (!push(stack, '1'))
        {
            FreeStack(stack);
            return NULL;
        }
    }

    int size = stack -> len;
    char* result = (char*)malloc(sizeof(char) * (size + 1));
    
    if (result == NULL)
    {
        FreeStack(stack);
        return NULL;
    }

    for (int k = 0; k < size; k++)
    {
        if (!pop(stack, &result[k]))
        {
            FreeStack(stack);
            free(result);
            return NULL;
        }
    }
    result[size] = '\0';

    FreeStack(stack);  
    return result;
}

struct Stack* initStack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL)
    {
        return NULL;
    }
    struct SNode* baseNode = (struct SNode*)malloc(sizeof(struct SNode));
    if (baseNode == NULL)
    {
        free(stack);
        return NULL;
    }
    baseNode -> next = NULL;
    stack -> base = baseNode;
    stack -> top = baseNode;
    stack -> len = 0;

    return stack;
}

void FreeStack(struct Stack* stack)
{
    struct SNode* p = stack -> top;
    while(p)
    {
        struct SNode* temp = p;
        p = p -> next;
        free(temp);
    }
    free(stack);
}

bool push(struct Stack* stack, char data)
{
    struct SNode* newnode = (struct SNode*)malloc(sizeof(struct SNode));
    if (newnode == NULL)
    {
        return false;
    }
    newnode -> data = data;

    newnode -> next = stack -> top;
    stack -> top = newnode;
    stack -> len++;
    return true;
}

bool pop(struct Stack* stack, char* returnData)
{
    if (stack -> top == stack -> base)
    {
        return false;
    }
    struct SNode* p = stack -> top;
    stack -> top = p -> next;

    *returnData = p -> data;
    free(p);

    stack -> len--;
    return true;
}

// @lc code=end

