
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include"function.h"
#include"entity.h"
#include"loan_function.h"

int main(void){
    Loan loans[100];
    addLoanRecord(loans,1,"zyh","fff",12);
    saveLoanFile(loans,loans,size(loans));
    return 0;
}


