#pragma.once
#include "open.h"
#include <iostream>
using std::cin,std::cout,std::endl;

//输入新的账户,bool型判断是否成功开户
void openAccount(BankListNode* head) {
    Account newaccount;
    cout << "开户操作：" << endl;
    cout << "请输入账号：";
    cin >> newaccount.accountID;
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
    cout << "请输入开户人姓名：";
    cin >> newaccount.ownerName;
    cout << "请输入性别（男性:1，女性:0）：";
    //检验是否输入正确性别
    int inputgender;
    cin >> inputgender;
    if (inputgender == 1)newaccount.gender = true;
    else if (inputgender == 0)newaccount.gender = false;
    else {
        cout << "不支持其他性别！";
        return;
    }
    cout << "请输入密码：";
    cin >> newaccount.password;
    cout << "请输入开户金额（单位：元）：";
    double balanceInput;
    cin >> balanceInput;
    newaccount.balance = balanceInput * 100;//单位换算，元转为分
    cout << "请输入开户日期（输入：年 月 日，空格分隔）：";
    cin >> newaccount.creationDate.year
        >> newaccount.creationDate.month
        >> newaccount.creationDate.day;
    cout << "请选择账户类型（定期：1，活期：0）：";
    int current;
    cin >> current;
    if (current == 1)newaccount.isFixed = true;
    else if (current == 0)newaccount.isFixed = false;
    else {
        cout << "请输入正确的账户类型！";
        return;
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
    cout << "请输入要注销的账户：";
    string inputpassword, inputaccountID;
    cin >> inputaccountID;
    cout << "请输入账户密码：";
    cin >> inputpassword;
    BankListNode* p = head->next;
    while (p != NULL) {
        if (p->account.accountID == inputaccountID) {
            if (p->account.password == inputpassword) {
                p->account.balance = 0;
                deleteAccount(head, p);
                cout << "销户成功，账户已删除。" << endl;
                return;
            }
            else {
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
    cout << "账户余额:" << acc.balance / 100.0 << " 元" << '\n';
    cout << "账户创建日期:" << acc.creationDate.year << "-" << acc.creationDate.month << "-" << acc.creationDate.day << '\n';
    cout << "账户类型:" << (acc.isFixed ? "定期" : "活期") << '\n';
}

void queryAccount(BankListNode* head, int choice, const string& targetID,
    const string& targetName, const Date& targetDate) {
    if (isEmpty(head)) { // 调用模板判空函数
        cout << "当前银行无任何账户信息！" << endl;
        return;
    }

    cout << "查询操作" << endl;
    cout << "请选择查询方式：" << endl;
    cout << "1. 按账号查询  2. 按姓名查询  3. 按开户日期查询  4. 查询全部" << endl;
    cin >> choice;
    BankListNode* p = head->next;
    bool found = false;

    switch (choice) {
    case 1: { // 按账号查询
        string targetID;
        cout << "请输入要查询的账号：";
        cin >> targetID;

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
        cout << "请输入要查询的姓名：";
        cin >> targetName;

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
        cout << "请输入要查询的开户日期（格式：年 月 日，空格分隔）：";
        cin >> targetDate.year >> targetDate.month >> targetDate.day;

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