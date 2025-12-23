#include "banklist.h"

Date operator++(Date &d, int)
{
    Date temp = d; // 保存原始值用于返回
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool isr = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);

    // 修改 d 本身
    d.day++;
    if (d.month == 2)
    {
        if (d.day > isr + daysInMonth[2])
        {
            d.day = 1;
            d.month++;
        }
    }
    else if (d.day > daysInMonth[d.month])
    {
        d.day = 1;
        d.month++;
        if (d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }
    return temp; // 返回修改前的值
}

Date operator++(Date &d)
{
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool isr = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);

    d.day++;
    if (d.month == 2)
    {
        if (d.day > isr + daysInMonth[2])
        {
            d.day = 1;
            d.month++;
        }
    }
    else if (d.day > daysInMonth[d.month])
    {
        d.day = 1;
        d.month++;
        if (d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }
    return d; 
}

bool operator==(const Date &d1, const Date &d2)
{
    return (d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day);
}

bool operator!=(const Date &d1, const Date &d2)
{
    return !(d1 == d2);
}

bool operator<(const Date &d1, const Date &d2)
{
    if (d1.year != d2.year)
        return d1.year < d2.year;
    if (d1.month != d2.month)
        return d1.month < d2.month;
    return d1.day < d2.day;
}

bool operator>(const Date &d1, const Date &d2)
{
    if (d1.year != d2.year)
        return d1.year > d2.year;
    if (d1.month != d2.month)
        return d1.month > d2.month;
    return d1.day > d2.day;
}

int operator-(Date d1, Date d2)
{
    int d = 0, sign = 1;
    if (d1 == d2)
        return 0;
    if (d1 < d2)
    {
        swap(d1, d2);
        sign = -1;
    }
    while (d1 != d2)
    {
        ++d2;
        d++;
    }
    return d * sign;
}

BankListNode *createList()
{
    auto *head = new BankListNode;
    head->account = Account{};
    head->next = nullptr;
    return head;
}

void destroyList(BankListNode *head)
{
    auto *current = head;
    while (current != nullptr)
    {
        auto *tmp = current;
        current = current->next;
        delete tmp;
    }
}

bool isEmpty(BankListNode *head)
{
    return head->next == nullptr;
}

BankListNode *appendAccount(BankListNode *head, const Account &account)
{
    auto *newNode = new BankListNode;
    newNode->account = account;
    newNode->next = nullptr;

    auto *tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    tail->next = newNode;
    return newNode;
}

void deleteAccount(BankListNode *head, BankListNode *node)
{
    auto *prev = head;
    while (prev->next != nullptr)
    {
        if (prev->next == node)
        {
            auto *tmp = prev->next;
            prev->next = tmp->next;
            delete tmp;
            return;
        }
        prev = prev->next;
    }
}

void editAccount(BankListNode *node, const Account &newAccountData)
{
    if (node != nullptr)
        node->account = newAccountData;
}

bool loadFromFile(BankListNode *head, const string &filepath)
{
    // 未实现，假装导入
    Account acc1 = {"ACC1001", "Alice", false, "alicepwd", 500000, {2023, 5, 20}, false};
    Account acc2 = {"ACC1002", "Bob", true, "bobpwd", 750000, {2022, 11, 15}, true};
    appendAccount(head, acc1);
    appendAccount(head, acc2);
    return true;
}

bool saveToFile(BankListNode *head, const string &filepath)
{
    // 未实现，假装保存成功
    return true;
}