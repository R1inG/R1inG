#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"entity.h"
#include"loan_function.h"

//初始化队列
void initQueue(Queue* queue){
    queue->front = queue->front = NULL;
}
//判断队列是否为空
int isQueueEmpty(Queue* queue){
    return (queue->front == NULL);
}
//展示当前队列数据
void showQueue(Queue *q){
    QueueNode *p = q->front;
    int i = 1;
    while(p != NULL){
        printf("%d:用户：%s, 物品：%s , 物品id: %d, 数量: %d\n",i,p->user_name,p->item_id,p->item_name,p->quantity);
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
//出列
void dequeue(Queue *q) {
    if(!isQueueEmpty(q)){
        q->front = q->front->next;
    }
    else{
        printf("Queue is empty!\n");
    }
}

//用户借用请求
void borrowRequest(Queue *q) {
    int item_id,borrow_quantity;
    char user_name[100],item_name[100];
    Item items[100];
    Loan loans[10000];

    int loan_id = readLoanFile("loans.txt",loans,10000);

    printf("输入你要借的物品id: ");
    scanf("%d",&item_id);
    printf("输入你要借的物品名称: ");
    scanf("%99s",item_name);
    printf("输入你的用户名: ");
    scanf("%99s",user_name);
    printf("输入你要借的物品数量: ");
    scanf("%d",&borrow_quantity);

    int count = readItemsFromFile(items,100);
    int now_quantity = 0;
    for(int i = 0 ; i < count ; i++){
        if(strcmp(items[i].item_name, item_name)==0)
            now_quantity += items[i].quantity;
    }
    if(borrow_quantity > now_quantity) {
        printf("你所借的物品库存量不足!\n");
        return;
    }
    
    enqueue(q,item_id, user_name, item_name, borrow_quantity);

    addLoanRecord(loans, loan_id, user_name, item_name, borrow_quantity);

    saveLoanFile("loans.txt",loans,10000);

    printf("请记住您的借用码:%d", loan_id);
}
//用户归还请求
void returnRequest(Queue *q) {
    int return_quantity,item_id;
    int loan_id;
    char user_name[100],item_name[100];
    Loan loans[10000];

    printf("输入借用码：");
    scanf("%d", &loan_id);
    printf("输入你要借的物品id: ");
    scanf("%d",&item_id);
    printf("输入你要借的物品名称: ");
    scanf("%99s",item_name);
    printf("输入你的用户名: ");
    scanf("%99s",user_name);
    printf("输入你要归还的物品数量：");
    scanf("%d", &return_quantity);

    enqueue(q,item_id,item_name,user_name,return_quantity);

    updateReturnRecord(loans, loan_id, return_quantity);

    saveLoanFile("loans.txt",loans,10000);

}
// 添加历史记录
void addLoanRecord(Loan loans[], int loan_id, const char *user_name, const char *item_name, int loan_quantity) {
    loans[loan_id].loan_id = loan_id;
    strcpy(loans[loan_id].user_name , user_name);
    strcpy(loans[loan_id].item_name , item_name);
    loans[loan_id].loan_quantity = loan_quantity;
    strcpy(loans[loan_id].status , "borrowed");
}
// 修改归还记录
void updateReturnRecord(Loan loans[], int loan_id, int return_quantity) {
    loans[loan_id].return_quantity = return_quantity;
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
        // 读取一条贷款记录
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
void searchHistory(char *filename) {
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
