#include <iostream>
#include "Sort.h"

using std::cout;
using std::endl;

// 帮助函数：把一个账户追加到单链表尾部（不带头结点）
void pushBack(BankListNode *&head, BankListNode *&tail, const Account &acc)
{
    auto *node = new BankListNode;
    node->account = acc;
    node->next = nullptr;

    if (head == nullptr)
    {
        head = tail = node;  // 第一个节点
    }
    else
    {
        tail->next = node;   // 接在尾巴后面
        tail = node;         // 更新尾指针
    }
}

// 帮助函数：打印链表（只打印几个关键字段）
// 这里传入的是“数据链表的首节点”，所以 main 里会传 head->next
void printList(const BankListNode *head)
{
    cout << "账号\t\t姓名\t\t余额(分)\t\t开户日期\t\t类型\n";
    while (head != nullptr)
    {
        const Account &a = head->account;
        cout << a.accountID << "\t"
             << a.ownerName << "\t\t"
             << a.balance << "\t\t"
             << a.creationDate.year << "-"
             << a.creationDate.month << "-"
             << a.creationDate.day << "\t\t"
             << (a.isFixed ? "定期" : "活期")
             << endl;
        head = head->next;
    }
}

// 释放整条链表（包含头结点）
void freeList(BankListNode *head)
{
    while (head != nullptr)
    {
        BankListNode *tmp = head->next;
        delete head;
        head = tmp;
    }
}

int main()
{
    cout << "\nHello, this is wj's sort test.\n" << endl;

    // 1. 准备 10 个测试数据
    Account testAccounts[10] = {
        {"ACC1001", "Alice",  false, "pwd1",  600000, {2023, 5, 20}, false},
        {"ACC1005", "Alice",  true,  "pwd2",  200000, {2021, 1, 10}, true },
        {"ACC1003", "Alice",true,  "pwd3",  800000, {2022, 3, 15}, false},
        {"ACC1002", "Bob",    true,  "pwd4",  100000, {2020, 7,  1}, true },
        {"ACC1010", "Ivy",    false, "pwd5", 1500000, {2019,12, 30}, false},
        {"ACC1007", "Grace",  false, "pwd6",  300000, {2024, 2,  5}, true },
        {"ACC1009", "Henry",  true,  "pwd7",  600000, {2018, 8, 18}, false},
        {"ACC1004", "Brian",  true,  "pwd8",  600000, {2023, 6,  6}, true },
        {"ACC1008", "Frank",  true,  "pwd9",  400000, {2022,10, 11}, false},
        {"ACC1006", "Eva",    false, "pwd10", 600000, {2021, 4, 25}, true }
    };

    // 2. 用这 10 个数据创建一条链表（带头结点）
    BankListNode *head = new BankListNode; // 头结点，不存放有效账户数据
    head->next = nullptr;

    BankListNode *dataHead = nullptr;  // 实际数据链表的首节点
    BankListNode *tail = nullptr;
    for (const auto &acc : testAccounts)
    {
        // 先构建不带头结点的数据链表
        pushBack(dataHead, tail, acc);
    }
    // 再把数据链表挂到头结点后面
    head->next = dataHead;

    cout << "===== 原始（带头结点，以下从 head->next 开始打印） =====" << endl;
    printList(head->next);

    // 3. 按姓名排序测试
    // 约定：SortByXXX 传入的是“带头结点的 head”，
    // 返回的是排序后数据链表的首节点（即 head->next）
    BankListNode *sortedByNameHead = SortByName(head);
    cout << "\n===== 按姓名排序结果 =====" << endl;
    printList(sortedByNameHead->next);

    // 4. 按金额排序测试
    BankListNode *sortedByMoneyHead = SortByMoney(head);
    cout << "\n===== 按金额排序结果 =====" << endl;
    printList(sortedByMoneyHead->next);

    // 5. 按账号排序测试
    BankListNode *sortedByAccountHead = SortByAccount(head);
    cout << "\n===== 按账号排序结果 =====" << endl;
    printList(sortedByAccountHead->next);

    // 这里假设三个 SortByXXX 都是在“同一条链表上原地排序”的实现，
    // 所以最后只释放一次 head 即可
    freeList(head);

    return 0;
}