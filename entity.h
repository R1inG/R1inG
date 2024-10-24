#ifndef __entity
#define __entity

//物品结构体
typedef struct Item{
    int item_id;//物品id
    char item_name[100];//物品名称
    char category[100];//物品类型
    int quantity;//数量
    int shelve_id;//存放货架位置
} Item;

//货架结构体
typedef struct Shelve{
    int shelve_id;//货架id
    Item *items;//存放物品
    int category;//存放物品类型
    int capacity;//存放容量
}Shelve;

//用户结构体 
typedef struct User{
    char user_name[100];//用户名
    char password[100];//密码
    int user_type;//用户类型 0 学生 1 管理员
} User;

//物品借还模块（队列）先申请先借
//队列节点
typedef struct QueueNode {
    int item_id;//物品id
    char item_name[100];//物品名称
    char user_name[100];//用户名
    int quantity;//数量
    struct QueueNode *next;
} QueueNode;

//队列定义
typedef struct Queue{
    QueueNode *front;
    QueueNode *rear;
} Queue;

//用户借还历史记录模块
typedef struct Loan{
    int loan_id;//借用id
    char user_name[100];//用户名
    char item_name[100];//物品名称
    int loan_quantity;//借用数量
    int return_quantity;//归还数量
    char time[100];
    char status[100];
} Loan;

//仓库布局
typedef struct Graph{
    int shelves_id;
    int **edges;
}Graph;

#endif


