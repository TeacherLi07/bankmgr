#include <iostream>
#include "open.h"
#include "banklist.h"
#include <windows.h>0
using std::cin, std::cout, std::endl;


int main() {
    // 1. 初始化链表（使用banklist.h的createList接口）
 //   BankListNode* head = createList();
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
 
 BankListNode *head = createList(); 
    int mainChoice = 0;

    // 2. 主菜单循环（测试open.cpp所有功能）
    while (true) {
        cout << "===================== 银行账户管理系统 =====================" << endl;
        cout << "1. 开户" << endl;
        cout << "2. 销户" << endl;
        cout << "3. 查询账户" << endl;
        cout << "4. 保存账户到文件" << endl;
        cout << "5. 从文件加载账户" << endl;
        cout << "0. 退出系统" << endl;
        cout << "==========================================================" << endl;
        cout << "请选择操作：";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                // 测试开户功能
                openAccount(head);
                cout << "----------------------------------------------------------" << endl;
                break;
            }

            case 2:{
                // 测试销户功能
                cancelaccount(head);
                cout << "----------------------------------------------------------" << endl;
                break;
            }

            case 3:{
                // 测试查询功能（修正原函数冗余参数问题）
                int dummyChoice = 0;
                string dummyID="", dummyName="";
                Date dummyDate;
                queryAccount(head, dummyChoice, dummyID, dummyName, dummyDate);
                cout << "----------------------------------------------------------" << endl;
                break;
            }

            case 4: {
                // 测试保存文件功能
                string filepath;
                cout << "请输入保存文件路径（如：accounts.txt）：";
                cin >> filepath;
                if (saveToFile(head, filepath)) {
                    cout << "账户信息保存成功！" << endl;
                } else {
                    cout << "账户信息保存失败！" << endl;
                }
                cout << "----------------------------------------------------------" << endl;
                break;
            }

            case 5: {
                // 测试加载文件功能
                string filepath;
                cout << "请输入加载文件路径（如：accounts.txt）：";
                cin >> filepath;
                if (loadFromFile(head, filepath)) {
                    cout << "账户信息加载成功！" << endl;
                } else {
                    cout << "账户信息加载失败！" << endl;
                }
                cout << "----------------------------------------------------------" << endl;
                break;
            }

            case 0:{
                // 退出系统，释放链表（使用banklist.h的destroyList接口）
                cout << "正在退出系统，释放资源..." << endl;
                destroyList(head);
                cout << "系统已退出！" << endl;
                return 0;
            }

            default:{
                cout << "无效的选择，请重新输入！" << endl;
                cout << "----------------------------------------------------------" << endl;
                break;
            }
        }
    }
}