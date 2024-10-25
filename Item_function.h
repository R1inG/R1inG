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
        sscanf(line, "%d,%99[^,],%99[^,],%d,%d", &items[count].item_id, items[count].item_name, items[count].category,&items[count].quantity,&items[count].shelve_id);
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
        fprintf(file, "%d,%s,%s,%d,%d\n", items[i].item_id, items[i].item_name, items[i].category,items[i].quantity,items[i].shelve_id);
    }

    fclose(file);
}
/********从货架中读取物品数据*******/
int readShelvesFromFile(Shelve shelves[], int maxShelves) {
    FILE *file = fopen("shelves.txt", "r");
    if (!file) {
        perror("无法打开文件");
        return 0;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < maxShelves) {
        if (sscanf(line, "%d,%d,%d", &shelves[count].shelve_id, &shelves[count].StorCapacity, &shelves[count].ActualCapacity) == 3) {
            count++;
        }
    }

    fclose(file);
    return count;
}
/********保存货架数据到文件*******/
void saveShelvesFromFile(Shelve shelves[], int numShelves) {
    FILE *file = fopen("shelves.txt", "w");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    for (int i = 0; i < numShelves; i++) {
        fprintf(file, "%d,%d,%d\n", shelves[i].shelve_id, shelves[i].StorCapacity, shelves[i].ActualCapacity);
    }

    fclose(file);
}
/************添加物品*************/
void addItem()
{
    Item items[MAX];
    Shelve shelves[MAX];
    int item_id;//物品id
    int StorCapacity;
    char item_name[MAX];
    char category[MAX];
    int quantity;
    int numItems = readItemsFromFile(items,MAX);
    int numShelves=readShelvesFromFile(shelves,MAX);
    int shelve_id;
    int successIndex=-1;
    
    printf("请输入新增物品名称：\n");
    scanf("%99s",item_name);
    for(int i=0;i<numItems;i++)
    {
        if(strcmp(items[i].item_name,item_name)==0)
        {
            successIndex=i;
            break;
        }
    }
    if(successIndex==-1)
    {
        item_id=numItems+1;
        printf("请输入新增物品种类：\n");
        scanf("%99s",category);
        printf("请输入新增物品数量：\n");
        scanf("%d",&quantity);
        printf("请输入新增物品货架号：\n");
        scanf("%d",&shelve_id);
        if(quantity<0)
        {
            printf("数量不能为负数！\n");
            return;
        }
        else if(shelves[shelve_id-1].ActualCapacity+quantity>shelves[shelve_id-1].StorCapacity)
        {
            printf("超出货架可容纳容量！\n");
            return;
        }
        else if(shelve_id<0)
        {
            printf("货架号不能为负数！\n");
            return;
        }
        else
        {

            strcpy(items[numItems].item_name, item_name);
            strcpy(items[numItems].category, category);
            items[numItems].item_id = item_id;
            items[numItems].quantity = quantity;
            items[numItems].shelve_id=shelve_id;
            shelves[shelve_id-1].ActualCapacity+=quantity;
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
            //写入货架容量
            saveShelvesFromFile(shelves,numShelves);
            // 写入用户信息为文本格式
            fprintf(pf, "\n%d,%s,%s,%d,%d", item_id, item_name, category, quantity,shelve_id);  // 写入新物品
            fclose(pf);
            printf("添加成功!\n");
        }
            
    }
    else
    {
        shelve_id=items[successIndex].shelve_id;
        printf("请输入新增物品数量：\n");
        scanf("%d",&quantity);
        if(quantity<0)
        {
            printf("数量不能为负数！\n");
            return;
        }

        else if(shelves[shelve_id-1].ActualCapacity+quantity>shelves[shelve_id-1].StorCapacity)
        {
            printf("超出货架可容纳容量！\n");
            return; 
        }
        else
        {

            items[successIndex].quantity += quantity;
            shelves[shelve_id-1].ActualCapacity+=quantity;
            saveItemsToFile(items,numItems);
            saveShelvesFromFile(shelves,numShelves);
            printf("数量更新成功！\n");
        }
    }
    
}


