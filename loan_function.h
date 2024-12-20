#ifndef __LOAN
#define __LOAN

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"entity.h"
#include"Item_function.h"

//初始化队列
void initQueue(Queue* queue);
//判断队列是否为空
int isQueueEmpty(Queue* queue);
//展示当前队列数据
void showQueue(Queue *q);
//保存队列到文本
 void saveQueueToFile(char *filename, Queue *q);
 //从文本中读取队列
 void readQueueToFile(char *filename, Queue *q);
//入列
void enqueue(Queue *q, int item_id, const char *item_name, const char *user_name, int quantity);
//用户借用请求
void borrowRequest(Queue *q);
//用户归还请求
void returnRequest(Queue *q);
// 添加历史记录
void addLoanRecord(Loan loans[], int loan_id, const char *user_name, const char *item_name, int loan_quantity);
// 修改归还记录
void updateReturnRecord(Loan loans[], int loan_id, int return_quantity);
//把历史记录保存在文本中
void saveLoanFile(char *filename, Loan loans[], int size);
//读取历史记录
int readLoanFile(char *filename, Loan loans[], int maxLoans);
//读取历史记录
void searchLoanHistory(char *filename);
//查询历史记录（用户名查找）
int searchLoanUsername(char *filename, char *user_name);
//查询历史记录（物品查找）
int searchLoanItem(char *filename, char *item_name);

//初始化队列
void initQueue(Queue* queue){
    queue->front = queue->rear = NULL;
}
//判断队列是否为空
int isQueueEmpty(Queue* queue){
    return (queue->front == NULL);
}
//展示当前队列数据
void showQueue(Queue *q){
    QueueNode *p = q->front;
    while(p != NULL){
        printf("用户：%s, 物品：%s , 物品id: %d, 数量: %d\n",p->user_name,p->item_name,p->item_id,p->quantity);
        p=p->next;
    }
}
//入列
void enqueue(Queue *q, int item_id, const char *item_name, const char *user_name, int quantity) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->item_id = item_id;
    strcpy(newNode->item_name, item_name);
    strcpy(newNode->user_name, user_name);
    newNode->quantity = quantity;
    newNode->next = NULL;
    
    if (isQueueEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 复制队列中的第i个节点
QueueNode* copyQueueNodeAtIndex(Queue *q, int i) {
    if (q == NULL || i <= 0 || isQueueEmpty(q)) {
        return NULL;
    }

    int count = 1; // 从队列的第一个节点开始计数
    QueueNode *current = q->front;

    while (current != NULL && count < i) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        // 没有找到第i个节点
        return NULL;
    }

    // 复制第i个节点
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->item_id = current->item_id;
    strncpy(newNode->item_name, current->item_name, sizeof(newNode->item_name) - 1);
    newNode->item_name[sizeof(newNode->item_name) - 1] = '\0';
    strncpy(newNode->user_name, current->user_name, sizeof(newNode->user_name) - 1);
    newNode->user_name[sizeof(newNode->user_name) - 1] = '\0';
    newNode->quantity = current->quantity;
    newNode->next = NULL;

    return newNode;
}

//出列
void dequeue(Queue *q) {
    if(!isQueueEmpty(q)){
        q->front = q->front->next;
    }
    else{
        printf("Queue is empty!\n");
    }
}

//队列中物品所在的货架
int ShelveNumber(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    
    int locateShelve[8]={0}; // 存储货架ID
    Item items[100]; // 假设这是从文件中读取的物品列表
    int number = readItemsFromFile(items, 100); // 读取物品信息
    QueueNode* current = q->front; // 使用临时指针遍历队列
    while (current != NULL) {
        for (int i = 0; i < number; i++) {
            // 使用 strcmp 进行字符串比较
            if (strcmp(items[i].item_name, current->item_name) == 0) {
                locateShelve[items[i].shelve_id] = 1; // 找到对应货架ID
                break; // 找到后可提前退出内层循环
            }
        }
        current = current->next; // 移动到下一个节点
    }
    int count = 0;
    //printf("队列中所有物品所在货架ID:");
    for (int i = 1; i < 8; i++) {
        if(locateShelve[i]==1){
            //printf("%d ", i);
            count++;
        }
    }
    //printf("\n");
    return count;
}

