#pragma once
#include "open.h"
#include <iostream>
#include <iomanip>
using std::cin, std::cout, std::endl;

//输入新的账户,bool型判断是否成功开户
void openAccount(BankListNode* head) {
    Account newaccount;
    // 新增标志位：标记是否需要退出当前函数
    bool exitFlag = false;

    cout << "开户操作：" << endl;
    cout << "请输入账号（输入0退出当前操作）：";
    cin >> newaccount.accountID;
    
    // 输入0退出当前操作
    if (newaccount.accountID == "0") {
        cout << "您选择退出当前操作..." << endl;
        return; // 直接返回，退出函数
    }

    //检验是否存在账户
    BankListNode* p = head->next;
    while (p != NULL) {
        if (p->account.accountID == newaccount.accountID) {
            cout << "错误：该账号已存在！开户失败。" << endl;
            return;
        }
        p = p->next;
    }
    //输入后续选项
    cout << "请输入开户人姓名（输入0退出当前操作）：";
    cin >> newaccount.ownerName;
    
    // 输入0退出当前操作
    if (newaccount.ownerName == "0") {
        cout << "您选择退出当前操作..." << endl;
        return; // 直接返回，退出函数
    }

    // 性别输入改为循环，用break跳出循环
    int inputgender = -1;
    while (true) {
        cout << "请输入性别（男性:1，女性:0，输入0退出当前操作）：";
        cin >> inputgender;
        
        // 输入0退出当前操作
        if (inputgender == 0) {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        } else if (inputgender == 1) {
            newaccount.gender = true;
            break; // 跳出性别输入循环
        } else {
            cout << "不支持其他性别！请重新输入！" << endl;
        }
    }

    cout << "请输入密码（输入0退出当前操作）：";
    cin >> newaccount.password;
    
    // 输入0退出当前操作
    if (newaccount.password == "0") {
        cout << "您选择退出当前操作..." << endl;
        return; // 直接返回，退出函数
    }

    // 金额输入改为循环，用break跳出循环
    double balanceInput = -1;
    while (true) {
        cout << "请输入开户金额（单位：元，输入0退出当前操作）：";
        cin >> balanceInput;
        
        // 输入0退出当前操作
        if (balanceInput == 0) {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        } else if (balanceInput > 0) {
            newaccount.balance = balanceInput * 100;//单位换算，元转为分
            break; // 跳出金额输入循环
        } else {
            cout << "开户金额不能为负数！请重新输入！" << endl;
        }
    }

    // 日期输入改为循环，用break跳出循环
    int year = -1, month = -1, day = -1;
    while (true) {
        cout << "请输入开户日期（输入：年 月 日，空格分隔，输入0退出当前操作）：";
        cin >> year >> month >> day;
        
        // 任意日期字段输入0退出当前操作
        if (year == 0 || month == 0 || day == 0) {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        } else if (year >= 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
            newaccount.creationDate.year = year;
            newaccount.creationDate.month = month;
            newaccount.creationDate.day = day;
            break; // 跳出日期输入循环
        } else {
            cout << "日期格式非法！请重新输入！" << endl;
        }
    }

    // 账户类型输入改为循环，用break跳出循环
    int current = -1;
    while (true) {
        cout << "请选择账户类型（定期：1，活期：0，输入0退出当前操作）：";
        cin >> current;
        
        // 输入0退出当前操作
        if (current == 0) {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        } else if (current == 1) {
            newaccount.isFixed = true;
            break; // 跳出类型输入循环
        } else {
            cout << "请输入正确的账户类型！请重新输入！" << endl;
        }
    }

    appendAccount(head, newaccount);
    cout << "开户成功" << endl;
    return;
}

void cancelaccount(BankListNode* head) {
    if (isEmpty(head)) {
        cout << "当前银行无任何账户信息，销户失败。" << endl;
        return;
    }
    cout << "销户操作：" << endl;
    cout << "请输入要注销的账户（输入0退出当前操作）：";
    string inputpassword, inputaccountID;
    cin >> inputaccountID;
    
    // 输入0退出当前操作
    if (inputaccountID == "0") {
        cout << "您选择退出当前操作..." << endl;
        return; // 直接返回，退出函数
    }

    cout << "请输入账户密码（输入0退出当前操作）：";
    cin >> inputpassword;
    
    // 输入0退出当前操作
    if (inputpassword == "0") {
        cout << "您选择退出当前操作..." << endl;
        return; // 直接返回，退出函数
    }

    BankListNode* p = head->next;
    while (p != NULL) {
        if (p->account.accountID == inputaccountID) {
            if (p->account.password == inputpassword) {
                p->account.balance = 0;
                deleteAccount(head, p);
                cout << "销户成功，账户已删除。" << endl;
                return;
            } else {
                cout << "错误：密码输入错误！销户失败。" << endl;
                return;
            }   
        }
        p = p->next;
    }
    cout << "错误：未找到该账号，销户失败。" << endl;
    return;
}

