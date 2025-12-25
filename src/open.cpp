#pragma.once
#include "open.h"
#include <iostream>
using std::cin,std::cout,std::endl;
//输入新的账户,bool型判断是否成功开户
// 返回值：bool - 开户是否成功（true成功，false失败）
bool openAccount(BankListNode* head, Account newaccount) {
    // 开户操作：
    // 请输入账号：
    // 接收账号（由调用方传入newaccount.accountID）
    
    // 检验是否存在账户
    BankListNode* p = head->next;
    while (p != NULL) {
        if (p->account.accountID == newaccount.accountID) {
            // 错误：该账号已存在！开户失败。
            return false; // 账号已存在，开户失败
        }
        p = p->next;
    }
    
    // 请输入开户人姓名：
    // 接收开户人姓名（由调用方传入newaccount.ownerName）
    
    // 请输入性别（男性:1，女性:0）：
    // 接收性别输入（由调用方完成性别赋值及校验）
    // if (inputgender == 1)newaccount.gender = true;
    // else if (inputgender == 0)newaccount.gender = false;
    // else {
    //     不支持其他性别！
    //     return false; // 性别不合法，开户失败
    // }
    
    // 请输入密码：
    // 接收密码（由调用方传入newaccount.password）
    
    // 请输入开户金额（单位：元）：
    // 接收开户金额（由调用方传入对应金额，此处执行单位换算）
    double balanceInput = newaccount.balance / 100; // 保持原变量名，还原输入金额（若无需还原可删除）
    newaccount.balance = balanceInput * 100; // 单位换算，元转为分
    
    // 请输入开户日期（输入：年 月 日，空格分隔）：
    // 接收开户日期（由调用方传入newaccount.creationDate的年、月、日）
    
    // 请选择账户类型（定期：1，活期：0）：
    // 接收账户类型输入（由调用方完成账户类型赋值及校验）
    // if (current == 1)newaccount.isFixed = true;
    // else if (current == 0)newaccount.isFixed = false;
    // else {
    //     请输入正确的账户类型！
    //     return false; // 账户类型不合法，开户失败
    // }
    
    appendAccount(head, newaccount);
    // 开户成功
    return true; // 开户成功
}

// 销户函数：移除输入输出，仅处理账户数据逻辑
// 参数说明：
// head - 银行链表头节点
// inputaccountID - 待注销的账号（由调用方传入）
// inputpassword - 待注销账户的密码（由调用方传入）
// 返回值：int - 销户结果状态码
//         0：销户成功
//         1：银行无账户，销户失败
//         2：密码输入错误，销户失败
//         3：未找到该账号，销户失败
int cancelaccount(BankListNode* head, string inputaccountID, string inputpassword) {
    if (isEmpty(head)) {
        // 当前银行无任何账户信息，销户失败。
        return 1; // 无账户，销户失败
    }
    
    // 销户操作：
    // 请输入要注销的账户：
    // 接收待注销账号（由调用方传入inputaccountID）
    // 请输入账户密码：
    // 接收账户密码（由调用方传入inputpassword）
    
    BankListNode* p = head->next;
    while (p != NULL) {
        if (p->account.accountID == inputaccountID) {
            if (p->account.password == inputpassword) {
                p->account.balance = 0;
                deleteAccount(head, p);
                // 销户成功，账户已删除。
                return 0; // 销户成功
            } else {
                // 错误：密码输入错误！销户失败。
                return 2; // 密码错误，销户失败
            }   
        }
        p = p->next;
    }
    
    // 错误：未找到该账号，销户失败。
    return 3; // 未找到账号，销户失败
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