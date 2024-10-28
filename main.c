
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include"function.h"
#include"entity.h"
#include"loan_function.h"


int main(void) {
    printf("***********欢迎来到仓库管理系统************\n");
    int type=login();
    if(type==0)//进入学生
    {
        studentMenu();
    }
    if(type==1)
    {
        adminMenu();
    }
    return 0;
}



