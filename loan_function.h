#ifndef __LOAN
#define __LOAN

//初始化队列
void initQueue(Queue* queue);
//判断队列是否为空
int isQueueEmpty(Queue* queue);
//展示当前队列数据
void showQueue(Queue *q);
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
int readLoanFile(char *filename, Loan loans[], int maxLoans);
void searchHistory(char *filename);

#endif
