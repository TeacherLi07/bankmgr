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


void printAccount(const Account& acc) {
    //输入需要输出的东西
};

void queryAccount(BankListNode* head, int choice, const string& targetID,
    const string& targetName, const Date& targetDate) {
    if (isEmpty(head)) { // 是否为空函数
        //cout << "当前银行无任何账户信息！" << endl;
        return;
    }
    //查询操作
    //"1. 按账号查询  2. 按姓名查询  3. 按开户日期查询  4. 查询全部" << endl;
    //int num;
    //cin >> num;选择输入
    BankListNode* p = head->next;
    bool found = false;
    switch (choice) {
    case 1:
        while (p != NULL) {
            if (p->account.accountID == targetID) {
                printAccount(p->account);
                found = true;
            }
            p = p->next;
        }
        break;
    case 2:
        while (p != NULL) {
            if (p->account.ownerName == targetName) {
                printAccount(p->account);
                found = true;
            }
            p = p->next;
        }
        break;
    case 3:
        while (p != NULL) {
            if (p->account.creationDate == targetDate) {
                printAccount(p->account);
                found = true;
            }
            p = p->next;
        }
        break;
    case 4:
        while (p != nullptr) {
            printAccount(p->account);
            found = true;
            p = p->next;
        }
        break;

    default:
        return;
    }
    if (!found) {
        //未找到相关输入
    }   
}