void print_whole_account(const Account& acc)
{
    cout << "账户ID:" << acc.accountID << '\n';
    cout << "账户姓名:" << acc.ownerName << '\n';
    cout << "账户性别:" << (acc.gender ? "男" : "女") << '\n';
    cout << "账户余额:" << std::fixed << std::setprecision(2) << acc.balance / 100.0 << " 元" << '\n';
    cout << "账户创建日期:" << acc.creationDate.year << "-" << acc.creationDate.month << "-" << acc.creationDate.day << '\n';
    cout << "账户类型:" << (acc.isFixed ? "定期" : "活期") << '\n';
}

void queryAccount(BankListNode* head, int choice, const string& targetID,
    const string& targetName, const Date& targetDate) {
    if (isEmpty(head)) { 
        cout << "当前银行无任何账户信息！" << endl;
        return;
    }

    // 查询方式输入改为循环，用break跳出循环
    while (true) {
        cout << "查询操作" << endl;
        cout << "请选择查询方式（输入0退出当前操作）：" << endl;
        cout << "1. 按账号查询  2. 按姓名查询  3. 按开户日期查询  4. 查询全部" << endl;
        cin >> choice;
        
        // 输入0退出当前操作
        if (choice == 0) {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        } else if (choice >= 1 && choice <= 4) {
            break; // 跳出查询方式选择循环
        } else {
            cout << "错误：查询方式选择无效！请重新输入！" << endl;
        }
    }

    BankListNode* p = head->next;
    bool found = false;

    switch (choice) {
    case 1: { // 按账号查询
        string targetID;
        cout << "请输入要查询的账号（输入0退出当前操作）：";
        cin >> targetID;
        
        // 输入0退出当前操作
        if (targetID == "0") {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        }

        while (p != nullptr) {
            if (p->account.accountID == targetID) {
                cout << "找到账户信息：" << endl;
                cout << "------------------------" << endl;
                print_whole_account(p->account);
                found = true;
                break;
            }
            p = p->next;
        }
        break;
    }
    case 2: { // 按姓名查询
        string targetName;
        cout << "请输入要查询的姓名（输入0退出当前操作）：";
        cin >> targetName;
        
        // 输入0退出当前操作
        if (targetName == "0") {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        }

        cout << "找到以下同名账户：" << endl;
        cout << "------------------------" << endl;
        while (p != nullptr) {
            if (p->account.ownerName == targetName) {
                print_whole_account(p->account);
                found = true;
            }
            p = p->next;
        }
        break;
    }
    case 3: { // 按开户日期查询
        Date targetDate;
        // 日期输入改为循环，用break跳出循环
        while (true) {
            cout << "请输入要查询的开户日期（格式：年 月 日，空格分隔，输入0退出当前操作）：";
            cin >> targetDate.year >> targetDate.month >> targetDate.day;
            
            // 任意日期字段输入0退出当前操作
            if (targetDate.year == 0 || targetDate.month == 0 || targetDate.day == 0) {
                cout << "您选择退出当前操作..." << endl;
                return; // 直接返回，退出函数
            } else if (targetDate.year >= 1900 && targetDate.month >= 1 && targetDate.month <= 12 && targetDate.day >= 1 && targetDate.day <= 31) {
                break; // 跳出日期输入循环
            } else {
                cout << "日期格式非法！请重新输入！" << endl;
            }
        }

        cout << "找到以下同日开户账户：" << endl;
        cout << "------------------------" << endl;
        while (p != nullptr) {
            if (p->account.creationDate == targetDate) {
                print_whole_account(p->account); 
                found = true;
            }
            p = p->next;
        }
        break;
    }
    case 4: { // 查询全部
        cout << "当前银行所有账户信息：" << endl;
        cout << "------------------------" << endl;
        while (p != nullptr) {
            print_whole_account(p->account);
            found = true;
            p = p->next;
        }
        break;
    }
    default:
        cout << "错误：查询方式选择无效！" << endl;
        return;
    }

    if (!found) {
        cout << "未找到符合条件的账户！" << endl;
    }
}