#ifndef __loan
#define __loan

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "entity.h"
void initQueue(Queue* queue){
    queue->front = queue->front = NULL;
}

int isQueueEmpty(Queue* queue){
    return (queue->front == NULL);
}

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

void dequeue(Queue *q) {
    if(!isQueueEmpty(q)){
        q->front = q->front->next;
    }
    else{
        printf("Queue is empty!\n");
    }
}

void addLoanRecord(Loan loans[], int loan_id, const char *user_name, const char *item_name, int loan_quantity) {
    loans[loan_id].loan_id = loan_id;
    strcpy(loans[loan_id].user_name , user_name);
    strcpy(loans[loan_id].item_name , item_name);
    loans[loan_id].loan_quantity = loan_quantity;
    strcpy(loans[loan_id].status , "borrowed");
}

void updateReturnRecord(Loan loans[], int loan_id, int return_quantity) {
    loans[loan_id].return_quantity = return_quantity;
    strcpy(loans[loan_id].status, "Returned");
}

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


#endif