#include"Item_function.h"
#include"user_function.h"


// 物品管理子菜单
void itemManagementMenu() {
    int choice=0;
    do {
        printf("\n物品管理：\n");
        printf("1. 添加物品\n");
        printf("2. 删除物品\n");
        printf("3. 修改物品\n");
        printf("4. 查询物品(ID)\n");
        printf("5. 查询物品(名称)\n");
        printf("6. 物品排序(数量)\n");
        printf("7. 物品排序(首字母)\n");
        printf("8. 返回上一级菜单\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("添加物品功能\n");
                addItem();
                break;
            case 2:
                printf("删除物品功能\n");
                // deleteItem();
                break;
            case 3:
                printf("修改物品功能\n");
                updateItem();
                break;
            case 4:
                printf("通过ID查询物品功能\n");
                searchItemByID();
                break;
            case 5:
                printf("通过名称查找物品功能\n");
                searchItemName();
                break;
            case 6:
                printf("通过物品数量排序功能\n");
                sortItemsByQuantity();
                break;
            case 7:
                printf("通过物品首字母排序功能\n");
                sortItemsByName();
                break;
            case 8:
                printf("返回上一级菜单\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice!=8);  // 选择8时返回上一级菜单
}

// 货架管理子菜单
void shelfManagementMenu() {
    int choice=0;
    do {
        printf("\n货架管理：\n");
        printf("1. 查询货架种类\n");
        printf("2. 返回上一级菜单\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("查询货架功能\n");
                searchShelves();
                break;
            case 2:
                printf("返回上一级菜单\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice != 2);  // 选择2时返回上一级菜单
}

// 用户管理（管理员）子菜单
void admUserManagementMenu() {
    int choice=0;
    do {
        printf("\n用户管理：\n");
        printf("1. 添加用户\n");
        printf("2. 修改用户密码\n");
        printf("3. 修改用户类型\n");
        printf("4. 查询用户\n");
        printf("5. 返回上一级菜单\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("添加用户功能\n");
                Register();
                break;
            case 2:
                printf("修改用户密码功能\n");
                admChangePassword();
                break;
            case 3:
                printf("修改用户类型功能\n");
                changeUserType();
                break;
            case 4:
                printf("查询用户功能\n");
                searchUserByUserName();
                break;
            case 5:
                printf("返回上一级菜单\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice != 5);  // 选择5时返回上一级菜单
}


// 借还管理子菜单
void borrowReturnManagementMenu() {
    int choice=0;
    do {
        printf("\n物品借还管理：\n");
        printf("1. 借用物品\n");
        printf("2. 归还物品\n");
        printf("3. 查看借用记录\n");
        printf("4. 返回上一级菜单\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("借用物品功能\n");
                // borrowItem();
                break;
            case 2:
                printf("归还物品功能\n");
                // returnItem();
                break;
            case 3:
                printf("查看借用记录功能\n");
                // viewBorrowRecords();
                break;
            case 4:
                printf("返回上一级菜单\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice != 4);  // 选择4时返回上一级菜单
}

void warehouseLayoutAndNavigation() {
    int choice=0;
    do {
        printf("\n仓库布局和导航功能\n");
        printf("1. 显示仓库布局\n");
        printf("2. 显示导航信息\n");
        printf("3. 返回上一级菜单\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("显示仓库布局\n");
                // 
                break;
            case 2:
                printf("显示导航信息\n");
                // 
                break;
            case 3:
                printf("返回上一级菜单\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice != 3);  // 选择3时返回上一级菜单
}

void dataStatisticsAndVisualization() {
    int choice=0;
    do {
        printf("\n数据统计和可视化功能\n");
        printf("1. 热门借还物品排行\n");
        printf("2. 活跃用户排行\n");
        printf("3. 返回上一级菜单\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("热门借还物品排行\n");
                // 
                break;
            case 2:
                printf("活跃用户排行\n");
                // 
                break;
            case 3:
                printf("返回上一级菜单\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice != 3);  // 选择3时返回上一级菜单
}

// 管理员主菜单
void adminMenu() {
    int choice=0;
    do {
        printf("\n管理员菜单：\n");
        printf("1. 物品管理\n");
        printf("2. 货架管理\n");
        printf("3. 用户管理\n");
        printf("4. 物品借还管理\n");
        printf("5. 仓库布局和导航\n");
        printf("6. 数据统计和可视化\n");
        printf("7. 退出登录\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                itemManagementMenu();  // 进入物品管理子菜单
                break;
            case 2:
                shelfManagementMenu();  // 进入货架管理子菜单
                break;
            case 3:
                admUserManagementMenu();  // 进入用户管理(管理员)子菜单
                break;
            case 4:
                printf("物品借还管理功能\n");
                borrowReturnManagementMenu();
                break;
            case 5:
                printf("仓库布局和导航功能\n");
                warehouseLayoutAndNavigation();
                break;
            case 6:
                printf("数据统计和可视化功能\n");
                dataStatisticsAndVisualization();
                break;
            case 7:
                printf("已退出登录。\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice != 7);  // 选择7时退出登录
}

// 用户主菜单
void studentMenu() {
    int choice=0;
    do {
        printf("\n学生菜单：\n");
        printf("1. 物品借还管理\n");
        printf("2. 仓库布局和导航\n");
        printf("3. 数据统计和可视化\n");
        printf("4. 修改用户密码\n");
        printf("5. 退出登录\n");
        printf("请输入选项：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                borrowReturnManagementMenu();  // 进入物品借还管理子菜单
                break;
            case 2:
                warehouseLayoutAndNavigation();
                break;
            case 3:
                dataStatisticsAndVisualization();
                break;
            case 4:
                stuChangePassword();
                break;
            case 5:
                printf("已退出登录。\n");
                break;
            default:
                printf("无效选项，请重新选择。\n");
        }
    } while (choice != 5);  // 选择4时退出登录
}
