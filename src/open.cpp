#include "input.h"
#include "open.h"
#include <iostream>
#include <iomanip>
using std::cin, std::cout, std::endl;

//输入新的账户,bool型判断是否成功开户
void openAccount(BankListNode* head) {
    Account newaccount;

    cout << "请输入账号（输入0退出当前操作）: ";
    string temp_accountID;
    inputAccountID(temp_accountID);
    if (temp_accountID == "0") {
        return; // 直接返回，退出函数
    }
    newaccount.accountID = temp_accountID;

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
    cout << "请输入开户人姓名（输入0退出当前操作）: ";
    inputName(newaccount.ownerName);
    
    // 输入0退出当前操作
    if (newaccount.ownerName == "0") {
        return; // 直接返回，退出函数
    }

    // 性别输入改为循环，用break跳出循环
    int input_gender;
    while (true) {
        cout << "请输入性别（男性:1，女性:0，输入2退出当前操作）: ";
        inputgender(input_gender);
        // 输入0退出当前操作
        if (input_gender == 2) {
            return; // 直接返回，退出函数
        } else if (input_gender == 1) {
            newaccount.gender = true;
            break; // 跳出性别输入循环
        } else if (input_gender == 0) {
            newaccount.gender = false;
            break; // 跳出性别输入循环
        } else {
            cout << "性别输入错误！请重新输入！" << endl;
        }
    }

    cout << "请输入密码（输入0退出当前操作）: ";
    
    inputpassword(newaccount.password);
    // 输入0退出当前操作
    if (newaccount.password == "0") {
        return; // 直接返回，退出函数
    }

    // 金额输入改为循环，用break跳出循环
    long long balanceInput = -1;
    while (true) {
        cout << "请输入开户金额（单位：元，输入-1退出当前操作）: ";
        inputmoney(balanceInput);
        // 输入0退出当前操作
        if (balanceInput == -1) {
            return; // 直接返回，退出函数
        } else if (balanceInput >= 0) {
            newaccount.balance = balanceInput;
            break; // 跳出金额输入循环
        } else {
            cout << "开户金额不能为负数！请重新输入！" << endl;
        }
    }

    // 日期输入改为循环，用break跳出循环
    Date tempDate;
    while (true) {
        cout << "请输入开户日期（输入：YYYYMMDD，（输入00000000退出当前操作）: ";
        inputdate(tempDate);
        if (!isValid(tempDate)) 
        {
            cout << "日期格式非法！请重新输入！" << endl;
            continue;
        }
        else if (tempDate.year == 0 && tempDate.month == 0 && tempDate.day == 0) {
            printf("您选择退出当前操作...\n");
            return; // 直接返回，退出函数
        }
        else {
            newaccount.creationDate = tempDate;
            break; // 跳出日期输入循环
        }
    }
    // 账户类型输入改为循环，用break跳出循环
    int current;
    while (true) {
        cout << "请选择账户类型（定期：1，活期：0，输入-1退出当前操作）: ";
        inputAccountType(current);
        // 输入0退出当前操作
        if (current == 0) {
            newaccount.isFixed = false;
            break; // 跳出类型输入循环
        } else if (current == 1) {
            newaccount.isFixed = true;
            break; // 跳出类型输入循环
        } 
        else if (current == -1) {
            return; // 直接返回，退出函数
        }
        else {
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
    cout << "请输入要注销的账户ID（输入0退出当前操作）: ";
    string input_password, input_accountID;
    inputpassword(input_accountID);
    
    // 输入0退出当前操作
    if (input_accountID == "0") {
        cout << "您选择退出当前操作..." << endl;
        return; // 直接返回，退出函数
    }

    cout << "请输入账户密码（输入0退出当前操作）: ";
    inputpassword(input_password);
    
    // 输入0退出当前操作
    if (input_password == "0") {
        cout << "您选择退出当前操作..." << endl;
        return; // 直接返回，退出函数
    }

    BankListNode* p = head->next;
    while (p != NULL) {
        if (p->account.accountID == input_accountID) {
            if (p->account.password == input_password) {
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
    cout << "账户ID: " << acc.accountID << '\n';
    cout << "账户姓名: " << acc.ownerName << '\n';
    cout << "账户性别: " << (acc.gender ? "男" : "女") << '\n';
    cout << "账户余额: " << std::fixed << std::setprecision(2) << acc.balance / 100.0 << " 元" << '\n';
    cout << "账户创建日期: " << acc.creationDate.year << "-" << acc.creationDate.month << "-" << acc.creationDate.day << '\n';
    cout << "账户类型: " << (acc.isFixed ? "定期" : "活期") << '\n';
}

void queryAccount(BankListNode* head)
{
    if (isEmpty(head)) { 
        cout << "当前银行无任何账户信息！" << endl;
        return;
    }
    int choice = -1;
    // 查询方式输入改为循环，用break跳出循环
    while (true) {
        cout << "请选择查询方式（输入0退出当前操作）: " << endl;
        cout << "1. 按账号查询  2. 按姓名查询  3. 按开户日期查询  4. 查询全部" << endl;
        
        inputgender(choice);
        // 输入0退出当前操作
        if (choice == 0) {
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
        cout << "请输入要查询的账号（输入0退出当前操作）: ";
        inputAccountID(targetID);
        
        // 输入0退出当前操作
        if (targetID == "0") {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        }

        while (p != nullptr) {
            if (p->account.accountID == targetID) {
                cout << "------------------------" << endl;
                print_whole_account(p->account);
                found = true;
                break;
            }
            p = p->next;
        }
        cout << "------------------------" << endl;
        break;
    }
    case 2: { // 按姓名查询
        string targetName;
        cout << "请输入要查询的姓名（输入0退出当前操作）: ";
        inputName(targetName);
        
        // 输入0退出当前操作
        if (targetName == "0") {
            cout << "您选择退出当前操作..." << endl;
            return; // 直接返回，退出函数
        }

        cout << "------------------------" << endl;
        while (p != nullptr) {
            if (p->account.ownerName == targetName) {
                print_whole_account(p->account);
                found = true;
            }
            p = p->next;
        }
        cout << "------------------------" << endl;
        break;
    }
    case 3: { // 按开户日期查询
        Date targetDate;
        // 日期输入改为循环，用break跳出循环
        while (true) {
            cout << "请输入要查询的开户日期（格式:YYYYMMDD，空格分隔，输入0退出当前操作）: ";
            inputdate(targetDate);

            // 任意日期字段输入0退出当前操作
            if (targetDate.year == 0 || targetDate.month == 0 || targetDate.day == 0) {
                cout << "您选择退出当前操作..." << endl;
                return; // 直接返回，退出函数
            } else if (!isValid(targetDate)) {
                cout << "日期格式非法！请重新输入！" << endl;
                continue;
            } else {
                break; // 跳出日期输入循环
            }
        }
        cout << "------------------------" << endl;
        while (p != nullptr) {
            if (p->account.creationDate == targetDate) {
                print_whole_account(p->account); 
                found = true;
            }
            p = p->next;
        }
        cout << "------------------------" << endl;
        break;
    }
    case 4: { // 查询全部
        cout << "当前银行所有账户信息: " << endl;
        
        while (p != nullptr) {
            cout << "------------------------" << endl;
            print_whole_account(p->account);
            found = true;
            p = p->next;
        }
        cout << "------------------------" << endl;
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