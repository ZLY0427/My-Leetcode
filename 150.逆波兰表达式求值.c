/*
 * @lc app=leetcode.cn id=150 lang=c
 *
 * [150] 逆波兰表达式求�?
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

struct StackNode {
    int val;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
    int count;
};

struct Stack* create_Stack();
void push_Stack(struct Stack* stack, int val);
int pop_Stack(struct Stack* stack);
void delete_Stack(struct Stack* stack);
bool is_Number(char* s);

int evalRPN(char** tokens, int tokensSize)
{
    if (!tokens || tokensSize <= 0) return 0;

    struct Stack* stack = create_Stack();
    for (int i = 0; i < tokensSize; ++i)
    {
        if (is_Number(tokens[i]))
            push_Stack(stack, atoi(tokens[i]));
        else
        {
            int a = pop_Stack(stack);
            int b = pop_Stack(stack);
            int val = 0;
            switch (tokens[i][0])
            {
                case '+':
                    val = a + b;
                    break;
                case '-':
                    val = b - a;
                    break;
                case '*':
                    val = a * b;
                    break;
                case '/':
                    val = b / a;
                    break;
                default:
                    break;
            }
            push_Stack(stack, val);
        }
    }

    int val = pop_Stack(stack);
    delete_Stack(stack);
    return val;
}

struct Stack* create_Stack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;
    
    stack -> top = NULL;
    stack -> count = 0;

    return stack;
}

void push_Stack(struct Stack* stack, int val)
{
    if (!stack) return ;

    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!node) return ;

    node -> val = val;
    node -> next = stack -> top;
    stack -> top = node;
    ++(stack -> count);
}

int pop_Stack(struct Stack* stack)
{
    if (!stack || stack -> count <= 0) return 0;

    struct StackNode* node = stack -> top;

    stack -> top = node -> next;
    --(stack -> count);

    int val = node -> val;
    free(node);

    return val;
}

void delete_Stack(struct Stack* stack)
{
    if (!stack) return ;

    while (stack -> count > 0) pop_Stack(stack);
    free(stack);
}

bool is_Number(char* s)
{
    if (!s || *s == '\0') return false;

    int idx = 0;
    if(s[0] == '-')
    {
        idx = 1;
        if(s[idx] == '\0') return false;
    }
    
    for(; s[idx] != '\0'; ++idx)
        if(s[idx] < '0' || s[idx] > '9') return false;
    
    
    return true;
}
// @lc code=end

