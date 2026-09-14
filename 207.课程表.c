/*
 * @lc app=leetcode.cn id=207 lang=c
 *
 * [207] 课程�?
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

struct GraphNode {
    int Course_ID;
    struct GraphNode* next;
};

struct Graph {
    struct GraphNode** Node;
    int Course_Num;
};

struct Graph* create_Graph(int Course_Num);
void add_Edge(struct Graph* graph, int Course_ID, int Prerequisite_Course_ID);
void free_Graph(struct Graph* graph);
bool dfs(int cur, int* color, struct Graph* graph);

bool canFinish(int numCourses, int** prerequisites,
               int prerequisitesSize, int* prerequisitesColSize)
{
    struct Graph* graph = create_Graph(numCourses);
    if (!graph) return false;

    for(int i = 0; i < prerequisitesSize; ++i)
    {
        int course = prerequisites[i][0];
        int pre = prerequisites[i][1];
        add_Edge(graph, course, pre);
    }

    int* color = (int*)calloc(numCourses, sizeof(int));
    bool hasCycle = false;

    for(int i = 0; i < numCourses; ++i)
        if(color[i] == 0)
            if(!dfs(i, color, graph))
            {
                hasCycle = true;
                break;
            }
        

    free(color);
    free_Graph(graph);
    return !hasCycle;
}

struct Graph* create_Graph(int Course_Num)
{
    if (Course_Num <= 0) return NULL;

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (!graph) return NULL;

    graph -> Course_Num = Course_Num;
    graph -> Node = (struct GraphNode**)malloc(Course_Num * sizeof(struct GraphNode*));
    if (!graph -> Node)
    {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < Course_Num; ++i)
    {
        graph -> Node[i] = (struct GraphNode*)malloc(sizeof(struct GraphNode));
        if (!graph -> Node[i])
        {
            for (int j = 0; j < i; ++j)
                free(graph -> Node[j]);
            free(graph -> Node);
            free(graph);
            return NULL;
        }
        graph -> Node[i] -> Course_ID = i;
        graph -> Node[i] -> next = NULL;
    }

    return graph;
}

void add_Edge(struct Graph* graph, int Course_ID, int Prerequisite_Course_ID)
{
    if (!graph || Course_ID < 0 || Prerequisite_Course_ID < 0)
        return;

    struct GraphNode* newNode = (struct GraphNode*)malloc(sizeof(struct GraphNode));
    newNode -> Course_ID = Prerequisite_Course_ID;
    newNode -> next = NULL;

    newNode -> next = graph -> Node[Course_ID] -> next;
    graph -> Node[Course_ID] -> next = newNode;
}

void free_Graph(struct Graph* graph)
{
    if (!graph) return;

    for (int i = 0; i < graph -> Course_Num; ++i)
    {
        struct GraphNode* p = graph -> Node[i] -> next;
        while(p != NULL)
        {
            struct GraphNode* temp = p;
            p = p -> next;
            free(temp);
        }
        free(graph -> Node[i]);
    }

    free(graph -> Node);
    free(graph);
}

bool dfs(int cur, int* color, struct Graph* graph)
{
    color[cur] = 1;

    struct GraphNode* p = graph -> Node[cur] -> next;
    while(p != NULL)
    {
        int neighbor = p -> Course_ID;
        if(color[neighbor] == 1)
            return false;
        else if(color[neighbor] == 0)
            if(!dfs(neighbor, color, graph))
                return false;

        p = p -> next;
    }
    color[cur] = 2;
    return true;
}

// @lc code=end