int *ShelveManager(Queue *q){
    
    int locateShelve[8]={0}; // 存储货架ID
    Item items[100]; // 假设这是从文件中读取的物品列表
    int number = readItemsFromFile(items, 100); // 读取物品信息
    QueueNode* current = q->front; // 使用临时指针遍历队列
    while (current != NULL) {
        for (int i = 0; i < number; i++) {
            // 使用 strcmp 进行字符串比较
            if (strcmp(items[i].item_name, current->item_name) == 0) {
                locateShelve[items[i].shelve_id] = 1; // 找到对应货架ID
                break; // 找到后可提前退出内层循环
            }
        }
        current = current->next; // 移动到下一个节点
    }
    int count = 0;
    int *index=(int *)malloc(sizeof(int));
    //printf("队列中所有物品所在货架ID:");
    for (int i = 1; i < 8; i++) {
        if(locateShelve[i]==1){
            //printf("%d ", i);
            index[count]=i;
            printf("%d",index[count]);
            count++;
        }
    }
    //printf("\n");
    return index;
}

// 保存队列到文本中
void saveQueueToFile(char *filename, Queue *q) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }
    QueueNode *current = q->front;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%d\n",
                current->item_id,
                current->item_name,
                current->user_name,
                current->quantity);
        current = current->next;
    }
    fclose(file);
}

// 从文件读取队列
void readQueueFromFile(char *filename, Queue *q) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }

    initQueue(q); // 初始化队列，确保是空的队列

    int item_id, quantity;
    char item_name[100], user_name[100];
    
    while (fscanf(file, "%d,%99[^,],%99[^,],%d\n", &item_id, item_name, user_name, &quantity) == 4) {
        enqueue(q, item_id, item_name, user_name, quantity);
    }

    fclose(file);

    showQueue(q);
}

//用户借用请求
void borrowRequest(Queue *q) {
    int item_id,borrow_quantity;
    char user_name[100],item_name[100];
    Item items[100];
    Loan loans[1000];
    Shelve shelves[100];
    int loan_id = readLoanFile("loans.txt",loans,1000);

    printf("输入你要借的物品id: ");
    scanf("%d",&item_id);
    printf("输入你要借的物品名称: ");
    scanf("%99s",item_name);
    printf("输入你的用户名: ");
    scanf("%99s",user_name);
    printf("输入你要借的物品数量: ");
    scanf("%d",&borrow_quantity);

    int count = readItemsFromFile(items,100);
    int numShelves=readShelvesFromFile(shelves,100);
    int now_quantity = 0;
    int index=-1;
    for(int i = 0 ; i < count ; i++){
        if(strcmp(items[i].item_name, item_name)==0)
        {
            now_quantity += items[i].quantity;
            index=i;
            break;
        }
            
    }
    // if(borrow_quantity > now_quantity) {
    //     printf("你所借的物品库存量不足!\n");
    //     return;
    // }
    // else 
    if(index==-1)
    {
        printf("未找到该物品！\n");
        return;
    }
    else
    {
        items[index].quantity-=borrow_quantity;
        shelves[items[index].shelve_id-1].ActualCapacity-=borrow_quantity;
        enqueue(q,item_id,  item_name,user_name, borrow_quantity);

        //addLoanRecord(loans, loan_id, user_name, item_name, borrow_quantity);

        //saveLoanFile("loans.txt",loans,loan_id+1);
        //saveItemsToFile(items,count);
        //saveShelvesFromFile(shelves,numShelves);
        // printf("请记住您的借用码:%d\n", loan_id);

    }
    
}
//用户归还请求
void returnRequest(Queue *q) {
    int return_quantity,item_id;
    Loan loans[1000];
    Item items[100];
    int numitems=readItemsFromFile(items,100);
    Shelve shelves[100];
    int numshelves=readShelvesFromFile(shelves,100);
    int loan_id ;
    int numloans=readLoanFile("loans.txt",loans,1000);;
    char user_name[100],item_name[100];

    printf("请输入借用码：");
    scanf("%d", &loan_id);
    printf("请输入物品编号:\n");
    scanf("%d",&item_id);
    int index=-1;
    for(int i=0;i<numloans;i++)
    {
        if(loan_id==loans[i].loan_id)
        {
            index=i;
            strcpy(user_name,loans[i].user_name);
            strcpy(item_name,loans[i].item_name);
            break;
        }
    }
    if(index==-1)
    {
        printf("未找到该借用码记录！\n");
        return;
    }
    else
    {
        printf("输入你要归还的物品数量：");
        scanf("%d", &return_quantity);
        if(return_quantity>loans[index].loan_quantity)
        {
            printf("归还数量多于借用数量！！\n");
            //return;
        }
        else
        {
            items[item_id-1].quantity+=return_quantity;
            shelves[items[item_id].shelve_id-2].ActualCapacity+=return_quantity;
            
            updateReturnRecord(loans, loan_id, return_quantity);
            saveItemsToFile(items,numitems);
            saveShelvesFromFile(shelves,numshelves);
            saveLoanFile("loans.txt",loans,numloans);
            printf("已添加到归还请求！\n");
        }
        //enqueue(q,item_id,item_name,user_name,return_quantity);
    }
}


