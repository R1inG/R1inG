#include <stdio.h>
#include <string.h>
#include "entity.h"
#include <stdlib.h>
#include <limits.h>
#include "loan_function.h"
#define NUM_SHELVES 8
#define INF INT_MAX

Graph* createGraph() {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->edges = (int**)malloc(NUM_SHELVES * sizeof(int *));
    for (int i = 0; i < NUM_SHELVES; i++) {
        graph->edges[i] = (int *)malloc(NUM_SHELVES * sizeof(int));
    }
    return graph;
}
// 初始化距离矩阵
void initGraph(Graph *graph) {
    int distances[NUM_SHELVES][NUM_SHELVES] = {
        {  0, 12, 45, 33, 23, 15, 44, 20 },
        { 12,  0, 23, 10, 38, 24, 30, 42 },
        { 45, 23,  0, 37, 29, 14, 46, 10 },
        { 33, 10, 37,  0, 49, 34, 15, 20 },
        { 23, 38, 29, 49,  0, 39, 13, 30 },
        { 15, 24, 14, 34, 39,  0, 44, 21 },
        { 44, 30, 46, 15, 13, 44,  0, 48 },
        { 20, 42, 10, 20, 30, 21, 48,  0 }
    };

    for (int i = 0; i < NUM_SHELVES; i++) {
        for (int j = 0; j < NUM_SHELVES; j++) {
            graph->edges[i][j] = distances[i][j];
        }
    }
}

// DP数组，用于存储子问题的最短路径结果
int dp[1 << NUM_SHELVES][NUM_SHELVES];
int path[1 << NUM_SHELVES][NUM_SHELVES];  // 用于记录路径

// tsp 函数计算最短路径
int tsp(Graph *graph, int mask, int pos, int target_mask) {
    if (mask == target_mask) {
        return graph->edges[pos][0];
    }

    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;
    int best_next = -1;

    for (int i = 0; i < NUM_SHELVES; i++) {
        if (!(mask & (1 << i)) && (target_mask & (1 << i))) {
            int new_ans = graph->edges[pos][i] + tsp(graph, mask | (1 << i), i, target_mask);
            if (new_ans < ans) {
                ans = new_ans;
                best_next = i;  // 记录最佳下一节点
            }
        }
    }

    dp[mask][pos] = ans;
    path[mask][pos] = best_next;  // 记录当前mask和pos下的最佳下一节点
    return ans;
}

// 输出路径
void printPath(int target_mask) {
    int mask = 1, pos = 0;
    printf("路线：%d ", pos);
    while (mask != target_mask) {
        pos = path[mask][pos];
        printf("-> %d ", pos);
        mask |= (1 << pos);
    }
    printf("-> 0\n");
}

// 计算最短路径的函数
void calculateShortestPath(Queue *q) {
    Graph *graph = createGraph();
    initGraph(graph);

    // 动态输入目标货架集合
    int target_shelves[NUM_SHELVES];
    int target_count=ShelveNumber(q);
    if(target_count==-1){
        printf("队列为空！\n");
        return;
    }

    printf("请输入目标货架数量: %d\n",target_count);
    
    printf("请输入目标货架编号（1 到 7）：");
    for (int i = 0; i < target_count; i++) {
        scanf("%d", &target_shelves[i]);
    }

    // 创建目标货架集合的掩码
    int target_mask = 0;
    for (int i = 0; i < target_count; i++) {
        target_mask |= (1 << target_shelves[i]);
    }
    target_mask |= 1; // 起点始终在集合中

    // 初始化 dp 数组
    memset(dp, -1, sizeof(dp));
    memset(path, -1, sizeof(path));

    // 计算最短路径
    int result = tsp(graph, 1, 0, target_mask);

    printf("最短路径长度: %d\n", result);
    printPath(target_mask);

    // 释放内存
    for (int i = 0; i < NUM_SHELVES; i++) {
        free(graph->edges[i]);
    }
    free(graph->edges);
    free(graph);
}

