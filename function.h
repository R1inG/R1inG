#include "entity.h"
#include<stdio.h>
#include<string.h>
#include <conio.h>
#include <windows.h>
#include <errno.h>
#define MAX 100

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
