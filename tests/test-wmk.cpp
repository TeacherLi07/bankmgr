#include <iostream>
#include <string>
#include "deposit&withdraw.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    // 1. 初始化链表
    cout << "正在初始化链表..." << endl;
    BankListNode* head = createList();

    // 2. 创建测试账户
    cout << "正在创建测试账户..." << endl;
    Account testAcc;
    testAcc.accountID = "1001";
    testAcc.password = "123456";
    testAcc.balance = 1000; // 初始余额 1000
    testAcc.ownerName = "TestUser";
    testAcc.isFixed = false;
    
    appendAccount(head, testAcc);
    cout << "账户已创建: ID=1001, 密码=123456, 余额=1000" << endl;

    // 3. 测试 find_accountID
    cout << "\n[测试 1] find_accountID" << endl;
    BankListNode* node = find_accountID(head, "1001");
    if (node != nullptr && node->account.accountID == "1001") {
        cout << "PASS: 成功找到账户 1001" << endl;
    } else {
        cout << "FAIL: 未找到账户 1001" << endl;
    }

    BankListNode* nodeFail = find_accountID(head, "9999");
    if (nodeFail == nullptr) {
        cout << "PASS: 正确处理不存在的账户" << endl;
    } else {
        cout << "FAIL: 错误地找到了不存在的账户" << endl;
    }

    if (node == nullptr) {
        cout << "无法继续测试，因为未找到账户。" << endl;
        destroyList(head);
        return 0;
    }

    // 4. 测试 password_correct
    cout << "\n[测试 2] password_correct" << endl;
    if (password_correct(node, "123456")) {
        cout << "PASS: 密码验证成功" << endl;
    } else {
        cout << "FAIL: 正确密码验证失败" << endl;
    }

    if (!password_correct(node, "wrong")) {
        cout << "PASS: 错误密码被拒绝" << endl;
    } else {
        cout << "FAIL: 错误密码验证通过" << endl;
    }

    // 5. 测试 depositmoney
    cout << "\n[测试 3] depositmoney" << endl;
    long long depositAmount = 500;
    cout << "存款: " << depositAmount << endl;
    depositmoney(node, depositAmount);
    if (node->account.balance == 1500) {
        cout << "PASS: 存款成功，当前余额: " << node->account.balance << endl;
    } else {
        cout << "FAIL: 存款失败，期望余额 1500，实际余额: " << node->account.balance << endl;
    }

    // 6. 测试 check_diposit_valid (检查取款是否有效)
    cout << "\n[测试 4] check_diposit_valid (检查余额是否充足)" << endl;
    // 当前余额 1500
    if (check_diposit_valid(node, 1000)) {
        cout << "PASS: 余额充足检查通过 (取 1000, 余额 1500)" << endl;
    } else {
        cout << "FAIL: 余额充足检查失败" << endl;
    }

    if (!check_diposit_valid(node, 2000)) {
        cout << "PASS: 余额不足检查通过 (取 2000, 余额 1500)" << endl;
    } else {
        cout << "FAIL: 余额不足检查失败" << endl;
    }

    // 7. 测试 withdrawmoney
    cout << "\n[测试 5] withdrawmoney" << endl;
    long long withdrawAmount = 300;
    cout << "取款: " << withdrawAmount << endl;
    withdrawmoney(node, withdrawAmount);
    if (node->account.balance == 1200) {
        cout << "PASS: 取款成功，当前余额: " << node->account.balance << endl;
    } else {
        cout << "FAIL: 取款失败，期望余额 1200，实际余额: " << node->account.balance << endl;
    }

    // 清理
    destroyList(head);
    cout << "\n所有测试结束。" << endl;

    return 0;
}