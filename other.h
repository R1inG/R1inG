#ifndef __OTHER__
#define __OTHER__

#include"loan_function.h"
#include"entity.h"
#include"user_function.h"
#include"item_function.h"

void bubbleSore(int arr[],int n){
    for(int i = 0; i < n-1; i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]<arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void readUserBorrowCount(){
    FILE *file = fopen("users.txt", "r");
    FILE *file2 = fopen("loans.txt", "r");
    if(file == NULL){
        perror("Unable to open file");
        return;
    }else if(file2 == NULL){
        perror("Unable to open file");
        return;
    }
    User user;
    Loan loan;
    int count = 0;
    char username[100][100];
    int borrowCount[100]={0};
    while(fscanf(file,"%99[^,],%99[^,],%d\n",user.user_name,user.password,&user.user_type)==3){
        strcpy(username[count] , user.user_name);
        count++;
    }

    while (fscanf(file2, "%d,%99[^,],%99[^,],%d,%d,%99s\n", &loan.loan_id, loan.user_name, loan.item_name, &loan.loan_quantity, &loan.return_quantity, loan.status) == 6) {
        for (int i = 0; i < count; i++) {
            if (strcmp(username[i], loan.user_name) == 0) {
                borrowCount[i]++;
            }
        }
    }

    bubbleSore(borrowCount,count);

    if(count>10){
        count=10;
    }

    for(int i=0;i<count;i++){
        printf("%10s |", username[i]);
        for(int j=0; j < borrowCount[i] ; j++){
            printf("*");
        }
        printf("\n");
    }
    
    fclose(file);
    fclose(file2);
}

void readItemBorrowCount(){
    FILE *file = fopen("items.txt", "r");
    FILE *file2 = fopen("loans.txt", "r");
    if(file == NULL){
        perror("Unable to open file");
        return;
    }else if(file2 == NULL){
        perror("Unable to open file");
        return;
    }
    Item item;
    Loan loan;
    int count = 0;
    char itemName[100][100];
    int borrowCount[100]={0};
    while(fscanf(file,"%d,%99[^,],%99[^,],%d,%d\n",&item.item_id,item.item_name,item.category,&item.quantity,&item.shelve_id)==5){
        strcpy(itemName[count] , item.item_name);
        count++;
    }

    while (fscanf(file2, "%d,%99[^,],%99[^,],%d,%d,%99s\n", &loan.loan_id, loan.user_name, loan.item_name, &loan.loan_quantity, &loan.return_quantity, loan.status) == 6) {
        for (int i = 0; i < count; i++) {
            if (strcmp(itemName[i], loan.item_name) == 0) {
                borrowCount[i]+=loan.loan_quantity;
            }
        }
    }
    
    bubbleSore(borrowCount,count);

    if(count>10){
        count=10;
    }

    for(int i=0;i<count;i++){
        printf("%10s | ", itemName[i]);
        for(int j=0; j < borrowCount[i] ; j++){
            printf("*");
        }
        printf("\n");
    }
    
    fclose(file);
    fclose(file2);
}


#endif