/************修改物品*************/
void updateItem(){
    Item items[MAX];
    Shelve shelves[MAX];
    int numItems=readItemsFromFile(items,MAX);
    int numShelves=readShelvesFromFile(shelves,MAX);
    int choice;
    int newItemID;
    int oldItemID;
    int quantity;
    int shelve_id;
    char oldName[MAX];
    char newName[MAX];
    char newCategory[MAX];
    printf("请输入需要修改的类型：\n");
    printf("物品编号(1)\n");
    printf("物品名称(2)\n");
    printf("物品种类(3)\n");
    printf("物品数量(4)\n");
    printf("物品货架(5)\n");
    scanf("%d",&choice);

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
        case 3:
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
                printf("请输入新种类名称：\n");
                scanf("%99s",newCategory);
                strcpy(items[index1].category,newCategory);
                saveItemsToFile(items,numItems);
                printf("修改成功！！\n");
            }

            break;
        }
        case 4:
        {
            int index1=-1;
            int shelve_id;
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
                shelve_id=items[index1].shelve_id-1;
                printf("请输入数量：\n");
                scanf("%d",&quantity);
                shelves[shelve_id].ActualCapacity-=items[index1].quantity;
                if(quantity>=0)
                {
                    if(shelves[shelve_id].ActualCapacity+quantity>shelves[shelve_id].StorCapacity)
                    {
                        printf("数量超过货架容量！\n");
                        return;
                    }
                    else
                    {
                        items[index1].quantity=quantity;
                        shelves[shelve_id].ActualCapacity+=items[index1].quantity;
                    }
                    
                }
                else
                {
                    printf("数量不能为负数！\n");
                    break;
                }  
                saveItemsToFile(items,numItems);
                saveShelvesFromFile(shelves,numShelves);
                printf("修改成功！！\n");
            }
            break;
        }    
        case 5:
        {
            int index1=-1;
            int index2=-1;
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
                    break;;
            }
            else
            {
                printf("请输入新的货架编号：\n");
                scanf("%d",&shelve_id);
                for(int j=0;j<numItems;j++)
                {
                    if(shelve_id==items[j].shelve_id)
                    {
                        index2=j;
                        break;
                    }
                }
                if(index2==-1)
                {
                    printf("该货架不存在！\n");
                    break;
                }
                else
                {
                    items[oldItemID-1].shelve_id=shelve_id;
                    saveItemsToFile(items,numItems);
                    printf("修改成功！！\n");
                }
            }
            break;
        }
        default:
            printf("无效选择，请重新输入\n");
            break;
    }

    
}

/**************查询物品************* */
void searchItemByID(){
    Item items[MAX];
    int item_id;
    int numItems=readItemsFromFile(items,MAX);
    printf("请输入你要查找的id号：\n");
    scanf("%d",&item_id);
    int low = 0;
    int high = numItems - 1;
    int tag=-1;
    while (low <= high) {
        int mid = low + (high - low) / 2; // 防止溢出的写法
        
        if (items[mid].item_id == item_id) {
            // 找到物品
            printf("物品ID：%d,物品名：%s,物品种类：%s,物品数量：%d,物品所属货架号：%d\n",items[mid].item_id,items[mid].item_name,items[mid].category,items[mid].quantity,items[mid].shelve_id);
            tag=1;
            break;
        } else if (items[mid].item_id < item_id) {
            // 如果中间元素的id小于目标id，搜索右半部分
            low = mid + 1;
        } else {
            // 如果中间元素的id大于目标id，搜索左半部分
            high = mid - 1;
        }
    }
    if(tag==-1)
    {
        printf("该物品不存在！！\n");
    }
}

/**************查询物品************* */
void searchItemName()
{
    Item items[MAX];
    int numItems = readItemsFromFile(items, MAX);
    int tag=-1;
    char item_name[MAX];
    printf("请输入你需要查询的物品名称：\n");
    scanf("%99s",item_name);
    for (int i = 0; i < numItems; i++) 
    {
        if (strcmp(items[i].item_name, item_name) == 0) 
        {
            printf("物品ID：%d,物品名：%s,物品种类：%s,物品数量：%d,物品所属货架号：%d\n",
               items[i].item_id, items[i].item_name, items[i].category, items[i].quantity, items[i].shelve_id);
               tag==1;
        }
    }
    if(tag==-1)
    {
        printf("该物品未找到！！\n");
        return;
    }
}

