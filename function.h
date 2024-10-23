#include "entity.h"
#include<stdio.h>
#include<string.h>
#include <conio.h>
#include <windows.h>
#include <errno.h>
#define MAX 100
// void addItem(Item item){

// }
void deleteItem(Item item){

}
void updateItem(Item item){

}
Item *searchItemID(int item_id){

}
Item *searchItemName(char item_name[MAX]){

}
void sortItemsByQuantity(){

}
void sortItemsByName(){

}

// void registerUser(User user){

// }
// User *loginUser(char *username, char *password){

// }
// void updateUser(User user){

// }
// void changeUserType(char userName[MAX], char userType[MAX]){
    
// }

/********输入密码******** */
void inputPassword(char *password) {
    char input_char;
	int index = 0;
	fflush(stdin);//清除输入缓存
	//密码显示*号且支持退格  
	while((input_char = getch()) != '\r'){//换行符 
		if(input_char == '\b'){//退格键 
			if(index < 0)
				continue;
			if(index > 0){
				putchar('\b');
				putchar(' ');
				putchar('\b');
				index--;
			}	
		}else{
			printf("*");
			password[index++] = input_char;
		}
	}
	password[index] = '\0';//结束符

}

/********从文件中读取用户数据*******/
int readUsersFromFile(User users[], int maxUsers) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        perror("无法打开文件");
        return 0;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < maxUsers) {
        sscanf(line, "%99[^,],%99[^,],%d", users[count].user_name, users[count].password, &users[count].user_type);
        count++;
    }

    fclose(file);
    return count;
}

/**********保存用户数据到文件***********/ 
void saveUsersToFile(User users[], int numUsers) {
    FILE *file = fopen("users.txt", "w");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s,%s,%d\n", users[i].user_name, users[i].password, users[i].user_type);
    }

    fclose(file);
}

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
/**************登录************* */
// 登录函数
void login(){
    User users[MAX];
    int numUsers = readUsersFromFile(users, MAX);

    char username[MAX];
    char password[MAX];

    printf("请输入用户名: ");
    scanf("%99s", username); // 限制输入长度为99个字符，防止缓冲区溢出
    printf("请输入密码: ");
    // scanf("%99s", password); // 限制输入长度为99个字符，防止缓冲区溢出

    inputPassword(password);

    int successIndex = -1;
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].user_name) == 0 && strcmp(password, users[i].password) == 0) {
            successIndex = i;
            break;
        }
    }

    if (successIndex != -1) {
        printf("登录成功！\n");
        if (users[successIndex].user_type == 0) {
             printf("欢迎进入仓库管理系统（学生）");// 学生登录，进入学生系统
        } else if (users[successIndex].user_type == 1) {
             printf("欢迎进入仓库管理系统（管理员）"); // 管理员登录，进入管理员系统
        }
    } else {
        printf("登录失败：用户名或密码错误。\n");
    }
}

/************更改用户密码************* */

// 修改用户密码
int updateUserPassword(User users[], int numUsers, const char* username, const char* newPassword) {
    int flag=-1;
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].user_name, username) == 0) {
            strcpy(users[i].password, newPassword);
            flag=1;
            break;
        }
    }
    return flag;
}

// 修改用户名和密码
int updateUser(User users[], int numUsers, const char* oldUsername, const char* newUsername, const char* newPassword) {
    int flag=-1;
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].user_name, oldUsername) == 0) {
            strcpy(users[i].user_name, newUsername);
            strcpy(users[i].password, newPassword);
            flag=1;
            break;
        }
    }
    return flag;
}

//学生修改密码
void stuChangePassword(){
    User users[MAX];
    int numUsers = readUsersFromFile(users, MAX);
    char username[MAX];
    char newPassword[MAX];
    char password[MAX];
    printf("请输入用户名: ");
    scanf("%99s", username);
    printf("请输入原密码：");
    inputPassword(password);
    //检查原密码是否正确
    int successIndex = -1;
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].user_name) == 0 && strcmp(password, users[i].password) == 0) 
        {
            successIndex = i;
            break;
        }
    }
    if (successIndex != -1) {
        printf("请输入新密码: ");
        // scanf("%99s", password);
    
        inputPassword(newPassword);
        if(updateUserPassword(users, numUsers, username, newPassword)==1)
        {
            saveUsersToFile(users, numUsers);
            printf("密码更新成功！\n");
        }
        else
            printf("更新失败！\n");
    }
     else {
        printf("密码错误！！！\n");
    }
}


