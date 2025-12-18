#include <iostream>
#include "banklist.h"
using std::cin, std::cout, std::endl;

int main()
{
    // 测试 list 操作
    BankListNode *list = createList();
    Account acc1{"1001", "Alice", false, "pass1", 500000, {2020, 1, 1}, false};
    Account acc2{"1002", "Bob", true, "pass2", 1000000, {2021, 2, 2}, true};
    appendAccount(list, acc1);
    appendAccount(list, acc2);
    cout << "List after adding two accounts:" << endl;
    for (BankListNode *node = list->next; node != nullptr; node = node->next)
    {
        cout << "AccountID: " << node->account.accountID << ", Owner: " << node->account.ownerName << endl;
    }
    // 测试删除账户
    deleteAccount(list, list->next); // 删除第一个账户
    cout << "List after deleting first account:" << endl;
    for (BankListNode *node = list->next; node != nullptr; node = node->next)
    {
        cout << "AccountID: " << node->account.accountID << ", Owner: " << node->account.ownerName << endl;
    }
    destroyList(list);
    return 0;
}