/**************排序物品（数量）************* */
// 交换两个物品
void swapItems(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序的辅助函数
int partition1(Item items[], int low, int high) 
{
    Item pivot = items[high];  // 选择最后一个元素作为基准
    int i = (low - 1);          // 小于基准的元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素的数量小于或等于基准的数量
        if (items[j].quantity <= pivot.quantity) {
            i++;    // 增加小于基准的元素的索引
            swapItems(&items[i], &items[j]);
        }
    }
    swapItems(&items[i + 1], &items[high]);
    return (i + 1);
}

// 快速排序逻辑
void quickSort1(Item items[], int low, int high) 
{
    if (low < high) {
        // pi是分区后的索引，它将数组分为两部分
        int pi = partition1(items, low, high);
        // 分别对分区后的两部分进行快速排序
        quickSort1(items, low, pi - 1);
        quickSort1(items, pi + 1, high);
    }
}
void sortItemsByQuantity()
{
    Item items[MAX];
    int numItems=readItemsFromFile(items,MAX);
    
    // 调用快速排序逻辑
    quickSort1(items, 0, numItems - 1);
    for (int i = 0; i < numItems; i++) {
        printf("物品ID：%d,物品名：%s,物品种类：%s,物品数量：%d,物品所属货架号：%d\n",
               items[i].item_id, items[i].item_name, items[i].category, items[i].quantity, items[i].shelve_id);
    }
}

/**************排序物品（名称）************* */
// 比较两个物品名称的首字母
int compareItemName(const void *a, const void *b) {
    const Item *itemA = (const Item *)a;
    const Item *itemB = (const Item *)b;
    return (itemA->item_name[0] - itemB->item_name[0]);
}

// 快速排序的辅助函数，使用首字母比较
int partition2(Item items[], int low, int high) {
    Item pivot = items[high];  // 选择最后一个元素作为基准
    int i = (low - 1);          // 小于基准的元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素的名称首字母小于或等于基准的首字母
        if (compareItemName(&items[j], &pivot) <= 0) {
            i++;    // 增加小于基准的元素的索引
            swapItems(&items[i], &items[j]);
        }
    }
    swapItems(&items[i + 1], &items[high]);
    return (i + 1);
}
// 快速排序逻辑
void quickSort2(Item items[], int low, int high) {
    if (low < high) {
        // pi是分区后的索引，它将数组分为两部分
        int pi = partition2(items, low, high);

        // 分别对分区后的两部分进行快速排序
        quickSort2(items, low, pi - 1);
        quickSort2(items, pi + 1, high);
    }
}

void sortItemsByName(){
    Item items[MAX];
    int numItems=readItemsFromFile(items,MAX);
    
    // 调用快速排序逻辑
    quickSort2(items, 0, numItems - 1);
    for (int i = 0; i < numItems; i++) {
        printf("物品ID：%d,物品名：%s,物品种类：%s,物品数量：%d,物品所属货架号：%d\n",
               items[i].item_id, items[i].item_name, items[i].category, items[i].quantity, items[i].shelve_id);
    }
}


/**************查询货架************* */
void searchShelves() {
    Item items[MAX];
    int numItems = readItemsFromFile(items, MAX);
    Shelve shelves[MAX];
    int numShelves = readShelvesFromFile(shelves, MAX);

    for (int i = 0; i < numShelves; i++) {
        int found = 0;
        for (int j = 0; j < numItems; j++) {
            if (items[j].shelve_id == shelves[i].shelve_id) {
                if (!found) 
                {
                    printf("货架号: %d: ", shelves[i].shelve_id);
                    found = 1;
                }
                printf("%s ", items[j].category);
            }
        }
        if (found) {
            printf("\n");
        }
    }
}
