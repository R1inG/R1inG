#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"entity.h"
#define MAX 100

/********从文件中读取物品数据*******/
int readItemsFromFile(Item items[], int maxItems) {
    FILE *file = fopen("items.txt", "r");
    if (!file) {
        perror("无法打开文件");
        return 0;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < maxItems) {
        sscanf(line, "%d,%99[^,],%99[^,],%d", &items[count].item_id, items[count].item_name, items[count].category,&items[count].quantity);
        count++;
    }

    fclose(file);
    return count;
}

/**********保存物品数据到文件***********/
void saveItemsToFile(Item items[], int numUsers) {
    FILE *file = fopen("items.txt", "w");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%d,%s,%s,%d\n", items[i].item_id, items[i].item_name, items[i].category,items[i].quantity);
    }

    fclose(file);
}

/**************添加物品************* */
void addItem(Item item){
    Item items[MAX];
    int item_id;//物品id
    char item_name[MAX];
    char category[MAX];
    int quantity;
    int numItems = readItemsFromFile(items,MAX);
    int successIndex=-1;
    
    printf("请输入新增物品编号：\n");
    scanf("%d",&item_id);
    for(int i=0;i<numItems;i++)
    {
        if(items[i].item_id==item_id)
        {
            successIndex=i;
            break;
        }
    }
    if(successIndex==-1)
    {
        printf("请输入新增物品名字：\n");
        scanf("%99s",item_name);
        printf("请输入新增物品种类：\n");
        scanf("%99s",category);
        printf("请输入新增物品数量：\n");
        scanf("%d",&quantity);
        if(quantity<0)
        {
            printf("数量不能为负数！\n");
            return;
        }
        else
        {

            strcpy(items[numItems].item_name, item_name);
            strcpy(items[numItems].category, category);
            items[numItems].item_id = item_id;
            items[numItems].quantity = quantity;
            numItems++;
            FILE *pf = fopen("items.txt", "a");  // 使用追加模式
            if (!pf) 
            { // 如果打开失败
                printf("%s\n", strerror(errno)); // 输出错误信息
                return;
            }
            
            // 写入用户信息到文件
            if (!pf) 
            { // 检查文件打开是否成功
                printf("%s\n", strerror(errno));
                return;
            }

            // 写入用户信息为文本格式
            fprintf(pf, "%d,%s,%s,%d\n", item_id, item_name, category, quantity);  // 写入新物品
            fclose(pf);
            printf("添加成功!\n");
        }
            
    }
    else
    {
        printf("请输入新增物品数量：\n");
        scanf("%d",&quantity);
        if(quantity<0)
        {
            printf("数量不能为负数！\n");
            return;
        }
        else
        {
            items[successIndex].quantity += quantity;
            saveItemsToFile(items,numItems);
            printf("数量更新成功！\n");
        }
    }
    
}

/**************删除物品************* */
void deleteItem(Item item){

}

/**************修改物品************* */
void updateItem(Item item){
    Item items[MAX];
    int numItems=readItemsFromFile(items,MAX);
    int choice;
    int newItemID;
    int oldItemID;
    char oldName[MAX];
    char newName[MAX];
    printf("请输入需要修改的类型：\n");
    printf("物品编号(1)\n");
    printf("物品名称(2)\n");
    printf("物品种类(3)\n");
    printf("物品数量(4)\n");
    scanf("%d",&choice);
    getchar();
    switch (choice)
    {
        case 1:
        {
            int index1=-1;
            printf("请输入原编号：\n");
            scanf("%d",&oldItemID);
            for(int i=0;i<numItems;i++)
            {
                if(items[i].item_id==oldItemID)
                {
                    index1=i;
                    break; // 找到匹配项后退出循环
                }
            }
            if(index1==-1)
            {
                printf("原编号不存在！\n");
                    return;
            }
            else
            {
                printf("请输入新编号：\n");
                scanf("%d",&newItemID);
                for(int j=0;j<numItems;j++)
                {
                    if(items[j].item_id==newItemID)
                    {
                        printf("该编号已经存在！\n");
                        return;
                    }
                }
                items[index1].item_id=newItemID;
                saveItemsToFile(items,numItems);
                printf("修改成功！！\n");
            }
            break;
        }
        case 2:
        {
            int index2=-1;
            printf("请输入原名称：\n");
            scanf("%99s",oldName);
            int i=0;
            printf("%s",oldName);
            for(int i=0;i<numItems;i++)
            {
                if(strcmp(oldName,items[i].item_name)==0)
                {
                    index2=i;
                    break; // 找到匹配项后退出循环
                }
            }

            if(index2==-1)
            {
                printf("原物品不存在！\n");
                    return;
            }
            else
            {
                printf("请输入新名称：\n");
                scanf("%99s",newName);
                for(int j=0;j<numItems;j++)
                {

                    if(strcmp(items[j].item_name,newName)==0)
                    {
                        printf("该物品已经存在！\n");
                        return;
                    }
                }
                strcpy(items[index2].item_name,newName);
                saveItemsToFile(items,numItems);
                printf("修改成功！！\n");
            }
            break;
        }    
        default:
            printf("无效选择，请重新输入\n");
            break;
    }

    
}

/**************查询物品************* */
Item *searchItemID(int item_id){

}

/**************查询物品************* */
Item *searchItemName(char item_name[100]){

}

/**************查询物品************* */
void sortItemsByQuantity(){

}

/**************查询物品************* */
void sortItemsByName(){

}