//管理员修改用户名密码
void admChangePassword(){
    User users[MAX];
    int numUsers = readUsersFromFile(users, MAX);
    char admUsername[MAX];
    char stuUsername[MAX];
    char password[MAX];
    char newUsername[MAX]="";
    char newPassword[MAX];
    printf("请输入管理员用户名: ");
    scanf("%99s", admUsername);
    printf("请输入原密码：");

    inputPassword(password);

    //检查原密码是否正确
    int successIndex = -1;
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(admUsername, users[i].user_name) == 0 && strcmp(password, users[i].password) == 0) {
            successIndex = i;
            break;
        }
    }
    
    if (successIndex != -1){
        printf("请输入需要修改的用户名：\n");
        scanf("%99s", stuUsername);
        int index=0;
        for(int i=0;i<numUsers;i++)
        {
            if(strcmp(users[i].user_name,stuUsername)==0)
            {
                index=i;
                printf("请输入新用户名（如果不需要请输入-1）：\n");
                scanf("%99s", newUsername);
                if(strcmp(newUsername,"-1")!=0&&users[index].user_type!=1)
                {
                    for(int k=0;k<numUsers;k++)
                    {
                        if(strcmp(newUsername,users[k].user_name)==0)
                        {
                            printf("用户已经存在！！\n");
                            break;
                        }
                        else
                        {
                            strcpy(users[index].user_name,newUsername);
                        }

                        printf("用户名修改成功！！！\n");
                    }          
                }
                else if(strcmp("-1",newUsername)==0)
                {
                    printf("请输入新密码：\n");
                    inputPassword(newPassword);

                    if(updateUserPassword(users, numUsers, users[index].user_name, newPassword)==1)
                    {
                        saveUsersToFile(users, numUsers);
                        printf("密码更新成功！\n");
                        saveUsersToFile(users,numUsers);
                        break;
                    }
                    else
                        printf("更新失败！\n");            
                }

                
            }
            
        }
        if(index==0)
            printf("无此用户！！！\n");
    }
    else
    {
        printf("账号或者密码错误!!!\n");
    }
}


/*********注册********* */
void Register() 
{
    User a; // 用来接收用户输入的结构体
    User users[MAX];
    int numUsers = readUsersFromFile(users, MAX);

    printf("欢迎来到注册界面!\n");

    FILE *pf = fopen("users.txt", "r"); // 以文本方式打开文件进行读取
    if (!pf) { // 如果打开失败
        printf("%s\n", strerror(errno)); // 输出错误信息
        return;
    }

    // 检查用户名是否重复
    printf("请输入您的用户名>> ");
    scanf("%99s", a.user_name);

    for(int i=0;i<numUsers;i++)
    {
        if (strcmp(a.user_name, users[i].user_name) == 0) { // 用户名已存在
            printf("此用户名已存在，请重新输入!\n");
            return;
        }
    }

    // 输入其他信息
    printf("请输入您的用户类型 (0: 学生, 1: 管理员)>> ");
    scanf("%d", &a.user_type);
    if(a.user_type!=1&&a.user_type!=0)
    {
        printf("输入用户类型有误！！！\n");
        return;
    }

    // 输入密码
    char password1[MAX];
    char password2[MAX];
    printf("请输入你的密码：\n");
    
    inputPassword(password1);

    printf("\n请再次确认您的密码>> ");
    
    inputPassword(password2);

    // 确认密码
    while (strcmp(password1, password2) != 0) {
        printf("\n两次密码不匹配! 请重新输入密码>> ");
        inputPassword(password1);
        printf("\n请再次确认>> ");
        inputPassword(password2);
    }
    strcpy(a.password,password1);
    

    // 写入用户信息到文件
    pf = fopen("users.txt", "a"); // 修改为以文本追加方式打开文件
    if (!pf) { // 检查文件打开是否成功
        printf("%s\n", strerror(errno));
        return;
    }

    // 写入用户信息为文本格式
    fprintf(pf, "\n%s,%s,%d", a.user_name, a.password, a.user_type); // 使用 fprintf 写入文本格式
    printf("\n账号注册成功，请登录!\n");
    fclose(pf); // 关闭文件
}


/***********改变用户类型（放在管理员系统里）************ */
void changeUserType()
{
    User users[MAX];
    int numUsers = readUsersFromFile(users, MAX);
    char admUserName[MAX];
    char userName[MAX];
    char admPassword[MAX];
    char tmp[MAX];
    int type;
    printf("请输入管理员用户名：\n");
    scanf("%99s",admUserName);
    printf("请输入密码：\n");
    inputPassword(admPassword);

    //检查原密码是否正确
    int tag=0;
    for (int i = 0; i < numUsers; i++) 
    {
        if (strcmp(admUserName, users[i].user_name) == 0 && strcmp(admPassword, users[i].password) == 0) {
            tag=1;
            break;
        }
    }
    if(tag==0)
    {
        printf("用户名或密码错误！！！\n");
        return;
    }
    else
    {
        printf("\n请输入需要修改的用户用户名：\n");
        scanf("%99s",userName);
        int successIndex = -1;
        for (int j = 0; j < numUsers; j++) 
        {
            if (strcmp(userName, users[j].user_name) == 0)
            {
                successIndex=j;
                break;
            }
        }
        if(successIndex==-1)
        {
            printf("未找到该用户！！\n");
            return;
        }
        else{
            printf("请输入你要修改的类型（0或1）\n");
            scanf("%d",&type);
            if(type!=1&&type!=0)
            {
                printf("输入的类型有误！！！\n");
                return;
            }
            else
            {
                users[successIndex].user_type=type;
                printf("修改成功！\n");
            }
            saveUsersToFile(users, numUsers);
        }
    }
    
}


/************添加物品*************/
void addItem()
{
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


/************修改物品*************/
void updateItem(){
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