// 添加历史记录
void addLoanRecord(Loan loans[], int loan_id, const char *user_name, const char *item_name, int loan_quantity) {
    loans[loan_id].loan_id = loan_id;
    strcpy(loans[loan_id].user_name , user_name);
    strcpy(loans[loan_id].item_name , item_name);
    loans[loan_id].loan_quantity = loan_quantity;
    loans[loan_id].return_quantity=0;
    strcpy(loans[loan_id].status , "borrowed");
}
// 修改归还记录
void updateReturnRecord(Loan loans[], int loan_id, int return_quantity) {
    loans[loan_id].return_quantity += return_quantity;
    strcpy(loans[loan_id].status, "Returned");
}

//把历史记录保存在文本中
void saveLoanFile(char *filename, Loan loans[], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }
    
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d,%s,%s,%d,%d,%s\n",
                loans[i].loan_id,
                loans[i].user_name,
                loans[i].item_name,
                loans[i].loan_quantity,
                loans[i].return_quantity,
                loans[i].status);
    }
    fclose(file);
}
//读取历史记录文本，并返回数量
int readLoanFile(char *filename, Loan loans[], int maxLoans) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return -1;
    }

    int count = 0;
    while (count < maxLoans) {
        // 读取一条借货记录
        if (fscanf(file, "%d,%99[^,],%99[^,],%d,%d,%99[^\n]",
                   &loans[count].loan_id, loans[count].user_name, loans[count].item_name,
                   &loans[count].loan_quantity, &loans[count].return_quantity, loans[count].status) == 6) {
            count++; // 成功读取一条记录
        } else {
            if (feof(file)) {
                break; // 文件末尾
            }
            // 读取失败，可能是格式不正确或其他原因
            fprintf(stderr, "Error reading loan record at line %d\n", count + 1);
            fclose(file);
            return -2;
        }
    }

    fclose(file);
    return count; // 返回读取到的记录数量
}
void searchLoanHistory(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }

    Loan loan;
    // 使用 fscanf 循环读取文件中的每一行
    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%d,%99[^\n]",
                  &loan.loan_id, loan.user_name, loan.item_name,
                  &loan.loan_quantity, &loan.return_quantity, loan.status) == 6) {
        // 打印读取的数据
        printf("%d, %s, %s, %d, %d, %s\n",
               loan.loan_id, loan.user_name, loan.item_name,
               loan.loan_quantity, loan.return_quantity, loan.status);
    }

    fclose(file);
}

int searchLoanUsername(char *filename, char *user_name) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return -1;
    }

    Loan loan;
    int borrow_count = 0;
    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%d,%99[^\n]",
                  &loan.loan_id, loan.user_name, loan.item_name,
                  &loan.loan_quantity, &loan.return_quantity, loan.status) == 6) {
        if (strcmp(loan.user_name, user_name) == 0) {
            printf("记录：ID: %d, 用户: %s, 物品: %s, 借用数量: %d, 归还数量: %d, 状态: %s\n",
                   loan.loan_id, loan.user_name, loan.item_name,
                   loan.loan_quantity, loan.return_quantity, loan.status);
            borrow_count++;
        }
    }

    fclose(file);
    if (borrow_count == 0) {
        printf("未找到用户名为 %s 的历史记录。\n", user_name);
    } else {
        printf("用户名 %s 的借阅总次数为：%d\n", user_name, borrow_count);
    }
    return borrow_count;
}

// 按物品名称查询历史记录并返回借阅次数
int searchLoanItem(char *filename, char *item_name) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return -1;
    }

    Loan loan;
    int borrow_count = 0;
    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%d,%99[^\n]",
                  &loan.loan_id, loan.user_name, loan.item_name,
                  &loan.loan_quantity, &loan.return_quantity, loan.status) == 6) {
        if (strcmp(loan.item_name, item_name) == 0) {
            printf("记录：ID: %d, 用户: %s, 物品: %s, 借用数量: %d, 归还数量: %d, 状态: %s\n",
                   loan.loan_id, loan.user_name, loan.item_name,
                   loan.loan_quantity, loan.return_quantity, loan.status);
            borrow_count++;
        }
    }

    fclose(file);
    if (borrow_count == 0) {
        printf("未找到物品名称为 %s 的历史记录。\n", item_name);
    } else {
        printf("物品名称 %s 的借阅总次数为：%d\n", item_name, borrow_count);
    }
    return borrow_count;
}



#endif
